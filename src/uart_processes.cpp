#include "uart_processes.hpp"

extern ADBMS1818Class adbms;
extern ina238 ina;
namespace huart{
    void init_tasks(){
        is_transmiting = false;
    }
};