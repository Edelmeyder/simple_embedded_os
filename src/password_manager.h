#ifndef _PASSWORD_MANAGER_H
#define _PASSWORD_MANAGER_H

#define PASS "4321"

#include "keyboard.h"
#include "lcd.h"

#include <inttypes.h>

void PASSWORD_MANAGER_init(void);
void PASSWORD_MANAGER_update(void);

#endif