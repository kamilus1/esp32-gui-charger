#include "driver/uart.h"
#include "ina238.hpp"
#include "ADBMS1818Class.hpp"
#include <lvgl.h>
#include <map>
#include <string.h>
#include <functional>

namespace huart{
    lv_timer_t *transmitting_task;
    static bool is_transmiting;
    static std::map<char*, std::function<void()>> commands_list;

    void init_tasks();
    void start_transmitting();
    static void transmit_data(lv_timer_t *timer);
    void interpret_command(char *command);
};