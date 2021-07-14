#include "gui_renders.hpp"
#include "ADBMS1818Class.hpp"
#include "ina238.hpp"
#include <cstring>

namespace gui{
    static void conversion_handler(lv_event_t *e);
    static void total_cells_handler(lv_event_t *e);


    static lv_obj_t *curr_scr;
    static lv_obj_t *trans_scr;
    static lv_obj_t *label_conv;
    static lv_obj_t *label_cell_qnt;
    void init_demo_screen();
    void load_transition();
    void load_current();

};