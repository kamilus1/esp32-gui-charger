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
        process_type_selected = 0;
        data_type_selected = 0;
        current_adbms = 0;
        init_main_scr_style();
        init_main_btn_style();
        init_main_btn_pr_style();
        init_prc_lbl_style();
        init_info_cnt_style();
        init_basic_label_style();
        init_error_label_style();
        init_msg_box_style();
        init_msg_box_btn_style();
        init_bars_style();
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
       
        /*Make a gradient*/
        lv_style_set_bg_opa(&info_cont_style, LV_OPA_COVER);
        lv_style_set_bg_color(&info_cont_style, LV_COLOR_MAKE(0,0,0));
        lv_style_set_bg_grad_color(&info_cont_style, lv_color_darken(main_buttons_colors[0],100));
        lv_style_set_bg_grad_dir(&info_cont_style, LV_GRAD_DIR_VER);

        /*Shift the gradient to the bottom*/
        lv_style_set_bg_main_stop(&info_cont_style, 150);

        lv_style_set_text_color(&info_cont_style, LV_COLOR_MAKE(255, 255, 255));
    }

    void init_basic_label_style(){
        lv_style_init(&basic_label_style);
        lv_style_set_bg_opa(&error_label_style, LV_OPA_COVER);           
        lv_style_set_bg_grad_dir(&error_label_style, LV_GRAD_DIR_VER);
        lv_style_set_text_color(&basic_label_style, LV_COLOR_MAKE(255, 255, 255));
    }

    void init_error_label_style(){
        lv_style_init(&error_label_style);
        lv_style_set_text_color(&error_label_style, LV_COLOR_MAKE(255, 255, 255));
    }   
    void init_msg_box_style(){
        lv_style_init(&msg_box_style);
        lv_style_set_bg_color(&msg_box_style, LV_COLOR_MAKE(50, 50, 50));
        lv_style_set_border_color(&msg_box_style, LV_COLOR_MAKE(0xff, 0xff, 0xff));
        lv_style_set_text_color(&msg_box_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_radius(&msg_box_style, 0);
        lv_style_set_border_width(&msg_box_style, 3);
    }

    void init_msg_box_btn_style(){
        lv_style_init(&msg_box_btn_style);
        lv_style_set_bg_color(&msg_box_btn_style, LV_COLOR_MAKE(20, 20, 20));
        lv_style_set_border_color(&msg_box_btn_style, LV_COLOR_MAKE(0xff, 0xff, 0xff));
        lv_style_set_radius(&msg_box_btn_style, 0);
        lv_style_set_text_color(&msg_box_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_opa(&msg_box_btn_style, LV_OPA_50);
        lv_style_set_border_width(&msg_box_btn_style, 1);
        
    }

    void init_bars_style(){
        lv_style_init(&bar_style);
        lv_style_set_border_color(&bar_style, LV_COLOR_MAKE(224, 224, 224));
        lv_style_set_border_width(&bar_style, 2);
        lv_style_set_radius(&bar_style, 0);
        lv_style_set_pad_all(&bar_style, 0);
        lv_style_set_anim_time(&bar_style, 500);

        lv_style_init(&green_bar_style);
        lv_style_init(&red_bar_style);
        lv_style_init(&yellow_bar_style);

        lv_style_set_bg_opa(&green_bar_style, LV_OPA_COVER);
        lv_style_set_bg_opa(&red_bar_style, LV_OPA_COVER);
        lv_style_set_bg_opa(&yellow_bar_style, LV_OPA_COVER);

        lv_style_set_bg_color(&green_bar_style, main_buttons_colors[0]);
        lv_style_set_bg_color(&red_bar_style, main_buttons_colors[2]);
        lv_style_set_bg_color(&yellow_bar_style, main_buttons_colors[1]);

        lv_style_set_radius(&green_bar_style, 2);
        lv_style_set_radius(&red_bar_style, 2);
        lv_style_set_radius(&yellow_bar_style, 2);
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
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
        
    }
    static void store_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(STORE_PROCESS);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }
    static void disch_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(DISCHARGE_PROCESS);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }
    static void cycle_scr_switch_handler(lv_event_t *e){
        if(tot_cell_qnt > 0){
            state = 2;
            load_transition();
            init_process_screen(CYCLE_PROCESS);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }

    static void process_back_handler(lv_event_t *e){
        
        state = 1;
        load_transition();
        init_start_screen();
        load_current();
        lv_timer_set_cb(adbms_read, adbms_start_scr_read);
    }

    static void process_start_switch_handler(lv_event_t *e){
        state = 3;
        uint8_t *process_type = (uint8_t *) lv_event_get_user_data(e);
        load_transition();
        init_start_process_screen(*process_type);
        load_current();
        
            }

    static void process_stop_handler(lv_event_t *e){
        static const char * btns[] = {"YES", "NO", ""};
        lv_obj_t *stop_mbox = lv_msgbox_create(lv_scr_act(), "STOP", "Stop process?", btns, true);
        lv_obj_add_event_cb(stop_mbox, process_stop_msgbox_handler, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_add_style(stop_mbox, &msg_box_style, LV_STATE_DEFAULT);
        lv_obj_add_style(lv_msgbox_get_close_btn(stop_mbox), &main_buttons_styles[2], LV_STATE_DEFAULT);
        lv_obj_add_style(lv_msgbox_get_close_btn(stop_mbox), &main_buttons_pr_styles[2], LV_STATE_PRESSED);
        lv_obj_add_style(lv_msgbox_get_btns(stop_mbox), &msg_box_btn_style, LV_STATE_DEFAULT);
        lv_obj_center(stop_mbox);
    }

    static void process_stop_msgbox_handler(lv_event_t *e){
        lv_obj_t *obj = lv_event_get_current_target(e);
        if(!strcmp("YES", lv_msgbox_get_active_btn_text(obj))){
            lv_msgbox_close(obj);
            state = 1;
            load_transition();
            init_start_screen();
            load_current();
        }else{
            lv_msgbox_close(obj);
        }
    }

    static void data_next_adbms_handler(lv_event_t *e){
        if((current_adbms + 1) >= ADBMS_AMOUNT){
            current_adbms = 0;
        }else{
            current_adbms += 1;
        }
        
    }

    static void data_prev_adbms_handler(lv_event_t *e){
        if(current_adbms <= 0){
            current_adbms = (ADBMS_AMOUNT - 1);
        }else{
            current_adbms -= 1;
        }
        
    }

    static void data_start_switch_handler(lv_event_t *e){
        
        state = 4;
        data_type_selected = 0;
        load_transition();
        init_data_list_screen();
        load_current();
        lv_timer_set_cb(adbms_read, adbms_data_scr_read);
    }
    static void data_back_handler(lv_event_t *e){
        if(state == 4){
            
            state = 1;
            load_transition();
            init_start_screen();
            load_current();
            lv_timer_set_cb(adbms_read, adbms_start_scr_read);
        }else if(state == 3){
            
            load_transition();
            init_start_process_screen(process_type_selected);
            load_current();
            lv_timer_set_cb(adbms_read, adbms_process_scr_read);
        }
    }

    static void data_next_mode_handler(lv_event_t *e){
        switch(data_type_selected){
            case 0:
                data_type_selected += 1;
                load_transition();
                init_data_candles_screen();
                load_current();
                lv_timer_set_cb(adbms_read, adbms_data_candles_scr_read);
                break;
            case 1:
                data_type_selected += 1;
                load_transition();
                init_data_process_graph();
                load_current();
                lv_timer_set_cb(adbms_read, adbms_data_graph_scr_read);
                break;
            case 2:
                data_type_selected = 0;
                load_transition();
                init_data_list_screen();
                load_current();
                lv_timer_set_cb(adbms_read, adbms_data_scr_read);
                break;
            default:
                break;
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
        std::vector<std::string> label_btns_text = {"CHARGE", "STORE", "DISCHARGE", "DATA", "CYCLE", "SETTINGS"};
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        
        //start screen grid 
        static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST}; 
        static lv_coord_t row_dsc[] = {30, 80, 80, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST}; 
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        
        //container with number of Battery Pack cells detected
        lv_obj_t *info_qnt_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_qnt_cont);
        init_cont(info_qnt_cont, &info_cont_style, 0, 3, 3);    //BOTTOM center
        label_cell_qnt = lv_label_create(info_qnt_cont);
        lv_label_set_text_fmt(label_cell_qnt, "%u-s Battery Pack Detected", tot_cell_qnt);
        lv_obj_set_style_text_font(label_cell_qnt, &lv_font_montserrat_20, LV_STATE_DEFAULT);
        lv_obj_align(label_cell_qnt, LV_ALIGN_CENTER, 0, 0);
        
        //container with special_symbol
        lv_obj_t *wifi_symbol = lv_obj_create(cont);
        lv_obj_remove_style_all(wifi_symbol);
        init_cont(wifi_symbol, &basic_label_style, 1, 0, 1);    //TOP center
        label_special_symbol = lv_label_create(wifi_symbol);
        lv_label_set_text(label_special_symbol, LV_SYMBOL_WIFI);
        lv_obj_align(label_special_symbol, LV_ALIGN_CENTER, 0, 0);

        //container with info about temp and voltage.
        lv_obj_t *info_temp_volt_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_temp_volt_cont);
        init_cont(info_temp_volt_cont, &basic_label_style, 2, 0, 1);    //TOP right
        label_cell_volt_temp = lv_label_create(info_temp_volt_cont);
        lv_obj_set_style_text_font(label_cell_volt_temp, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_label_set_text_fmt(label_cell_volt_temp,"vBAT:  %.2f v\ntBAT:         %d°c", sum_cell_volt, temperature); // to define Battery's Temp, taken from LM35, applied on 1818's GPIO
        lv_obj_align(label_cell_volt_temp, LV_ALIGN_BOTTOM_LEFT, 0, 0);
        
        //container with info about input electricity
        lv_obj_t *info_input_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_input_cont);
        init_cont(info_input_cont, &error_label_style, 0, 0, 1);    //TOP left
        label_input_electricity = lv_label_create(info_input_cont);
        lv_obj_set_style_text_font(label_input_electricity, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_label_set_text_fmt(label_input_electricity, "INPUT:  %.1f v\ntCHG:     %d°c", input_voltage, temperature); // internal temp in charger, taken from INA
        lv_obj_align(label_input_electricity, LV_ALIGN_BOTTOM_LEFT, 0, 0);

        lv_obj_t *buttons[6];
        lv_obj_t *label_buttons[6];
        
        for(uint8_t i=0; i<6; i++){
            buttons[i] = lv_btn_create(cont);
            lv_obj_add_style(buttons[i], &main_buttons_styles[i], LV_STATE_DEFAULT);
            lv_obj_add_style(buttons[i], &main_buttons_pr_styles[i], LV_STATE_PRESSED);
            lv_obj_set_grid_cell(buttons[i], LV_GRID_ALIGN_STRETCH, (i%3), 1, LV_GRID_ALIGN_STRETCH, ((i+3)/3), 1);
            label_buttons[i] = lv_label_create(buttons[i]);
            lv_label_set_text(label_buttons[i], label_btns_text[i].c_str());
            lv_obj_set_style_text_font(label_buttons[i], &lv_font_montserrat_12, LV_STATE_DEFAULT);
            lv_obj_align(label_buttons[i], LV_ALIGN_BOTTOM_LEFT, -8, 10); 
        }
        lv_obj_add_event_cb(buttons[0], charge_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[1], store_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[2], disch_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[3], data_start_switch_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(buttons[4], cycle_scr_switch_handler, LV_EVENT_CLICKED, NULL);
        
    }

    void init_process_screen(uint8_t process_type){
        std::vector<std::string> process = {"CHARGE", "STORE", "DISCHG", "CYCLE"};
        std::vector<std::string> process_info = {"CURRENT", "CUT TEMP", "MAX.CAPACITY", "SAFETY TIMER", "BALANCE dVmin"};
        process_type_selected = process_type;
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {70, 70, 70, 70,  LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 25, 25, 25, 25, 25, 25,  LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 5);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *start_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 6);
        init_button(start_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 3, 6);
        lv_obj_add_event_cb(back_btn, process_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(start_btn, process_start_switch_handler, LV_EVENT_CLICKED, &process_type_selected);

        lv_obj_t *process_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(process_cont);
        init_cont(process_cont, &process_label_style, 2, 6);
        
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
    void init_start_process_screen(uint8_t process_type){
        std::vector<std::string> process = {"CHARGING IN PROGRESS", "STORING IN PROGRESS", 
        "DISCHARGING IN PROGRESS", "CYCLING IN PROGRESS"};

        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {60, 60, 60, 60, 60, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 30, 30, 30, 30, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 5);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //buttons
        lv_obj_t *stop_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        init_button(stop_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 5);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 4, 5);
        lv_obj_add_event_cb(stop_btn, process_stop_handler, LV_EVENT_CLICKED, NULL);
        //process cont
        lv_obj_t *process_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(process_cont);
        init_cont(process_cont, &process_label_style, 0, 1, 5);

        lv_obj_t *label_process = lv_label_create(process_cont);
        lv_obj_t *label_stop = lv_label_create(stop_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_set_style_text_font(label_process, &lv_font_montserrat_20, LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(label_stop, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(label_data, &lv_font_montserrat_14, LV_STATE_DEFAULT);
        lv_label_set_text(label_process, process[process_type].c_str());
        lv_label_set_text(label_stop, "STOP");
        lv_label_set_text(label_data, "DATA");
        lv_obj_center(label_process);
        lv_obj_center(label_stop);
        lv_obj_center(label_data);
    }

    void init_data_list_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {60, 60, 60, 60, 60, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 15, 15, 15, 15, 15, 15, 15, 15, 15, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
        //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 5);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //buttons
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        lv_obj_t *prev_btn = lv_btn_create(cont);
        lv_obj_t *next_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 10);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 4, 10);
        init_button(prev_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 1, 10);
        init_button(next_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 3, 10);
        lv_obj_add_event_cb(back_btn, data_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(next_btn, data_next_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(prev_btn, data_prev_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(data_btn, data_next_mode_handler, LV_EVENT_CLICKED, NULL);


        //button labels
        lv_obj_t *label_back = lv_label_create(back_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_t *label_prev = lv_label_create(prev_btn);
        lv_obj_t *label_next = lv_label_create(next_btn);
        
        lv_label_set_text(label_back, "BACK");
        lv_label_set_text(label_data, "DATA");
        lv_label_set_text(label_prev, LV_SYMBOL_LEFT);
        lv_label_set_text(label_next, LV_SYMBOL_RIGHT);

        lv_obj_center(label_back);
        lv_obj_center(label_data);
        lv_obj_center(label_prev);
        lv_obj_center(label_next);

        //cells data labels & containers;
        lv_obj_t *cells_voltage_conts[18];

        for(uint8_t i=0; i<18;i++){
            cells_voltage_conts[i] = lv_obj_create(cont);
            lv_obj_remove_style_all(cells_voltage_conts[i]);
            init_cont(cells_voltage_conts[i], &basic_label_style, (i/9)*2, 1+i%9, 2);
            label_cells_voltage[i] = lv_label_create(cells_voltage_conts[i]);
            lv_label_set_text_fmt(label_cells_voltage[i], "C%u: 0.000", (i+1));
            lv_obj_align(label_cells_voltage[i], LV_ALIGN_LEFT_MID, 1, 0);
        }
    }

    void init_data_candles_screen(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 20, 120, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
         //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 18);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //buttons;
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        lv_obj_t *prev_btn = lv_btn_create(cont);
        lv_obj_t *next_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 3, 4);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 14, 3, 4);
        init_button(prev_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 4, 3, 4);
        init_button(next_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 3, 3);
        lv_obj_add_event_cb(back_btn, data_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(next_btn, data_next_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(prev_btn, data_prev_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(data_btn, data_next_mode_handler, LV_EVENT_CLICKED, NULL);

        //button labels
        lv_obj_t *label_back = lv_label_create(back_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_t *label_prev = lv_label_create(prev_btn);
        lv_obj_t *label_next = lv_label_create(next_btn);
        
        lv_label_set_text(label_back, "BACK");
        lv_label_set_text(label_data, "DATA");
        lv_label_set_text(label_prev, LV_SYMBOL_LEFT);
        lv_label_set_text(label_next, LV_SYMBOL_RIGHT);

        lv_obj_center(label_back);
        lv_obj_center(label_data);
        lv_obj_center(label_prev);
        lv_obj_center(label_next);

        //candles containers

        lv_obj_t *candle_conts[18];
        lv_obj_t *label_conts[18];
        for(uint8_t i=0; i<18;i++){
            //candles
            candle_conts[i] = lv_obj_create(cont);
            init_cont(candle_conts[i], &basic_label_style, i, 2);
            bars_cells_voltage[i] = lv_bar_create(candle_conts[i]);
            init_bar(bars_cells_voltage[i], &green_bar_style, &bar_style);

            label_conts[i] = lv_obj_create(cont);
            init_cont(label_conts[i], &basic_label_style, i, 1);
            label_cells_voltage[i] = lv_label_create(label_conts[i]);
            lv_label_set_text(label_cells_voltage[i], "0.000");
            lv_obj_center(label_cells_voltage[i]);

        }
    }

    void init_data_process_graph(){
        curr_scr = lv_obj_create(NULL);
        lv_obj_add_style(curr_scr, &main_screen_style, LV_STATE_DEFAULT );
        static lv_coord_t col_dsc[] = {60, 60, 60, 60, 60, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {25, 140, 30,   LV_GRID_TEMPLATE_LAST};
        lv_obj_t *cont = lv_obj_create(curr_scr);
        init_grid(cont, col_dsc, row_dsc);
        lv_obj_add_style(cont, &main_screen_style, LV_STATE_DEFAULT);
         //info container
        lv_obj_t *info_cont = lv_obj_create(cont);
        lv_obj_remove_style_all(info_cont);
        init_cont(info_cont, &info_cont_style, 0, 0, 5);
        //info cont label
        label_info_cont = lv_label_create(info_cont);
        lv_obj_set_style_text_font(label_info_cont, &lv_font_montserrat_16, LV_STATE_DEFAULT);
        lv_label_set_text(label_info_cont, "0-S BAT DETECTED 0.0V 0°C");
        //buttons
        lv_obj_t *back_btn = lv_btn_create(cont);
        lv_obj_t *data_btn = lv_btn_create(cont);
        lv_obj_t *prev_btn = lv_btn_create(cont);
        lv_obj_t *next_btn = lv_btn_create(cont);
        init_button(back_btn, &main_buttons_styles[2], &main_buttons_pr_styles[2], 0, 2);
        init_button(data_btn, &main_buttons_styles[0], &main_buttons_pr_styles[0], 4, 2);
        init_button(prev_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 1, 2);
        init_button(next_btn, &main_buttons_styles[5], &main_buttons_pr_styles[5], 3, 2);
        lv_obj_add_event_cb(back_btn, data_back_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(next_btn, data_next_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(prev_btn, data_prev_adbms_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(data_btn, data_next_mode_handler, LV_EVENT_CLICKED, NULL);
        
        //button labels
        lv_obj_t *label_back = lv_label_create(back_btn);
        lv_obj_t *label_data = lv_label_create(data_btn);
        lv_obj_t *label_prev = lv_label_create(prev_btn);
        lv_obj_t *label_next = lv_label_create(next_btn);
        
        lv_label_set_text(label_back, "BACK");
        lv_label_set_text(label_data, "DATA");
        lv_label_set_text(label_prev, LV_SYMBOL_LEFT);
        lv_label_set_text(label_next, LV_SYMBOL_RIGHT);

        lv_obj_center(label_back);
        lv_obj_center(label_data);
        lv_obj_center(label_prev);
        lv_obj_center(label_next);
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
            lv_label_set_text_fmt(label_cell_qnt, "%u-s Battery Pack Detected", tot_cell_qnt);
            lv_label_set_text_fmt(label_cell_volt_temp,"vBAT:  %.2f v\ntBAT:         %d°c", sum_cell_volt, temperature); // to define Battery's Temp, taken from LM35, applied on 1818's GPIO
            lv_label_set_text_fmt(label_input_electricity, "INPUT:  %.1f v\ntCHG:     %d°c", input_voltage, temperature); // internal temp in charger, taken from INA
    }

    void adbms_data_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        cells_qnt = adbms.get_cell_qnt(current_adbms);
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        for(uint8_t i=0; i<cells_qnt;i++){
            lv_label_set_text_fmt(label_cells_voltage[i], "C%u: %.3f", (i+1), adbms.convert_voltage(adbms(current_adbms, i) ));
        }
        for(uint8_t i=cells_qnt; i<18;i++){
            lv_label_set_text_fmt(label_cells_voltage[i], "C%u 0.000", (i+1));
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
        
    }

    void adbms_data_candles_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        cells_qnt = adbms.get_cell_qnt(current_adbms);
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        for(uint8_t i=0; i<cells_qnt;i++){
            lv_label_set_text_fmt(label_cells_voltage[i],  "%.3f", adbms.convert_voltage(adbms(current_adbms, i)));
            lv_bar_set_value(bars_cells_voltage[i], adbms.voltage_percent(adbms.convert_voltage(adbms(current_adbms, i))), LV_ANIM_ON);
        }
        for(uint8_t i=cells_qnt; i<18;i++){
            lv_label_set_text(label_cells_voltage[i], "0.000");
            lv_bar_set_value(bars_cells_voltage[i], 0, LV_ANIM_OFF);
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
        
    }

    void adbms_data_graph_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
    }

    void adbms_process_scr_read(lv_timer_t *timer){
        adbms.cell_detect();
        tot_cell_qnt = adbms.get_tot_cell_qnt();
        sum_cell_volt = adbms.get_sum_cell_voltage();
        if(ina.device_found()){
            temperature = (int)ina.read_temperature();
        }else{
            temperature = 0;
        }
        lv_label_set_text_fmt(label_info_cont, "%u-s Battery detected %.1fV %d°c", tot_cell_qnt, sum_cell_volt, temperature);
    }

    void init_adbms_task(){
        adbms_read = lv_timer_create(adbms_start_scr_read, ADBMS_READ_PERIOD, NULL);
    }
};