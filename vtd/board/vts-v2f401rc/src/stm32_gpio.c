

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/clock.h>
#include <nuttx/wdog.h>
#include <nuttx/ioexpander/gpio.h>

#include <arch/board/board.h>

#include "chip.h"
#include "stm32.h"
#include "vts-v2f401rc.h"

#if defined(CONFIG_DEV_GPIO) && !defined(CONFIG_GPIO_LOWER_HALF)

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct stm32gpio_dev_s
{
  struct gpio_dev_s gpio;
  uint8_t id;
};

struct stm32gpint_dev_s
{
  struct stm32gpio_dev_s stm32gpio;
  pin_interrupt_t callback;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int gpin_read(FAR struct gpio_dev_s *dev, FAR bool *value);
static int gpout_read(FAR struct gpio_dev_s *dev, FAR bool *value);
static int gpout_write(FAR struct gpio_dev_s *dev, bool value);
static int gpint_read(FAR struct gpio_dev_s *dev, FAR bool *value);
static int gpint_attach(FAR struct gpio_dev_s *dev,
                        pin_interrupt_t callback);
static int gpint_enable(FAR struct gpio_dev_s *dev, bool enable);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct gpio_operations_s gpin_ops =
{
  .go_read   = gpin_read,
  .go_write  = NULL,
  .go_attach = NULL,
  .go_enable = NULL,
};

static const struct gpio_operations_s gpout_ops =
{
  .go_read   = gpout_read,
  .go_write  = gpout_write,
  .go_attach = NULL,
  .go_enable = NULL,
};

static const struct gpio_operations_s gpint_ops =
{
  .go_read   = gpint_read,
  .go_write  = NULL,
  .go_attach = gpint_attach,
  .go_enable = gpint_enable,
};

#if BOARD_NGPIOIN > 0
/* This array maps the GPIO pins used as INPUT */

static const uint32_t g_gpioinputs[BOARD_NGPIOIN] =
{

};

static struct stm32gpio_dev_s g_gpin[BOARD_NGPIOIN];
#endif

#if BOARD_NGPIOOUT > 0
/* This array maps the GPIO pins used as OUTPUT */
static const uint32_t g_gpiooutputs[BOARD_NGPIOOUT] =
{
	UC_CE,
};

static struct stm32gpio_dev_s g_gpout[BOARD_NGPIOOUT];
#endif

#if BOARD_NGPIOINT > 0
/* This array maps the GPIO pins used as INTERRUPT INPUTS */

static const uint32_t g_gpiointinputs[BOARD_NGPIOINT] =
{

};

static struct stm32gpint_dev_s g_gpint[BOARD_NGPIOINT];
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int stm32gpio_interrupt(int irq, void *context, void *arg)
{
  FAR struct stm32gpint_dev_s *stm32gpint = (FAR struct stm32gpint_dev_s *)arg;

  DEBUGASSERT(stm32gpint != NULL && stm32gpint->callback != NULL);
  gpioinfo("Interrupt! callback=%p\n", stm32gpint->callback);

  stm32gpint->callback(&stm32gpint->stm32gpio.gpio);
  return OK;
}

static int gpin_read(FAR struct gpio_dev_s *dev, FAR bool *value)
{
  FAR struct stm32gpio_dev_s *stm32gpio = (FAR struct stm32gpio_dev_s *)dev;

  DEBUGASSERT(stm32gpio != NULL && value != NULL);
  DEBUGASSERT(stm32gpio->id < BOARD_NGPIOIN);
  gpioinfo("Reading...\n");

  *value = stm32_gpioread(g_gpioinputs[stm32gpio->id]);
  return OK;
}

static int gpout_read(FAR struct gpio_dev_s *dev, FAR bool *value)
{
  FAR struct stm32gpio_dev_s *stm32gpio = (FAR struct stm32gpio_dev_s *)dev;

  DEBUGASSERT(stm32gpio != NULL && value != NULL);
  DEBUGASSERT(stm32gpio->id < BOARD_NGPIOOUT);
  gpioinfo("Reading...\n");

  *value = stm32_gpioread(g_gpiooutputs[stm32gpio->id]);
  return OK;
}

static int gpout_write(FAR struct gpio_dev_s *dev, bool value)
{
  FAR struct stm32gpio_dev_s *stm32gpio = (FAR struct stm32gpio_dev_s *)dev;

  DEBUGASSERT(stm32gpio != NULL);
  DEBUGASSERT(stm32gpio->id < BOARD_NGPIOOUT);
  gpioinfo("Writing %d\n", (int)value);

  //vts debug purpose

  stm32_gpiowrite(g_gpiooutputs[stm32gpio->id], value);
  return OK;
}

static int gpint_read(FAR struct gpio_dev_s *dev, FAR bool *value)
{
  FAR struct stm32gpint_dev_s *stm32gpint = (FAR struct stm32gpint_dev_s *)dev;

  DEBUGASSERT(stm32gpint != NULL && value != NULL);
 // DEBUGASSERT(stm32gpint->stm32gpio && stm32gpint->stm32gpio.id < BOARD_NGPIOINT);
  gpioinfo("Reading int pin...\n");

  *value = stm32_gpioread(g_gpiointinputs[stm32gpint->stm32gpio.id]);
  return OK;
}

static int gpint_attach(FAR struct gpio_dev_s *dev,
                        pin_interrupt_t callback)
{
  FAR struct stm32gpint_dev_s *stm32gpint = (FAR struct stm32gpint_dev_s *)dev;

  gpioinfo("Attaching the callback\n");

  /* Make sure the interrupt is disabled */

  (void)stm32_gpiosetevent(g_gpiointinputs[stm32gpint->stm32gpio.id], false,
                           false, false, NULL, NULL);

  gpioinfo("Attach %p\n", callback);
  stm32gpint->callback = callback;
  return OK;
}

static int gpint_enable(FAR struct gpio_dev_s *dev, bool enable)
{
  FAR struct stm32gpint_dev_s *stm32gpint = (FAR struct stm32gpint_dev_s *)dev;

  if (enable)
    {
      if (stm32gpint->callback != NULL)
        {
          gpioinfo("Enabling the interrupt\n");

          /* Configure the interrupt for rising edge */

          (void)stm32_gpiosetevent(g_gpiointinputs[stm32gpint->stm32gpio.id],
                                   true, false, false, stm32gpio_interrupt,
                                   &g_gpint[stm32gpint->stm32gpio.id]);

        }
    }
  else
    {
      gpioinfo("Disable the interrupt\n");
      (void)stm32_gpiosetevent(g_gpiointinputs[stm32gpint->stm32gpio.id],
                               false, false, false, NULL, NULL);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_gpio_initialize
 *
 * Description:
 *   Initialize GPIO drivers for use with /apps/examples/gpio
 *
 ****************************************************************************/

int stm32_gpio_initialize(void)
{
  int i;
  int pincount = 0;

#if BOARD_NGPIOIN > 0
  for (i = 0; i < BOARD_NGPIOIN; i++)
    {
      /* Setup and register the GPIO pin */

      g_gpin[i].gpio.gp_pintype = GPIO_INPUT_PIN;
      g_gpin[i].gpio.gp_ops     = &gpin_ops;
      g_gpin[i].id              = i;
      (void)gpio_pin_register(&g_gpin[i].gpio, pincount);

      /* Configure the pin that will be used as input */

      stm32_configgpio(g_gpioinputs[i]);

      pincount++;
    }
#endif

#if BOARD_NGPIOOUT > 0
  for (i = 0; i < BOARD_NGPIOOUT; i++)
    {
      /* Setup and register the GPIO pin */

      g_gpout[i].gpio.gp_pintype = GPIO_OUTPUT_PIN;
      g_gpout[i].gpio.gp_ops     = &gpout_ops;
      g_gpout[i].id              = i;
      (void)gpio_pin_register(&g_gpout[i].gpio, pincount);

      /* Configure the pin that will be used as output */
      stm32_gpiowrite(g_gpiooutputs[i], 0);
      stm32_configgpio(g_gpiooutputs[i]);

      pincount++;
    }
#endif


#if BOARD_NGPIOINT > 0
/*
  for (i = 0; i < BOARD_NGPIOINT; i++)
    {
      // Setup and register the GPIO pin

      g_gpint[i].stm32gpio.gpio.gp_pintype = GPIO_INTERRUPT_PIN;
      g_gpint[i].stm32gpio.gpio.gp_ops     = &gpint_ops;
      g_gpint[i].stm32gpio.id              = i;
      (void)gpio_pin_register(&g_gpint[i].stm32gpio.gpio, pincount);

      // Configure the pin that will be used as interrupt input

      stm32_configgpio(g_gpiointinputs[i]);

      pincount++;
    }
  */
#endif

  return 0;
}
#endif /* CONFIG_DEV_GPIO && !CONFIG_GPIO_LOWER_HALF */
