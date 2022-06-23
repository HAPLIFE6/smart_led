#ifndef __GUI_H
#define __GUI_H

#include "main.h"

typedef struct {
    uint8_t bk1_point;
    uint8_t bk2_point;
    bool bk_mode;
}GUI_InitTypedef;
extern GUI_InitTypedef GUI_InitStructure;

void GUI_Init(GUI_InitTypedef *GUI_InitStructure);
#endif
