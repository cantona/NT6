// Room: /lingzhou/baxian.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "八仙道觀");
        set("long", @LONG
這裡是八仙道觀，內有八仙殿，供著張果老、鐵拐李、呂洞賓等八
仙的塑像，香案上香煙繚繞。靠牆放著幾張太師椅，地上放著幾個蒲團。
東西兩側是走廊，北邊是東二巷， 南邊是後院,種著些楊柳和老槐樹，
是道士們休息的地方。後院還有一口井，不過看上去有點異樣。
LONG );
        set("exits", ([
                "west" : __DIR__"xiaolu2",
        ]));
        set("objects", ([
                __DIR__"npc/laodaoshi" : 1,
        ]));
        set("coor/x", -6235);
        set("coor/y", 2965);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}