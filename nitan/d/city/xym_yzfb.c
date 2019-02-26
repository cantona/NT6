//xym_yzfb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "yz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "俠義盟揚州分舵");
        set("long", @LONG
這裏是俠義盟在揚州的分舵。分舵舵主鄭雲虎乃成中嶽麾下的一
員猛將，粗獷豪邁。在房間的牆上有一塊牌子 (paizi)。加入俠義盟
的玩家，可以在這裏選擇任務去完成。
LONG );

        set("objects", ([
               "/d/city/npc/boss-zheng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : "/d/city/xym_yzdamen",
        ]));

	set("coor/x", -50);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>