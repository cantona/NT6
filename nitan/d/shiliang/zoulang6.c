// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "走廊");
        set("long", @LONG
你走在一條長長的走廊上，上面雕樑畫柱，飛檐琉璃，穿行其
間，心情舒暢。往東是溫老五的住處，往西是後院。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ 
            "west"  : __DIR__"houyuan",
            "north" : __DIR__"zoulang7",
            "south" : __DIR__"zoulang5",
            "east"  : __DIR__"fang4",
        ]));
        set("coor/x", 1620);
        set("coor/y", -1930);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}