// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "走廊");
        set("long", @LONG
你走在一條長長的走廊上，上面雕樑畫柱，飛檐琉璃，穿行其
間，心情舒暢。往西是溫老三的住處，往東是後院。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ 
            "east"  : __DIR__"houyuan",
            "north" : __DIR__"zoulang3",
            "south" : __DIR__"zoulang1",
            "west"  : __DIR__"fang2",
        ]));
        set("coor/x", 1600);
        set("coor/y", -1930);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}