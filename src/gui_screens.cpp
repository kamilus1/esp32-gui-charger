#include "gui_screens.hpp"
extern ADBMS1818Class adbms;
extern ina238 ina;

namespace gui{
    void init_styles(){
        state = 1;
        tot_cell_qnt = 0;
        sum_cell_volt = 0.0;
        temperature = 0;
        input_voltage = 0;
        max_power = 0;
        init_main_scr_style();
        init_main_btn_style();
        init_main_btn_pr_style();
        init_prc_lbl_style();
        init_info_cnt_style();
        init_basic_label_style();
        init_error_label_style();
    }
    void init_main_scr_style(){
        lv_style_init(&main_screen_style);
        lv_style_set_bg_color(&main_screen_style, LV_COLOR_MAKE(0, 0, 0));
        lv_style_set_bg_grad_color(&main_screen_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_width(&main_screen_style, 0);    //Serg
        lv_style_set_border_color(&main_screen_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));   //Serg add
        lv_style_set_text_color(&main_screen_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_pad_all(&main_screen_style, 0);    //Serg. padding all(0)
        lv_style_set_pad_gap(&main_screen_style, 5);    //Serg. padding_gap(5)
    }

    void init_main_btn_style(){
        for(uint8_t i=0;i<6;i++){
            lv_style_init(&main_buttons_styles[i]);
            lv_style_set_radius(&main_buttons_styles[i], 0);
            lv_style_set_text_color(&main_buttons_styles[i], LV_COLOR_MAKE(0x00, 0x00, 0x00));
            lv_style_set_bg_opa(&main_buttons_styles[i], LV_OPA_100);
            lv_style_set_bg_color(&main_buttons_styles[i], main_buttons_colors[i]);
            /*
            lv_style_set_bg_grad_color(&main_buttons_styles[i], main_buttons_colors[i]);
            lv_style_set_bg_grad_dir(&main_buttons_styles[i], LV_GRAD_DIR_VER);
            lv_style_set_border_opa(&main_buttons_styles[i], LV_OPA_40);
            lv_style_set_border_width(&main_buttons_styles[i], 2);
            lv_style_set_border_color(&main_buttons_styles[i], LV_COLOR_MAKE(0xf0, 0xf0, 0xf0));
            */
            lv_style_set_shadow_width(&main_buttons_styles[i], 0);
            lv_style_set_shadow_ofs_y(&main_buttons_styles[i], 0);

            lv_style_set_outline_opa(&main_buttons_styles[i], LV_OPA_COVER);
            lv_style_set_outline_color(&main_buttons_styles[i], main_buttons_colors[i]);
            lv_style_set_pad_all(&main_buttons_styles[i], 10);
        }
    }

    void init_main_btn_pr_style(){
        for(uint8_t i=0; i < 6 ; i++){
            lv_style_init(&main_buttons_pr_styles[i]);
            lv_style_set_outline_width(&main_buttons_pr_styles[i], 5);
            lv_style_set_outline_opa(&main_buttons_pr_styles[i], LV_OPA_TRANSP);

            lv_style_set_translate_y(&main_buttons_pr_styles[i], 4);
            lv_style_set_shadow_ofs_y(&main_buttons_pr_styles[i], 3);
            
            //lv_style_set_bg_color(&main_buttons_pr_styles[i], main_buttons_colors[i]);
            //lv_style_set_bg_grad_color(&main_buttons_pr_styles[i], lv_palette_darken(main_buttons_colors[i], 4));

            /*Add a transition to the the outline*/
            static lv_style_transition_dsc_t trans;
            static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, (lv_style_prop_t)0};
            lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

            lv_style_set_transition(&main_buttons_pr_styles[i], &trans);
        }
    }

    void init_prc_lbl_style(){
        lv_style_init(&process_label_style);
        lv_style_set_text_color(&process_label_style, lv_palette_main(LV_PALETTE_YELLOW));
        lv_style_set_bg_color(&process_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_color(&process_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_bg_grad_color(&process_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
    }
    void init_info_cnt_style(){
        lv_style_init(&info_cont_style);
        lv_style_set_radius(&info_cont_style, 0);
        lv_style_set_bg_color(&info_cont_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_bg_grad_color(&info_cont_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_border_color(&info_cont_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_side(&info_cont_style, LV_BORDER_SIDE_BOTTOM);
        lv_style_set_border_width(&info_cont_style, 1);
        lv_style_set_text_color(&info_cont_style, LV_COLOR_MAKE(224, 224, 224));
    }

    void init_basic_label_style(){
        lv_style_init(&basic_label_style);
        lv_style_set_bg_color(&basic_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_bg_grad_color(&basic_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_text_color(&basic_label_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_width(&basic_label_style, 0);
    }

    void init_error_label_style(){
        lv_style_init(&error_label_style);
        lv_style_set_bg_color(&error_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_bg_grad_color(&error_label_style, LV_COLOR_MAKE(0x00, 0x00, 0x00));
        lv_style_set_text_color(&error_label_style, lv_palette_main(LV_PALETTE_RED));
        lv_style_set_border_width(&error_label_style, 0);
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

    static void charge_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen();
            load_current();
        }
        
    }
    static void store_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(STORE_PROCESS);
            load_current();
        }
    }
    static void disch_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(DISCHARGE_PROCESS);
            load_current();
        }
    }
    static void cycle_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(CYCLE_PROCESS);
            load_current();
        }
    }

    static void process_back_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 1;
            load_transition();
            init_start_screen();
            load_current();
        }
    }


    void init_transition_screen(){
        trans_scr = lv_obj_create(NULL);
        lv_obj_add_style(trans_scr, &main_screen_style, LV_STATE_DEFAULT);
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
        //grid
        static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST}; 
        static lv_coord_t row_dsc[] = {80, 80, LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST}; 
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        //container with info about amount of liion batteries connected
        lv_obj_t *info_qnt_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_qnt_cont);
        init_cont(info_qnt_cont, &info_cont_style, 0, 2, 3);
        label_cell_qnt = lv_label_create(info_qnt_cont);
        lv_label_set_text_fmt(label_cell_qnt, "%u-s Li-Ion Battery Detected", tot_cell_qnt);
        lv_obj_set_style_text_font(label_cell_qnt, &lv_font_montserrat_22, LV_STATE_DEFAULT);
        lv_obj_align(label_cell_qnt, LV_ALIGN_LEFT_MID, 5, 0);
        //container with info about temp and voltage.
        lv_obj_t *info_temp_volt_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_temp_volt_cont);
        init_cont(info_temp_volt_cont, &basic_label_style, 1, 3, 2);
        label_cell_volt_temp = lv_label_create(info_temp_volt_cont);
        lv_obj_set_style_text_font(label_cell_volt_temp, &lv_font_montserrat_22, LV_STATE_DEFAULT);
        lv_label_set_text_fmt(label_cell_volt_temp, "%d°C   %.1f V", temperature, sum_cell_volt);
        lv_obj_align(label_cell_volt_temp, LV_ALIGN_RIGHT_MID, -5, 0);
        //container with info about input electricity
        lv_obj_t *info_input_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_input_cont);
        init_cont(info_input_cont, &error_label_style, 0, 3);
        label_input_electricity = lv_label_create(info_input_cont);
        lv_obj_set_style_text_font(label_input_electricity, &lv_font_montserrat_12, LV_STATE_DEFAULT);
        lv_label_set_text_fmt(label_input_electricity, "DC Input: %.1f\nMax Power: %d", input_voltage, max_power);

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
        lv_obj_add_event_cb(buttons[0], charge_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[1], store_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[2], disch_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[4], cycle_scr_switch_handler, LV_EVENT_CLICKED, NULL);
    }

    void init_process_screen(uint8_t process_type){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {70, 70, 70, 70,  LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 25, 25, 25, 25, 25, 25,  LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        std::vector<std::string> process = {"CHARGE", "STORE", "DISCHG", "CYCLE"};
        std::vector<std::string> process_info = {"CURRENT", "CUT TEMP", "MAX.CAPACITY", "SAFETY TIMER", "BALANCE dVmin"};
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *start_btn = lv_btn_create(cont);
        lv_obj_t *process_cont = lv_obj_create(cont);
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(process_cont);
        lv_obj_remove_style_all(info_cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 6);
        init_button(start_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 3, 6);
        init_cont(process_cont, &process_label_style, 2, 6);
        init_cont(info_cont, &info_cont_style, 0, 0, 4);
        lv_obj_add_event_cb(back_btn, process_back_handler, LV_EVENT_CLICKED, NULL);
        
        lv_obj_t *label_back_btn = lv_label_create(back_btn);
        lv_obj_t *label_start_btn = lv_label_create(start_btn);
        lv_obj_t *label_process = lv_label_create(process_cont);
        
        lv_obj_set_style_text_font(label_process, &lv_font_montserrat_14, LV_STATE_DEFAULT);

        lv_label_set_text(label_back_btn, "BACK");
        lv_label_set_text(label_start_btn, "START");
        lv_label_set_text(label_process, process[process_type].c_str());
        lv_obj_center(label_back_btn);
        lv_obj_center(label_start_btn);
        lv_obj_center(label_process);
    }



    void load_transition(){
        lv_scr_load(trans_scr);
        lv_obj_del(curr_scr);
    }
    void load_current(){
        lv_scr_load(curr_scr);
    }

    void adbms_start_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            input_voltage = ina.read_voltage();
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
            input_voltage = 0;
        }
        max_power = input_voltage * MAX_CURRENT;
        lv_label_set_text_fmt(label_cell_qnt, "%u-s Li-Ion Battery Detected", tot_cell_qnt);
        lv_label_set_text_fmt(label_cell_volt_temp, "%d°C   %.1f V", temperature, sum_cell_volt);
        lv_label_set_text_fmt(label_input_electricity, "DC Input: %.1f\nMax Power: %d", input_voltage, max_power);
    }

    void init_adbms_task(){
        adbms_read = lv_timer_create(adbms_start_scr_read, ADBMS_READ_PERIOD, NULL);
    }
};