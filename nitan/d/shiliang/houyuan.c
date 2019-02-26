// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "後院");
        set("long", @LONG
這裏是個大大的後院，古樹參天，知了在樹上不停地叫着，有個
僕人在那裏清掃着地面。
LONG
        );
        set("outdoors","shiliang");
        set("exits", ([ 
            "southwest" : __DIR__"zoulang1",
            "west"      : __DIR__"zoulang2",
            "northwest" : __DIR__"zoulang3",
            "north"     : __DIR__"zoulang4",
            "southeast" : __DIR__"zoulang5",
            "east"      : __DIR__"zoulang6",
            "northeast" : __DIR__"zoulang7",
        ]));
        set("objects", ([
                 __DIR__"npc/atu" : 1,
        ]));
        set("coor/x", 1610);
        set("coor/y", -1930);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}