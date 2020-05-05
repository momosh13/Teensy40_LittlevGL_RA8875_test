#include <lvgl.h>
#include <SPI.h>
#include <RA8875.h>
#include <Wire.h>
#include <FT5206.h>

LV_FONT_DECLARE(rubo_50);

#define RA8875_CS 10 
#define RA8875_RESET 9
#define CTP_INT  4

RA8875 display = RA8875(RA8875_CS, RA8875_RESET);

#define LVGL_TICK_PERIOD 10

//#define WAKE 4
//#define INTRPT 15

FT5206 cts = FT5206(CTP_INT);


int screenWidth = 800;
int screenHeight = 480;

uint8_t registers[FT5206_REGISTERS];
uint16_t new_coordinates[5][2];
uint8_t current_touches = 0;

int oldTouchX = 0;
int oldTouchY = 0;

volatile uint32_t count = 0;
IntervalTimer TX_timer;
IntervalTimer tick;

int BL = 13;



  //###################################################################

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 40];

void create_tab1(lv_obj_t * parent);
void create_tab2(lv_obj_t * parent);
void create_tab3(lv_obj_t * parent);

lv_obj_t * slider_label;
int slider_value = 0;

  //#####################  Serial debugging  //#########################
  
//void my_print(lv_log_level_t level, const char * file, uint32_t line, const char * dsc)
//{
//}

static void lv_tick_handler(void)
{
  lv_tick_inc(LVGL_TICK_PERIOD);
}



    //######################### Touch  #############################

bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
  uint16_t touchX, touchY;

    if (cts.touched()){
      //uint16_t x,y;  
      cts.getTSregisters(registers);
      current_touches = cts.getTScoordinates(new_coordinates, registers); 

    touchX = new_coordinates[0][0];
    touchY = new_coordinates[0][1];
    //touchY = 480-touchY;
    Serial.print("X= ");
    Serial.print(touchX);
    Serial.print(" Y= ");
    Serial.println(touchY); 

    if ((touchX != oldTouchX) || (touchY != oldTouchY))
        {
   
            oldTouchY = touchY;
            oldTouchX = touchX;
               data->state = LV_INDEV_STATE_PR; 
             //  data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
                data->point.x = touchX;
                data->point.y = touchY;
     
        }
  } else
      {
        
        data->point.x = oldTouchX;
        data->point.y = oldTouchY;
        data->state =LV_INDEV_STATE_REL;
      } 
  return 0;
}

  //#################### Display flushing ########################
  
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{ 

  display.writeRect(area->x1, area->y1, area->x2 - area->x1 +1, area->y2 - area->y1+1, (uint16_t *)color_p);

  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
  
}











    
