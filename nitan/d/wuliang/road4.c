// Room: /wuliang/road4.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這裡是劍湖宮內最長的甬道。甬道繞山勢曲折延展，南通正廳，
北面就是無量劍掌門人的居所劍湖宮了。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("exits", ([
                "northup"  : __DIR__"jianhugong",
                "south"    : __DIR__"zhengting",
        ]));
        set("coor/x", -71000);
        set("coor/y", -79880);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}