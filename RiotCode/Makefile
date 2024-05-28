# name of your application
APPLICATION = LiVeSeMain

# If no BOARD is found in the environment, use this default:
BOARD ?=  b-l072z-lrwan1  #native  b-l072z-lrwan1 iotlab-m3 

#CONTINUE_ON_EXPECTED_ERRORS=1


# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

#Lora OTA
APPEUI ?= 0000000000000000
DEVEUI ?= 70B3D57ED004FBE2                        #ANTONIO
APPKEY ?= 6D70E2413BCB9E7CAECD628135306D8F

# DEVEUI ?= 70B3D57ED004FAEF
# APPEUI ?= 0000000000000000
# APPKEY ?= AEEA78EFE6778AFFDBB6414A92C44A05

# Send a message every 20s after joining the network


# Pass these enviroment variables to docker
DOCKER_ENV_VARS += DEVEUI
DOCKER_ENV_VARS += APPEUI
DOCKER_ENV_VARS += APPKEY

# Default radio driver is Semtech SX1276 (used by the B-L072Z-LRWAN1 board)
DRIVER ?= sx1276

# Default region is Europe and default band is 868MHz
LORA_REGION ?= EU868

# Include the Semtech-loramac package
USEPKG += semtech-loramac

USEMODULE += $(DRIVER)
USEMODULE += fmt
FEATURES_OPTIONAL += periph_rtc
FEATURES_OPTIONAL += periph_eeprom

#CFLAGS



#Allow Stop Mode

CFLAGS += -DPM_BLOCKER_INITIAL=0x00000001

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Modules to include:
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += xtimer
USEMODULE += analog_util
USEMODULE += pir
#photoresistor
FEATURES_REQUIRED+= periph_adc 
#lora
FEATURES_REQUIRED+= periph_i2c  


ifndef CONFIG_KCONFIG_USEMODULE_LORAWAN
 # OTAA compile time configuration keys
 CFLAGS += -DCONFIG_LORAMAC_APP_KEY_DEFAULT=\"$(APPKEY)\"
 CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
 CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"
endif

include $(RIOTBASE)/Makefile.include
