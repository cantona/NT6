// Room: /wuliang/road5.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "後山小路");
        set("long", @LONG
這是條通往後山的羊腸小路，就是無量弟子也絕少來此。這裡山
林茂密，人跡罕見，小鳥鳴響不絕于耳。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"road6",
                "east"   : __DIR__"road3",
        ]));
        set("objects", ([
                __DIR__"obj/cao" : 2,
        ]));
        set("coor/x", -71020);
        set("coor/y", -79890);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}