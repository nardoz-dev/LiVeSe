// Default Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Riot Libraries
#include "thread.h"
#include "xtimer.h"
#include "ztimer.h"
#include "pir.h"
#include "periph/adc.h"
#include "periph/gpio.h"
#include "analog_util.h"
#include "fmt.h"
// LoraWan Libraries
#include "net/loramac.h"
#include "semtech_loramac.h"
//Drivers
#include "sx127x.h"
#include "sx127x_netdev.h"
#include "sx127x_params.h"

//Useful constant for our code
#define ADC_MIC                  ADC_LINE(2)
#define ADC_LIGHT                ADC_LINE(0)
#define ADC_RES                  ADC_RES_12BIT
#define SLEEP_LORA               10

// LoraWan Define
#define PM_LOCK_LEVEL       (1)
static semtech_loramac_t loramac;
static sx127x_t sx127x;


char *message = "This is LiveSe!";

static uint8_t deveui[LORAMAC_DEVEUI_LEN];
static uint8_t appeui[LORAMAC_APPEUI_LEN];
static uint8_t appkey[LORAMAC_APPKEY_LEN];

//Global variables
bool LoraOk=false;
char stackPir[THREAD_STACKSIZE_DEFAULT];
char stackCompute[THREAD_STACKSIZE_DEFAULT];
kernel_pid_t pid_read = 0;
kernel_pid_t pid_pir = 0;
xtimer_ticks32_t last ;
uint8_t sample = 0;
uint8_t lux = 0;
pir_t dev;	
uint8_t mic_Samp = 0;
int LIGHT_samp = 0;
uint8_t old_Light = 78;
uint8_t vol = 0;
uint8_t light =0;
pir_event_t readPir = 0;
uint8_t final_result=0;
uint8_t pir_counter=0;
uint8_t current_result=0;
uint8_t pir_value;
uint8_t street_value=101;
bool same_read_mic=false;
uint8_t sleep_sensors=5;


void LoraInit(void){

    // Drivers Setup

    sx127x_setup(&sx127x, &sx127x_params[0], 0);
    loramac.netdev = &sx127x.netdev;
    loramac.netdev->driver = &sx127x_driver;

    //Lora Stack

    semtech_loramac_init(&loramac);


    //Over The Air Activation 

    fmt_hex_bytes(deveui, CONFIG_LORAMAC_DEV_EUI_DEFAULT);
    fmt_hex_bytes(appeui, CONFIG_LORAMAC_APP_EUI_DEFAULT);
    fmt_hex_bytes(appkey, CONFIG_LORAMAC_APP_KEY_DEFAULT);
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);

    semtech_loramac_set_dr(&loramac, LORAMAC_DR_5);

   
    
    if (!semtech_loramac_is_mac_joined(&loramac)) {
        
        puts("Starting join procedure");
        if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
            puts("Join procedure failed");
            return;
        }
    }
    
    puts("Join procedure succeeded");
}


static void send_message(void){
    printf("Sending: %s\n", message);
    
    uint8_t ret = semtech_loramac_send(&loramac, (uint8_t *)message, strlen(message));
    while(ret!= SEMTECH_LORAMAC_TX_DONE){
    ret = semtech_loramac_send(&loramac, (uint8_t *)message, strlen(message));
    }
    puts("Message sent!");
    
    if (ret != SEMTECH_LORAMAC_TX_DONE)  {
        printf("Cannot send message '%s', ret code: %d\n", message, ret);
        return;
    }
	
}


void create_msg(void){
    if(street_value==0){
        message = "RED";
    }
    else if(street_value==1){
        message ="YELLOW";
    }
    else{
        message = "GREEN";
    }
}
    
/* Algorithm 1.0 (More precise)
int computeAlg(int l,int v,pir_event_t m){
    int z=0;
    if((int)m==0){
        z=0;
    }
    else{
        z=30;
    }
    return l+v+z;
}
*/

// Standard algorithm
uint8_t computeAlgNoMIC(uint8_t l,pir_event_t m){
    uint8_t z=0;
    if((uint8_t)m==0){
        z=0;
    }
    else{
        z=40;
    }
    return l+z;
}

// Pir Handler Algorithm
void *pir_handler(void* arg){
    (void) arg;
    while(1){
        //puts("Sono nel thread PIR");
        if(pir_counter!=0){
            pir_counter-=1;
            if(same_read_mic){
                xtimer_sleep(4);
            }
            else{
                xtimer_sleep(3);
            }
        }
        else{
            readPir=pir_get_status(&dev);
            if(readPir ==150 ){
                pir_value=0;            //No motion detected
            }
            else {
                pir_value=1;            //Motion detected
                pir_counter=10;
            }
            xtimer_sleep(10);
        }
    }
}

//Main function thread - used to read values from sensors
void *read_handler(void *arg) {	   
    
    (void)arg;
    while(1){
        //puts("Ciao sono nel Thread di lettura!");
   	
    
       
        //Main loop
        
        //MIC_samp = adc_sample(ADC_MIC, ADC_RES);        
        //vol = adc_util_map(MIC_samp, ADC_RES, 1, 25);
        LIGHT_samp = adc_sample(ADC_LIGHT, ADC_RES);
               
        light = adc_util_map(LIGHT_samp, ADC_RES, 1, 60);
        //printf("LIGHT RAW : %d \n ", LIGHT_samp) ;
        //printf("LIGHT CONVERTED : %d \n \n \n ", light) ;
        
        if(abs(old_Light-light) <=5){
            same_read_mic=true;
            sleep_sensors=10;
        }
        
        else{
            same_read_mic=false;
            sleep_sensors=5;
        }
        

        //Algorithm to interpolate data from sensors
        current_result=computeAlgNoMIC(light,pir_value);
        
        if(current_result <=33){
            final_result=0;                                 //Not secure ----> RED STREET
        }
        else if(current_result >= 34 && current_result <=66){
            final_result=1;                                 //More or less secure ----> ORANGE STREET
        }
        else{
            final_result=2;                                 //Secure -----> GREEN STREET
        }
        old_Light=light;
        
        xtimer_sleep(sleep_sensors);
        
    }
  
    return NULL;
}

// Main
int main(void){
    puts("LiVeSe_Dev2");
	
    // Initialization the ADC line for MIC - PHOTORESISTOR
    /*
	if (adc_init(ADC_MIC) < 0) {
        return 1;
    }
    */
    if (adc_init(ADC_LIGHT) < 0) {
        return 1;
    }

    // PIR initialization		
	pir_params_t params;
	params.gpio = GPIO_PIN(PORT_A, 10);
	params.active_high = 0;
	if(pir_init( &dev, &params) != 0 ){
		return 0;
    }
    
    LoraInit();
    
	pid_read = thread_create(stackCompute, sizeof(stackCompute),
                  THREAD_PRIORITY_MAIN - 1,
                  0,
                  read_handler, NULL,
                  "thread_read");

    puts("Thread lettura creato");

    pid_pir = thread_create(stackPir, sizeof(stackPir),
                  THREAD_PRIORITY_MAIN - 1,
                  0,
                  pir_handler, NULL,
                  "thread_pir");

    puts("Thread Pir creato");


    while(1){
        
		printf("LIGHT ===> %d\t VOLUME ===> %d\t  PIR===> %s\n", light ,vol , pir_value ? "Movement Detected" : "No Movement Detected");
        printf("0--->RED!\t 1--->ORANGE!\t 2--->GREEN!\n----->Current Value is: %d\n\n",final_result);

        if(final_result!=street_value){
            street_value=final_result;
            create_msg();
            message="YELLOW";
            printf("This is the messagge to send via Lora ----> %s\n",message);
            send_message();
        }
        xtimer_sleep(SLEEP_LORA);
    }

    //This will be never executed
    return 0;
}


