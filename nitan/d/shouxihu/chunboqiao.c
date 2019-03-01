// Room: /yangzhou/chunboqiao.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","春波橋");
        set("long",@LONG
小紅橋是一座木制拱橋，此橋西接桃花塢，東連四橋煙雨樓前南端
小島，與四橋煙雨樓相通。
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "west" : __DIR__"taohuawu",
                "east" : __DIR__"siqiaoyanyu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1);
        set("coor/y", 40);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}