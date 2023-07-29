#include <stdio.h>

#include "board.h"
#include "periph_conf.h"

#include "apa102.h"
#include "apa102_params.h"
#include "color.h"
#include "ztimer.h"
#include "periph/pwm.h"

int main(void) {
  if(pwm_init(PWM_DEV(0), PWM_LEFT, 1000, 255) == 0) {
    printf("failed to initialize PWM\n");
    return 2;
  }
  int red_led = 0;
  int delta = 1;

  apa102_t dotstar;
  apa102_init(&dotstar, &apa102_params[0]);
  color_hsv_t ds_color = { 0.0, 1.0, 1.0 };
  color_rgba_t ds_led = {{0, 0, 0}, 32};

  while(true) {
    red_led += delta;
    if(red_led == 64)
      delta = -1;
    else if(red_led == 0)
      delta = 1;
    pwm_set(PWM_DEV(0), 0, red_led);

    ds_color.h += 1.0;
    if(ds_color.h > 360.0)
      ds_color.h = 0.0;
    color_hsv2rgb(&ds_color, &ds_led.color);
    apa102_load_rgba(&dotstar, &ds_led);

    ztimer_sleep(ZTIMER_USEC, 20000);
  }

  return 0;
}
