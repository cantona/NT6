// Room: /d/taishan/sibeiya.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "斯碑崖");
        set("long", @LONG
玉女池側有巨石高聳黝黑若鼎，明人查志隆題“天柱”，秦李斯篆
書《泰山刻石》曾嵌石內，俗稱斯碑崖。
LONG );
        set("exits", ([
                "south" : __DIR__"yunuchi",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 50);
	set("coor/y", 310);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}