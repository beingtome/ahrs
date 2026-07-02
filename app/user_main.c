#include "board.h"
#include "board_config.h"
#include "drv_board.h"
#include "shell_port.h"

void user_main(void)
{
    board_init();

    shell_init();
    while (1) {
        shell_task();
    }
}
