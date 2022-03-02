#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/SMSlib.h"
#include "lib/PSGlib.h"
#include "actor.h"
#include "data.h"

char line_counter;

void interrupt_handler() {
//	SMS_setBGPaletteColor(0, line_counter);
	switch (line_counter) {
	case 1:
		SMS_setSpritePaletteColor(0, 0);
		SMS_setSpritePaletteColor(1, 0x0F);
		break;
		
	case 2:
		SMS_loadSpritePalette(player_1_palette_bin);
		break;
	}
		
	
	line_counter++;
	if (line_counter > 5) line_counter = 1;
}

void main() {	
	SMS_useFirstHalfTilesforSprites(1);
	SMS_setSpriteMode(SPRITEMODE_TALL);
	SMS_VDPturnOnFeature(VDPFEATURE_HIDEFIRSTCOL);

	SMS_displayOff();

	SMS_setBGPaletteColor(0, 0);
	SMS_setSpritePaletteColor(0, 0);
	
	SMS_loadPSGaidencompressedTiles(player_1_tiles_psgcompr, 2);

	line_counter = 0;
	SMS_setLineInterruptHandler(&interrupt_handler);
	SMS_setLineCounter(32);
	SMS_enableLineInterrupt();

	SMS_initSprites();

	SMS_addSprite(200, 32, 2);
	SMS_addSprite(208, 32, 4);
	SMS_addSprite(200, 48, 6);
	SMS_addSprite(208, 48, 8);

	SMS_addSprite(200, 64, 2);
	
	SMS_finalizeSprites();
	SMS_copySpritestoSAT();

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

