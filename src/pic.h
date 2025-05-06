#pragma once

#include "idt.h"
#include "utils.h"

void PICInit(void);
void PICEnableIrq(u8 irq);
