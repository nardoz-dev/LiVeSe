// Standard Libs

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Timers Libs

#include "xtimer.h"
#include "ztimer.h"

// LoraWan

#include "net/loramac.h"
#include "semtech_loramac.h"
#include "fmt.h"

//Drivers

#include "sx127x.h"
#include "sx127x_netdev.h"
#include "sx127x_params.h"


// Random MSG


#include "random.h"





#define SLEEP_IOTLAB        3



static semtech_loramac_t loramac;

static sx127x_t sx127x;


char *message = "This is LiveSe!";

static uint8_t deveui[LORAMAC_DEVEUI_LEN];
static uint8_t appeui[LORAMAC_APPEUI_LEN];
static uint8_t appkey[LORAMAC_APPKEY_LEN];






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



static void send_message(void)
{

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


void random_msg(void){

    uint32_t random_num=random_uint32_range(0,3);
    
    if(random_num==0){
        message = "RED";
    }
    else if(random_num==1){
        message ="YELLOW";
    }
    else{
        message = "GREEN";
    }
}


int main(void){
    LoraInit();
    while(1){
        random_msg();
        printf("This is the messagge to send via Lora ----> %s\n",message);
        send_message();
        xtimer_sleep(SLEEP_IOTLAB);
    }
}