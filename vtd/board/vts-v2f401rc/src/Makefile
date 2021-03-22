

-include $(TOPDIR)/Make.defs

ASRCS =
CSRCS = stm32_appinit.c stm32_boot.c
#stm32_spi.c

ifeq ($(CONFIG_DEV_GPIO),y)
  CSRCS += stm32_gpio.c
endif

ifeq ($(CONFIG_MODEM_SIM868),y)
  CSRCS += stm32_sim868.c
endif

ifeq ($(CONFIG_GPS_SIM68),y)
  CSRCS += stm32_sim68.c
endif

ifeq ($(CONFIG_ENGINE_SENSOR),y)
  CSRCS += vts_engine.c
endif

ifeq ($(CONFIG_PANIC_SENSOR),y)
  CSRCS += vts_panic.c
endif

ifeq ($(CONFIG_AC_SENSOR),y)
  CSRCS += vts_ac.c
endif

ifeq ($(CONFIG_LOUDHORN),y)
  CSRCS += vts_loudhorn.c
endif

ifeq ($(CONFIG_BATTERY_SENSOR),y)
  CSRCS += vts_battery.c
endif

ifeq ($(CONFIG_BATTERY_CHARGER),y)
  CSRCS += stm32_battery_charger.c
endif

include $(TOPDIR)/configs/Board.mk
