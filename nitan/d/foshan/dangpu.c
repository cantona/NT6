#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","英雄典當");
        set("long", @LONG
當舖裡一張高高的櫃台，櫃台後面坐著當舖的朝奉。這家當舖是
鳳老爺所開，十多年來從沒人來鬧過事，朝奉也就很放心。櫃台上掛
著一個木牌子(paizi)。
LONG );
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
                __DIR__"npc/chaofeng": 1,
        ]));

        set("exits", ([
                "north"  : __DIR__"street5",
        ]));
	set("coor/x", -6550);
	set("coor/y", -9760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}