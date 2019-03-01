// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "東廂房");
        set("long", @LONG
這是供來客休息的廂房，房子不大，但是很整潔，牆上掛
着一些字畫。有個丫鬟正忙着為客人泡茶。
LONG
        );
        set("exits", ([ 
                "west" : __DIR__"yuanzi",
        ]));
        set("objects", ([
                "/d/changan/obj/chairs" : 1,
                __DIR__"npc/yahuan" : 1,
        ]));
        set("coor/x", 1620);
        set("coor/y", -1960);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}