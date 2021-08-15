#include "uart_processes.hpp"

extern ADBMS1818Class adbms;
extern ina238 ina;
namespace huart{
   
    void init_tasks(){
        commands_list.insert(std::pair<char*, std::function<void()>>("gd", start_transmitting));
        is_transmiting = false;
    }

    void start_transmitting(){
        if(!is_transmiting){
            is_transmiting = true;
            transmitting_task = lv_timer_create(transmit_data, 2000, NULL);
        }
    }
    
    
    void interpret_command(char *command){
        try{
            std::function<void()> task = commands_list.at(command);
            task();
        }catch (const std::out_of_range& e){
            uart_write_bytes(UART_NUM_0, e.what(), strlen(e.what()));
        }
        
    }

    void transmit_data(lv_timer_t *timer){

    }
};