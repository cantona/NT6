#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "當舖");
        set("long", @LONG
這是周鬆天開的當舖。這當舖可能和官府有勾結。在這裡
不管你的東西的來路如何都照收。你也可以看看有什麼東西你
需要也可以去買一點。不過價錢可能比其他地方要貴一點。櫃
台的牆上掛著一個牌子(paizi)。
LONG);
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_beg", 1);
        set("item_desc", ([
                "paizi" : WHT "\n\n        ※※※※※※※※※※※\n"
                              "        ※                  ※\n"
                              "        ※     公平交易     ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "賣出" NOR + WHT "：   " NOR + HIY "sell" NOR + WHT "   ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "買進" NOR + WHT "：   " NOR + HIY "buy" NOR + WHT "    ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "估價" NOR + WHT "：   " NOR + HIY "value" NOR + WHT "  ※\n"
                              "        ※                  ※\n"
                              "        ※                  ※\n"
                              "        ※※※※※※※※※※※\n\n\n" NOR,
        ]));


        set("objects", ([
                  __DIR__"npc/zhousongtian" : 1,
                  __DIR__"npc/yitai" : 1,
        ]));

        set("exits", ([
                  "north" : __DIR__"yanling",
        ]));

        set("coor/x", -9050);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}