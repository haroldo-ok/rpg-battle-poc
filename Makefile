PRJNAME := rpg_battle
OBJS := data.rel actor.rel rpg_battle.rel

all: $(PRJNAME).sms

data.c: data/* data/player_1_tiles.psgcompr  data/player_2_tiles.psgcompr  data/player_3_tiles.psgcompr
	folder2c data data

data/player_1_tiles.psgcompr: data/img/player_1.png
	BMP2Tile.exe data/img/player_1.png -noremovedupes -8x16 -palsms -fullpalette -savetiles data/player_1_tiles.psgcompr -savepalette data/player_1_palette.bin

data/player_2_tiles.psgcompr: data/img/player_2.png
	BMP2Tile.exe data/img/player_2.png -noremovedupes -8x16 -palsms -fullpalette -savetiles data/player_2_tiles.psgcompr -savepalette data/player_2_palette.bin

data/player_3_tiles.psgcompr: data/img/player_3.png
	BMP2Tile.exe data/img/player_3.png -noremovedupes -8x16 -palsms -fullpalette -savetiles data/player_3_tiles.psgcompr -savepalette data/player_3_palette.bin

data/%.path: data/path/%.spline.json
	node tool/convert_splines.js $< $@

data/%.bin: data/map/%.tmx
	node tool/convert_map.js $< $@
	
%.vgm: %.wav
	psgtalk -r 512 -u 1 -m vgm $<

%.rel : %.c
	sdcc -c -mz80 --peep-file lib/peep-rules.txt $<

$(PRJNAME).sms: $(OBJS)
	sdcc -o $(PRJNAME).ihx -mz80 --no-std-crt0 --data-loc 0xC000 lib/crt0_sms.rel $(OBJS) SMSlib.lib lib/PSGlib.rel
	ihx2sms $(PRJNAME).ihx $(PRJNAME).sms	

clean:
	rm *.sms *.sav *.asm *.sym *.rel *.noi *.map *.lst *.lk *.ihx data.*
