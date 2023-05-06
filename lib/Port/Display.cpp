#include "Display.h"
#include "Config.h"
#include "FreeRTOS/FreeRTOS.h"
#include <stdint.h>
#include <Arduino.h>

#define DISP_HOR_RES 240
#define DISP_VER_RES 240
#define DISP_BUF_SIZE 240 * 240 / 2

// static lv_color_t lv_full_disp_buf[DISP_BUF_SIZE];
lv_color_t lv_disp_buf_p[DISP_BUF_SIZE * sizeof(lv_color_t)];
static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;

void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *fun, const char *dsc)
{
    Serial.printf("%s@%d %s->%s\r\n", file, line, fun, dsc);
    Serial.flush();
}
SCREEN_CLASS screen = SCREEN_CLASS(240,240);
/**
 * @brief  屏幕刷新回调函数
 * @param  disp:屏幕驱动地址
 * @param  area:刷新区域
 * @param  color_p:刷新缓冲区地址
 * @retval 无
 */
static void disp_flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);

    screen.startWrite();
    screen.setAddrWindow(area->x1, area->y1, w, h);
    screen.pushColors((uint16_t *)(&color_p->full), w * h, true);
    screen.endWrite();

    lv_disp_flush_ready(disp);
}

static void disp_wait_cb(lv_disp_drv_t *disp_drv)
{
    //    __wfi();
}

/**
 * @brief  屏幕初始化
 * @param  无
 * @retval 无
 */
void lv_port_disp_init(SCREEN_CLASS *scr)
{
    // lv_log_register_print_cb(
    //     reinterpret_cast<lv_log_print_g_cb_t>(my_print)); /* register print function for debugging */
    lv_log_register_print_cb(
        reinterpret_cast<lv_log_print_g_cb_t>(my_print)); /* register print function for debugging */

    /* Move the malloc process to Init() to make sure that the largest heap can be used for this buffer.
     *
    lv_disp_buf_p = static_cast<lv_color_t*>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    if (lv_disp_buf_p == nullptr)
        LV_LOG_WARN("lv_port_disp_init malloc failed!\n");
    */

    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf_p, nullptr, DISP_BUF_SIZE);

    /*Initialize the display*/
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = DISP_HOR_RES;
    disp_drv.ver_res = DISP_VER_RES;
    disp_drv.flush_cb = disp_flush_cb;
    disp_drv.wait_cb = disp_wait_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = scr;
    lv_disp_drv_register(&disp_drv);
}

TaskHandle_t handleTaskLvgl;
void TaskLvglUpdate(void *parameter)
{
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    for (;;)
    {
        lv_task_handler();

        delay(5);
    }
}
/**
 * @brief  显示初始化
 * @param  无
 * @retval 无
 */
void Port_Init()
{
    static SCREEN_CLASS screen1;
    // lv_disp_buf_p = static_cast<lv_color_t *>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    // if (lv_disp_buf_p == nullptr)
    //     Serial.printf("lv_port_disp_init malloc failed!\n");
    // else
    //     Serial.printf("malloc successfully!\n");

    /* 屏幕初始化 */
    screen1.begin();
    screen1.setRotation(0);
    screen1.fillScreen(TFT_BLACK);

    /* lvgl初始化 */
    lv_init();
    lv_port_disp_init(&screen1);
    // lv_port_indev_init();
    // lv_fs_if_init();

    // // Update display in parallel thread.
    // xTaskCreate(
    //     TaskLvglUpdate,
    //     "LvglThread",
    //     20000,
    //     nullptr,
    //     configMAX_PRIORITIES - 1,
    //     &handleTaskLvgl);

    // /* 背光渐亮 */
    // HAL::Backlight_SetGradual(500, 1000);
}
