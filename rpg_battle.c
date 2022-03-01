#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/SMSlib.h"
#include "lib/PSGlib.h"
#include "actor.h"
#include "data.h"

char line_counter;

void interrupt_handler() {
	SMS_setBGPaletteColor(0, line_counter);
	SMS_setSpritePaletteColor(0, line_counter);
	
	line_counter++;
}

void main() {	
	SMS_useFirstHalfTilesforSprites(1);
	SMS_setSpriteMode(SPRITEMODE_TALL);
	SMS_VDPturnOnFeature(VDPFEATURE_HIDEFIRSTCOL);

	SMS_displayOff();

	line_counter = 0;
	SMS_setLineInterruptHandler(&interrupt_handler);
	SMS_setLineCounter(60);
	SMS_enableLineInterrupt();

	SMS_displayOn();

	while (1) {
		SMS_waitForVBlank();
	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0); // code 9999 hopefully free, here this means 'homebrew'
SMS_EMBED_SDSC_HEADER(0,1, 2022,02,28, "Haroldo-OK\\2022", "RPG Battle POC",
  "A proof-of-concept RPG Battle System.\n"
  "Made for the SMS Power! Competition 2022 - https://www.smspower.org/forums/18879-Competitions2022DeadlineIs27thMarch\n"
  "Built using devkitSMS & SMSlib - https://github.com/sverx/devkitSMS");

