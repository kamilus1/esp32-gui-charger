#include "gui_styles.hpp"

namespace gui{
    void init_styles(){
        init_button_pr_style();
        init_button_style();
        init_button_tr_style();
    }
    void init_button_style(){
        lv_style_init(&button_style);

        lv_style_set_radius(&button_style, 3);

        lv_style_set_bg_opa(&button_style, LV_OPA_100);
        lv_style_set_bg_color(&button_style, lv_palette_main(LV_PALETTE_BLUE));
        lv_style_set_bg_grad_color(&button_style, lv_palette_darken(LV_PALETTE_BLUE, 2));
        lv_style_set_bg_grad_dir(&button_style, LV_GRAD_DIR_VER);

        lv_style_set_border_opa(&button_style, LV_OPA_40);
        lv_style_set_border_width(&button_style, 2);
        lv_style_set_border_color(&button_style, lv_palette_main(LV_PALETTE_GREY));

        lv_style_set_shadow_width(&button_style, 8);
        lv_style_set_shadow_color(&button_style, lv_palette_main(LV_PALETTE_GREY));
        lv_style_set_shadow_ofs_y(&button_style, 8);

        lv_style_set_outline_opa(&button_style, LV_OPA_COVER);
        lv_style_set_outline_color(&button_style, lv_palette_main(LV_PALETTE_BLUE));

        lv_style_set_text_color(&button_style, lv_color_white());
        lv_style_set_pad_all(&button_style, 10);
    }
    void init_button_pr_style(){
        lv_style_init(&button_pr_style);

        /*Ad a large outline when pressed*/
        lv_style_set_outline_width(&button_pr_style, 30);
        lv_style_set_outline_opa(&button_pr_style, LV_OPA_TRANSP);

        lv_style_set_translate_y(&button_pr_style, 5);
        lv_style_set_shadow_ofs_y(&button_pr_style, 3);
        lv_style_set_bg_color(&button_pr_style, lv_palette_darken(LV_PALETTE_BLUE, 2));
        lv_style_set_bg_grad_color(&button_pr_style, lv_palette_darken(LV_PALETTE_BLUE, 4));
    }
    void init_button_tr_style(){
        static lv_style_transition_dsc_t trans;
        static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA,(lv_style_prop_t) 0};
        lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);
        lv_style_set_transition(&button_pr_style, &trans);
    }

    

};