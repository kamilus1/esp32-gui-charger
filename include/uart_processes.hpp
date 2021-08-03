#include "driver/uart.h"
#include "ina238.hpp"
#include "ADBMS1818Class.hpp"
#include <lvgl.h>
#include <map>

namespace huart{
    lv_timer_t *task1;
    const std::map<std::string, uint8_t> tasks_commands;

    void init_tasks();


};