// Room: /d/taishan/kongzimiao.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "孔子廟");
        set("long", @LONG
孔子廟位于孔子崖下，明嘉靖年間尚書朱衡建。廟有山門、正殿、
配殿，內奉孔子，配祀顏子、曾子、子思、孟子等。山門上有清人徐宗
幹題聯：“仰之彌高，鑽之彌堅，可以語上也；出乎其類，拔乎其萃，
宜若登天然。”
LONG );
        set("exits", ([
                "southup" : __DIR__"kongziya",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 320);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}