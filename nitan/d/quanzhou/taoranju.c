// Room: /d/quanzhou/taoranju.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "陶然茶居");
        set("long", @LONG
這是專供品嚐和銷售茶葉的店鋪，店裏清香四溢進門就有心曠神怡
之感。牆上有一價目表(sign)。
LONG );
        set("outdoors", "quanzhou");
        set("item_desc", ([
                "sign" : "
茶杯(Cha bei)                 ：三十文銅板
鐵觀音茶杯(Guanying chabei)   ：三十文銅板
龍井茶杯(Longjing chabei)     ：三十文銅板
茉莉花茶杯(Moli chabei)       ：三十文銅板
香片茶杯(Xiangpian chabei)    ：三十文銅板\n"
        ]));
        set("exits", ([
                "south" : __DIR__"xinmenji",
        ]));
        set("objects", ([
                __DIR__"npc/tao" : 1,
        ]));
	set("coor/x", -910);
	set("coor/y", -7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}