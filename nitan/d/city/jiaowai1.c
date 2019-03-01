// Room: /d/city/jiaowai1.c
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "草地");
        set("long", @LONG
這是揚州郊外的一片芳草地，落英繽紛，蜂歌蝶舞，朝露夕光，
沁人心脾。真是好時光。偶有幾對小男女結伴踏青，鶯聲麗影，嬉鬧
動人。
LONG );

    set("exits", ([
        "north" : "/d/city/dongmen",
        "south" : "/d/city/jiaowai2",
    ]));
    	set("quarrys", ([
                "caihuashe" : 100000,
                "dushe"     : 50000,
                "lang"      : 20000,
    	]));

    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", 40);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}
