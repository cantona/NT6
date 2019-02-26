// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "走廊盡頭");
        set("long", @LONG
你來到走廊的盡頭，往北看去是好大的一個湖泊，前面有個
小亭，温氏兄弟還真會享受。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ 
            "north"     : __DIR__"tingzi",
            "southeast" : __DIR__"zoulang7",
            "south"     : __DIR__"houyuan",
            "southwest" : __DIR__"zoulang3",
        ]));
        set("coor/x", 1610);
        set("coor/y", -1910);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}