//Room: jiulou2.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "望星樓二樓");
        set("long", @LONG
二樓是酒樓的雅座。在這裡的客人們都低言慢語，不象樓下的客
人那般狂呼豪飲。二樓賣的酒菜也是望星樓掌廚最拿手的。兩旁掛著
長聯直貫屋角：[1；31m       君即飲此觴，對酒高歌，人醉樓頭，待劉伶同
樂；       余亦醺一夢，臨風把盞，雲橫江上，與王粲銷愁。[2；37；0m
LONG );


        set("exits", ([
                "down" : "/d/changan/jiulou",
        ]));
        set("objects", ([
                "/d/changan/npc/yang-laoban" : 1,
        ]));

        set("coor/x", -10750);
	set("coor/y", 1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}