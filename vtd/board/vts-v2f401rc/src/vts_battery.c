

#include <nuttx/config.h>

#include <errno.h>
#include <debug.h>

#include <nuttx/board.h>
#include <nuttx/analog/adc.h>
#include <arch/board/board.h>

#include "chip.h"
#include "up_arch.h"

#include "stm32_pwm.h"
#include "vts-v2f401rc.h"

#ifdef CONFIG_STM32_ADC1

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/* The number of ADC channels in the conversion list */


#define ADC1_NCHANNELS 1


static const uint8_t  g_adc1_chanlist[ADC1_NCHANNELS] = {0};

/* Configurations of pins used byte each ADC channels */

static const uint32_t g_adc1_pinlist[ADC1_NCHANNELS]  = {GPIO_ADC1_IN13};


/************************************************************************************
 * Public Functions
 ************************************************************************************/

/************************************************************************************
 * Name: stm32_adc_setup
 *
 * Description:
 *   Initialize ADC and register the ADC driver.
 *
 ************************************************************************************/

int vts_battery_init(void)
{
  struct adc_dev_s *adc;
  int ret;
  int i;

  /* Configure the pins as analog inputs for the selected channels */

  for (i = 0; i < ADC1_NCHANNELS; i++)
    {
      stm32_configgpio(g_adc1_pinlist[i]);
    }

  /* Call stm32_adcinitialize() to get an instance of the ADC interface */

  adc = stm32_adcinitialize(1, g_adc1_chanlist, ADC1_NCHANNELS);
  if (adc == NULL)
    {
      aerr("ERROR: Failed to get ADC interface\n");
      return -ENODEV;
    }

  /* Register the ADC driver at "/dev/adc0" */

  ret = adc_register("/dev/battery", adc);
  if (ret < 0)
    {
      aerr("ERROR: adc_register failed: %d\n", ret);
      return ret;
    }

  return OK;
}

#endif /* CONFIG_STM32_ADC1 */
