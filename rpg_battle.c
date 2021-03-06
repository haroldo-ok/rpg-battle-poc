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
	case 2:
		SMS_loadSpritePalette(player_1_palette_bin);
		break;

	case 3:
		SMS_loadSpritePalette(player_2_palette_bin);
		break;

	case 4:
		SMS_loadSpritePalette(player_2_palette_bin);
		break;
		
	default:
		SMS_loadSpritePalette(player_3_palette_bin);
	}
		
	
	line_counter++;
	if (line_counter > 4) line_counter = 0;
}

void draw_player(char x, char y, char tile) {
	SMS_addSprite(x, y, tile);
	SMS_addSprite(x + 8, y, tile + 2);
	y += 16;
	SMS_addSprite(x, y, tile + 4);
	SMS_addSprite(x + 8, y, tile + 6);
}

void main() {	
	SMS_useFirstHalfTilesforSprites(1);
	SMS_setSpriteMode(SPRITEMODE_TALL);
	SMS_VDPturnOnFeature(VDPFEATURE_HIDEFIRSTCOL);

	SMS_displayOff();

	SMS_setBGPaletteColor(0, 0x04);
	
	SMS_loadPSGaidencompressedTiles(player_1_tiles_psgcompr, 2);
	SMS_loadPSGaidencompressedTiles(player_2_tiles_psgcompr, 10);
	SMS_loadPSGaidencompressedTiles(player_3_tiles_psgcompr, 18);

	line_counter = 0;
	SMS_setLineInterruptHandler(&interrupt_handler);
	SMS_setLineCounter(32);
	SMS_enableLineInterrupt();

	SMS_initSprites();

	draw_player(200, 64, 18);
	draw_player(200, 100, 2);	
	draw_player(200, 136, 10);	

	SMS_finalizeSprites();
	SMS_copySpritestoSAT();

	SMS_displayOn();

	while (1) {
		SMS_waitForVBlank();
	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0); // code 9999 hopefully free, here this means 'homebrew'
SMS_EMBED_SDSC_HEADER(0,1, 2022,03,03, "Haroldo-OK\\2022", "RPG Battle POC",
  "A proof-of-concept RPG Battle System.\n"
  "Built using devkitSMS & SMSlib - https://github.com/sverx/devkitSMS");

