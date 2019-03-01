// Room: /d/quanzhou/neitang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "內堂");
        set("long", @LONG
這裡是藥舖的內堂，東首擺了一個書架，上面放了不少醫書。此外
還有幾張桌椅(chair)。看來大概是藥舖接待客人的地方。
LONG );
        set("item_desc", ([
                "chair"   : 
"一張椅子，抹拭得很幹凈，椅背刻著雙龍搶珠的圖案，兩條龍刻得甚是
生動，張牙舞爪地搶奪一個鑲在椅背上青光發亮的鐵球(Iron Ball)。\n",
        ]));
        set("exits", ([
                "out"   : __DIR__"jishitang",
        ]));
	set("coor/x", -921);
	set("coor/y", -7681);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}