#include "board.h"
#include "board_config.h"
#include "drv_board.h"
#include "printf.h"

void user_main(void)
{
    board_init();

    while (1) {
        drv_gpio_toggle(LED_INSTANCE);
        HAL_Delay(1000);
        printf("123\r\n");
    }
}
