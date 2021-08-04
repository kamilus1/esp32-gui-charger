#include "driver/uart.h"
#include "ina238.hpp"
#include "ADBMS1818Class.hpp"
#include <lvgl.h>
#include <map>

namespace huart{
    lv_timer_t *transmitting_task;
    bool is_transmiting;
    const char *commands_list[7] {"gd", "sd", "st", "str", "shp", "sp", "ht"};

    void init_tasks();
    void start_transmitting();

};