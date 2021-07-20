#include "gui_renders.hpp"


namespace gui{
    void init_button(lv_obj_t *button, lv_style_t *style, lv_style_t *style_pr, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h){                                                                                                                                            
        lv_obj_add_style(button, style, LV_STATE_DEFAULT);
        lv_obj_add_style(button, style_pr, LV_STATE_PRESSED);
        lv_obj_set_grid_cell(button, LV_GRID_ALIGN_STRETCH, x, w, LV_GRID_ALIGN_STRETCH, y, h);
    }

    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text){
        label = lv_label_create(parent);
        lv_obj_remove_style_all(label);
        lv_label_set_text(label, text);
    }

    void init_cont(lv_obj_t *cont, lv_style_t *style, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h){
        lv_obj_add_style(cont, style, LV_STATE_DEFAULT);
        lv_obj_set_grid_cell(cont, LV_GRID_ALIGN_STRETCH, x, w, LV_GRID_ALIGN_STRETCH, y, h);
    }

    void init_grid(lv_obj_t *cont, const lv_coord_t col[], const lv_coord_t rows[], lv_coord_t w, lv_coord_t h){
        lv_obj_set_grid_align(cont, LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_END);
        lv_obj_set_grid_dsc_array(cont, col, rows);
        lv_obj_set_size(cont, w, h);
        lv_obj_center(cont);
    }
};