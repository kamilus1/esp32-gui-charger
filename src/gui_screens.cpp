#include "gui_screens.hpp"
extern ADBMS1818Class adbms;
extern ina238 ina;

namespace gui{
    void init_styles(){
        init_main_scr_style();
        init_main_btn_style();
        init_main_btn_pr_style();
    }
    void init_main_scr_style(){
        lv_style_init(&main_screen_style);
        lv_style_set_bg_color(&main_screen_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_bg_grad_color(&main_screen_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_color(&main_screen_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_text_color(&main_screen_style, LV_COLOR_MAKE(224, 224, 224));
    }

    void init_main_btn_style(){
        for(uint8_t i=0;i<6;i++){
            lv_style_init(&main_buttons_styles[i]);
            lv_style_set_radius(&main_buttons_styles[i], 1);
            lv_style_set_text_color(&main_buttons_styles[i], LV_COLOR_MAKE(0x00, 0x00, 0x00));
            lv_style_set_bg_opa(&main_buttons_styles[i], LV_OPA_100);
            lv_style_set_bg_color(&main_buttons_styles[i], lv_palette_main(main_buttons_colors[i]));
            lv_style_set_bg_grad_color(&main_buttons_styles[i], lv_palette_darken(main_buttons_colors[i], 2));
            lv_style_set_bg_grad_dir(&main_buttons_styles[i], LV_GRAD_DIR_VER);

            lv_style_set_border_opa(&main_buttons_styles[i], LV_OPA_40);
            lv_style_set_border_width(&main_buttons_styles[i], 2);
            lv_style_set_border_color(&main_buttons_styles[i], LV_COLOR_MAKE(0xf0, 0xf0, 0xf0));
            lv_style_set_shadow_width(&main_buttons_styles[i], 0);
            lv_style_set_shadow_ofs_y(&main_buttons_styles[i], 0);

            lv_style_set_outline_opa(&main_buttons_styles[i], LV_OPA_COVER);
            lv_style_set_outline_color(&main_buttons_styles[i], lv_palette_main(main_buttons_colors[i]));
            lv_style_set_pad_all(&main_buttons_styles[i], 10);
        }
    }

    void init_main_btn_pr_style(){
        for(uint8_t i=0; i < 6 ; i++){
            lv_style_init(&main_buttons_pr_styles[i]);
            lv_style_set_outline_width(&main_buttons_pr_styles[i], 30);
            lv_style_set_outline_opa(&main_buttons_pr_styles[i], LV_OPA_TRANSP);

            lv_style_set_translate_y(&main_buttons_pr_styles[i], 5);
            lv_style_set_shadow_ofs_y(&main_buttons_pr_styles[i], 3);
            lv_style_set_bg_color(&main_buttons_pr_styles[i], lv_palette_darken(main_buttons_colors[i], 2));
            lv_style_set_bg_grad_color(&main_buttons_pr_styles[i], lv_palette_darken(main_buttons_colors[i], 4));

            /*Add a transition to the the outline*/
            static lv_style_transition_dsc_t trans;
            static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, (lv_style_prop_t)0};
            lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

            lv_style_set_transition(&main_buttons_pr_styles[i], &trans);
        }
    }


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
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {130, 130, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {100, 60, LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
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

        lv_obj_add_style(btn_rd, &main_buttons_styles[0], LV_STATE_DEFAULT);
        lv_obj_add_style(btn_rd, &main_buttons_pr_styles[0], LV_STATE_PRESSED);
        lv_obj_center(label_btn_rd);
        lv_obj_center(label_btn_cnv);
        lv_obj_center(label_cell_qnt);
        lv_obj_center(label_conv);
    }
    void init_start_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {95, 95, 95, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {70, 70, 30, 30, LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        lv_obj_t *buttons[6];
        lv_obj_t *label_buttons[6];
        std::vector<std::string> label_btns_text = {"CHARGE", "STORE", "DISCHARGE", "DATA", "CYCLE", "SETTINGS"};
        for(uint8_t i=0; i<6; i++){
            buttons[i] = lv_btn_create(cont);
            lv_obj_add_style(buttons[i], &main_buttons_styles[i], LV_STATE_DEFAULT);
            lv_obj_add_style(buttons[i], &main_buttons_pr_styles[i], LV_STATE_PRESSED);
            lv_obj_set_grid_cell(buttons[i], LV_GRID_ALIGN_STRETCH, (i%3), 1, LV_GRID_ALIGN_STRETCH, (i/3), 1);
            
            label_buttons[i] = lv_label_create(buttons[i]);
            lv_label_set_text(label_buttons[i], label_btns_text[i].c_str());
            lv_obj_set_style_text_font(label_buttons[i], &lv_font_montserrat_12, LV_STATE_DEFAULT);
            lv_obj_center(label_buttons[i]);
        }
    }



    void load_transition(){
        lv_scr_load(trans_scr);
        lv_obj_del(curr_scr);
    }
    void load_current(){
        
        lv_scr_load(curr_scr);
    }
};