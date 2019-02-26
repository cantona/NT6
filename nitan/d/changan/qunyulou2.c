//Room: qunyulou2.c

inherit ROOM;

void create()
{
        set("short", "羣玉樓二樓");
        set("long", @LONG
羣玉樓二樓。這是一座三層高的小樓，本來是某一位大亨陪同夫
人賞月之處，現在已被羣玉樓用重金買下。只聽一聲聲划拳行令，加
雜着女人的嬌笑，不時的從房間中傳出。
LONG );
        set("exits", ([ /* sizeof() == 6 */
                "north" : "/d/changan/qunyuys1",
                "south" : "/d/changan/qunyuys2",
                "west"  : "/d/changan/qunyuys3",
                "east"  : "/d/changan/qunyuys4",
                "down"  : "/d/changan/qunyulou1",
                "up"    : "/d/changan/qunyulou3",
        ]));

        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}