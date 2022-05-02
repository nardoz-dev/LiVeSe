# name of your application
APPLICATION = LiVeSeMain

# If no BOARD is found in the environment, use this default:
BOARD ?=  nucleo-f401re  #native  b-l072z-lrwan1 iotlab-m3 

#CONTINUE_ON_EXPECTED_ERRORS=1


# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

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
#FEATURES_REQUIRED+= periph_i2c  



include $(RIOTBASE)/Makefile.include
