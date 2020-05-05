void setup() {

  //ledcSetup(10, 5000/*freq*/, 10 /*resolution*/);
  //ledcAttachPin(18, 10);
  //analogReadResolution(10);
  //ledcWrite(10,BL);
  //pinMode(B, OUTPUT);
  //digitalWrite(B, HIGH);
  Serial.begin(115200); /* prepare for possible serial debug */

 
  display.begin(RA8875_800x480);
  cts.begin();

//Serial.println("RA8875 start"); 
 lv_init();
    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 40);
    
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
    indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
    lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/

  //#################################  Set the theme  #########################################

  
  lv_theme_t * th = lv_theme_night_init(210, NULL);     //Set a HUE value and a Font for the Night Theme
  lv_theme_set_current(th);

  lv_obj_t * scr = lv_cont_create(NULL, NULL);
  lv_disp_load_scr(scr);



  static lv_style_t style1; 
  lv_style_copy(&style1, &lv_style_plain);
  style1.text.color = LV_COLOR_YELLOW;
  style1.text.font = &rubo_50;

      static lv_style_t rel;
    lv_style_copy(&rel, &lv_style_btn_tgl_rel);
    rel.body.main_color = LV_COLOR_RED;
    rel.body.grad_color = LV_COLOR_BLACK;
    rel.text.color = LV_COLOR_WHITE;
    rel.text.font = &rubo_50;
    

    static lv_style_t pr;
    lv_style_copy(&pr, &lv_style_btn_tgl_pr);
    pr.body.main_color = LV_COLOR_YELLOW;
    pr.body.grad_color = LV_COLOR_BLACK;
    pr.text.color = LV_COLOR_WHITE;  
    pr.text.font = &rubo_50;

    lv_obj_t *tabview;
    tabview = lv_tabview_create(lv_scr_act(), NULL);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");


    /*Add content to the tabs*/
    lv_obj_t * label = lv_label_create(tab1, NULL);
  
  // Create simple label 
  //lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  //lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style1);
  lv_label_set_text(label, "Display Brighness");
  lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -50);

  // Create a slider in the center of the display 
  //lv_obj_t * slider = lv_slider_create(lv_scr_act(), NULL);
  lv_obj_t * slider = lv_slider_create(tab1, NULL);
  lv_obj_set_width(slider, screenWidth-50);                        //Set the width
  lv_obj_set_height(slider, 50);
  lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);    //Align to the center of the parent (screen)
  lv_obj_set_event_cb(slider, slider_event_cb);         //Assign an event function
  
  // Create a label below the slider 
  slider_label = lv_label_create(tab1, NULL);
  lv_label_set_style(slider_label, LV_LABEL_STYLE_MAIN, &style1);
  lv_label_set_text(slider_label, "0");
  lv_obj_set_auto_realign(slider, true);
  lv_obj_align(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  //lv_label_set_text(slider_label1, "%");
  //lv_obj_align(slider_label1, slider_label, LV_ALIGN_OUT_BOTTOM_MID, 10, 10);


    
static const char * btnm_map[] = {"1", "2", "3", "4", "\n",
                                  "5", "6", "7", "8", ""};

    lv_obj_t * btnm1 = lv_btnm_create(tab2, NULL);
    lv_btnm_set_map(btnm1, btnm_map);
    lv_obj_set_size(btnm1, 470, 220);   //Button size
    lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, -5, 0);
    lv_btnm_set_btn_ctrl_all(btnm1, LV_BTNM_CTRL_TGL_ENABLE);
    lv_btnm_set_one_toggle(btnm1, true);
    lv_obj_set_event_cb(btnm1, event_handler);
    
    lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_REL, &rel); //red
    lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_PR, &rel);  //red
    lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_TGL_REL, &pr); //yel
    lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_TGL_PR, &pr);  //yel

   

    label = lv_label_create(tab3, NULL);
    lv_label_set_text(label, "Third tab");  

//    lv_obj_t * ta = lv_ta_create(lv_disp_get_scr_act(NULL), NULL);
//    lv_obj_align(ta, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
//
//    /* Default object*/
//    lv_obj_t * kb1 = lv_kb_create(lv_disp_get_scr_act(NULL), NULL);
//    lv_obj_align(kb1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
//    lv_kb_set_ta(kb1, ta);

  tick.begin(lv_tick_handler, LVGL_TICK_PERIOD * 1000);  // Start tick timer
  Serial.println("tick.begin");
}
