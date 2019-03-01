//Room: qunyulou3.c

inherit ROOM;

void create()
{
        set("short", "群玉樓三樓");
        set("long", @LONG
群玉樓三樓。這是一座三層高的小樓，本來是某一位大亨陪同夫
人賞月之處，現在已被群玉樓用重金買下。只聽一聲聲劃拳行令，加
雜著女人的嬌笑，不時的從房間中傳出。
LONG );
        set("exits", ([ /* sizeof() == 5 */
                "north" : "/d/changan/qunyuys5",
                "south" : "/d/changan/qunyuys6",
                "west"  : "/d/changan/qunyuys7",
                "east"  : "/d/changan/qunyuys8",
                "down"  : "/d/changan/qunyulou2",
        ]));

        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}