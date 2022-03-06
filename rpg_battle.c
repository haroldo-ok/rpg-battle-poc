#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/SMSlib.h"
#include "lib/PSGlib.h"
#include "actor.h"
#include "data.h"

char line_counter;
char color_index;

char next_color_value;
char next_color_index;
char *next_palette;

void interrupt_handler() {
	/*
	SMS_setSpritePaletteColor(0, line_counter);
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
	*/
	
	// Wait for a bit, so the CRAM dots don't appear at the right side.
	for (char i = 1; i; i--);
	
	SMS_setSpritePaletteColor(next_color_index, next_color_value);
	
	next_color_index = color_index;
	next_color_value = next_palette[color_index];
	
	color_index++;
	color_index &= 0x0F;
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
	color_index = 0;
	next_color_value = 0;
	next_color_index = 0;
	next_palette = player_1_palette_bin;

	SMS_setLineInterruptHandler(&interrupt_handler);
	SMS_setLineCounter(2);
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
SMS_EMBED_SDSC_HEADER(0,2, 2022,03,06, "Haroldo-OK\\2022", "RPG Battle POC",
  "A proof-of-concept RPG Battle System.\n"
  "Built using devkitSMS & SMSlib - https://github.com/sverx/devkitSMS");

