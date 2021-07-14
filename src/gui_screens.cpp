#include "gui_screens.hpp"
extern ADBMS1818Class adbms;
extern ina238 ina;

namespace gui{
    static void conversion_handler(lv_event_t *e){
        lv_event_code_t code = lv_event_get_code(e);
        if(code == LV_EVENT_CLICKED){
            adbms.start_cv_sc_conversion();
            if(adbms.pladc_rdy()){
                lv_label_set_text(label_conv, "Conversion done!");
            }else{
                lv_label_set_text(label_conv, "Conversion not done!");
            }
        }
    }
    static void total_cells_handler(lv_event_t *e){
        lv_event_code_t code = lv_event_get_code(e);
        if(code == LV_EVENT_CLICKED){
            adbms.cell_detect();
            int i = (int)adbms.get_tot_cell_qnt();
            lv_label_set_text_fmt(label_cell_qnt, "Cells detected: %d", i);
        }
    }


    void init_transition_screen(){
        trans_scr = lv_obj_create(NULL);
    }
    void init_demo_screen(){
        curr_scr = lv_obj_create(NULL);
        static lv_coord_t col_dsc[] = {130, 130, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {100, 60, LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        lv_obj_set_grid_align(cont, LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_END);
        lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
        lv_obj_set_size(cont, 310, 220);
        lv_obj_center(cont);
        lv_obj_t *obj_cnv = lv_obj_create(cont); //containers of output text
        lv_obj_t *obj_rd = lv_obj_create(cont);

        lv_obj_t *btn_rd = lv_btn_create(cont);
        lv_obj_t *btn_cnv = lv_btn_create(cont);
        lv_obj_set_grid_cell(obj_rd, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
        lv_obj_set_grid_cell(obj_cnv, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

        lv_obj_set_grid_cell(btn_rd, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
        lv_obj_set_grid_cell(btn_cnv, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
        lv_obj_add_event_cb(btn_cnv, conversion_handler, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(btn_rd, total_cells_handler, LV_EVENT_ALL, NULL);

        label_cell_qnt = lv_label_create(obj_rd);
        label_conv = lv_label_create(obj_cnv);
        lv_label_set_long_mode(label_cell_qnt, LV_LABEL_LONG_WRAP);
        lv_label_set_long_mode(label_conv, LV_LABEL_LONG_WRAP);
        
        lv_obj_t *label_btn_rd = lv_label_create(btn_rd);
        lv_obj_t *label_btn_cnv = lv_label_create(btn_cnv);
        lv_label_set_text(label_btn_rd, "Total cells");
        lv_label_set_text(label_btn_cnv, "SC Conv");
        lv_label_set_text(label_cell_qnt, "Cells detected: 0");
        lv_label_set_text(label_conv, "Conversion not done!");
        lv_obj_center(label_btn_rd);
        lv_obj_center(label_btn_cnv);
        lv_obj_center(label_cell_qnt);
        lv_obj_center(label_conv);
    }
    void load_transition(){
        lv_scr_load(trans_scr);
        lv_obj_del(curr_scr);
    }
    void load_current(){
        
        lv_scr_load(curr_scr);
    }
};