// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
這是通往衢州石樑鎮的青石大道，浙南山國，比之水鄉澤國的蘇南
浙北，自是另一風味了。北面就是石樑温家了。
LONG
        );
        set("outdoors", "shiliang");
        set("exits", ([
                "southdown" : __DIR__"road2",
                "north"     : __DIR__"gate",
        ]));
        set("objects", ([
                __DIR__"npc/nongfu" : 1,
        ]));
        set("coor/x", 1610);
        set("coor/y", -1980);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}