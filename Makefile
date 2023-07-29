-include Makefile.include

APPLICATION = blinken
BOARD ?= native

EXTERNAL_BOARD_DIRS += $(CURDIR)/boards

USEMODULE += apa102
USEMODULE += color
USEMODULE += periph_pwm
USEMODULE += ztimer_usec

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
