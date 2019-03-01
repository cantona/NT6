#include <room.h>
inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
這是一家規模很小的客店，店裡的擺設也相當的陳舊和簡陋。客
店的老板是一個老頭，因為這間小店的成本小，老頭也就沒請其它人
幫忙，客店內外的一切都是由他在打理。客店的櫃台上掛著一個牌子
(paizi)。
LONG );
       set("exits", ([
                "east" : "/d/beijing/caroad_w1",
        ]));
        set("item_desc", ([
                "paizi" : "牌子上歪歪斜斜的寫著兩個字：\n\n"
                        "                       客滿！\n\n",
        ]));
        set("objects", ([
                "/d/beijing/npc/chenlaotou" : 1,
                "/d/beijing/npc/youren" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();

        replace_program(ROOM);
}