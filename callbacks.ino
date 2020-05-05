void printEvent(String Event, lv_event_t event)
{
  
 // Serial.print(Event);
 // printf(" ");

  switch(event) {
      case LV_EVENT_PRESSED:
          //printf("Pressed\n");
          break;

      case LV_EVENT_SHORT_CLICKED:
          //printf("Short clicked\n");
          break;

      case LV_EVENT_CLICKED:
         // printf("Clicked\n");

          break;

      case LV_EVENT_LONG_PRESSED:
          //printf("Long press\n");
          break;

      case LV_EVENT_LONG_PRESSED_REPEAT:
          //printf("Long press repeat\n");
          break;

      case LV_EVENT_RELEASED:
          //printf("Released\n");
          break;
  }
}

void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        const char * txt = lv_btnm_get_active_btn_text(obj);

        printf("%s was pressed\n", txt);

        
    }
}

void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{

  printEvent("Slider", event);

  if(event == LV_EVENT_VALUE_CHANGED) {
      static char buf[4];                                 /* max 3 bytes  for number plus 1 null terminating byte */
      snprintf(buf, 4, "%u", lv_slider_get_value(slider));
      lv_obj_align(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
      lv_label_set_text(slider_label, buf);               /*Refresh the text*/
      slider_value=lv_slider_get_value(slider);
      
      Serial.print("VALUE=");
      Serial.println(map(slider_value, 1, 100, 400, 800));
      BL= map(slider_value, 1, 100, 400, 800);
     // ledcWrite(10,BL);
  }
}
