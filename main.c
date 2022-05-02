#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Riot Libraries
#include "shell.h"
#include "thread.h"
#include "xtimer.h"
#include "xtimer.h"
#include "pir.h"
#include "periph/adc.h"
#include "periph/gpio.h"
#include "analog_util.h"

//Usefull constant for our code
#define ADC_MIC                  ADC_LINE(2)
#define ADC_LIGHT                ADC_LINE(0)
#define ADC_RES                  ADC_RES_12BIT
#define SLEEP_SENSOR			 1
#define SLEEP_MAIN				 5
#define DELAY                       (1000LU * US_PER_MS) /* 100 ms */

//Global variables
char stack[THREAD_STACKSIZE_MAIN];
kernel_pid_t pid = 0;
int flag = 0;
xtimer_ticks32_t last ;
int sample = 0;
int lux = 0;
pir_t dev;	
int MIC_samp = 0;
int LIGHT_samp = 0;
int vol = 0;
int light =0;
pir_event_t read = 0;
int final_result=0;
int pir_counter=0;
int current_result=0;
int pir_value;
int old_final_result=4;
    
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
int computeAlgNoMIC(int l,pir_event_t m){
    int z=0;
    if((int)m==0){
        z=0;
    }
    else{
        z=40;
    }
    return l+z;
}

//Main function thread - used to read values from sensors
void *thread_handler(void *arg) {	    
   	read = pir_get_status( &dev);
    while (flag ==0) {
        //Main loop
        xtimer_sleep(SLEEP_SENSOR);
        MIC_samp = adc_sample(ADC_MIC, ADC_RES);        
        vol = adc_util_map(MIC_samp, ADC_RES, 1, 25);
        LIGHT_samp = adc_sample(ADC_LIGHT, ADC_RES);        
        light = adc_util_map(LIGHT_samp, ADC_RES, 1, 60);
        
        //Pir read
        read=pir_get_status(&dev);
        if(read ==150 ){
            pir_value=0;            //No motion detected
		}
		else {
            pir_value=1;            //Motion detected
		}

        //Algorithm to interpolate data from sensors
        current_result=computeAlgNoMIC(light,pir_value);
        if(current_result >=0 && current_result <=33){
            final_result=0;                                 //Not secure ----> RED STREET
        }
        else if(current_result >= 34 && current_result <=66){
            final_result=1;                                 //More or less secure ----> ORANGE STREET
        }
        else{
            final_result=2;                                 //Secure -----> GREEN STREET
        }

    }
    // Put itself in zombie state
   	thread_zombify();
   	
    (void)arg;
    return NULL;
}

//Create and start thread
int th_start(int argc , char **argv){
    pid = thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST,
                  thread_handler, NULL,
                  "thread");
    
	(void)argc;
	(void)argv;
	return 0;
}

int th_stop(int argc , char **argv){
	//status[ 1 : pending-zombie | 3 : bl mutex ] 
	flag = 1;
	printf("waiting for kill...\n");
	while( thread_getstatus(pid) != 1) { }
	int ret = thread_kill_zombie(pid);
	printf("dead!:%d\n",ret);
	//reset flag
	flag = 0;
	pid = 0;
	(void)argc;
	(void)argv;
	return 0;
}

int th_pid(int argc , char **argv){

		printf("pid--%d\n",pid);
		printf("status--%d\n", thread_getstatus(pid));
		
	(void)argc;
	(void)argv;
	return 0;
	
	}


int mad_main(int argc , char **argv){

    // MAIN ROUTINE 
	while(1){
		xtimer_sleep(SLEEP_MAIN);
        // Read sensors, Execute logic , be ready to send data via Lora
		//printf("::::I'M the MAIN::::\n");

		printf("LIGHT ===> %d\t VOLUME ===> %d\t  PIR===> %s\n", light ,vol , pir_value ? "Movement Detected" : "No Movement Detected");
        printf("0--->RED!\t 1--->ORANGE!\t 2--->GREEN!\n----->Current Value is: %d\n\n",final_result);
       
        //Next upgrade send via LoRa
    			
	}
	(void)argc;
	(void)argv;
	return 0;	
}
	

//Shell command 
static const shell_command_t commands[] = {
/* if you want new commands on the board write here yours!!! */
    {"sample" , "start sample" , th_start},
    { "stop" , "stop " , th_stop},
    { "pid" , "see pid" , th_pid },
    { "mad" , "mad-MODE" , mad_main }
};

int main(void)
{
    puts("LiVeSe_Dev2");	 	
    // Initialization the ADC line for MIC - PHOTORESISTOR
	if (adc_init(ADC_MIC) < 0) {
        return 1;
    }
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

    last = xtimer_now();
	th_start(1,NULL);
	mad_main(1,NULL);
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    
    //This will be never executed
    return 0;
}


