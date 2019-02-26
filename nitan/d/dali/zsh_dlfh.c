//zsh_bjfh.c
#include <ansi.h>

inherit ROOM;

#define PLACE "dl"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"紫衫會大廳"NOR);
        set("long", @LONG
這裏是紫衫會設在大理的分會，廳中掛了很多丹青草圖，幾名書
僮有的提畫卷，有的磨墨。正中一白鬚老者，正信手揮毫，看來正在
作畫。房間牆壁上有一塊牌子(paizi)。凡紫衫會成員均可以在這裏取
得各種任務去完成。
LONG );

        set("objects", ([ 
               "/d/dali/npc/zsh_xiao"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "north" : "/d/dali/zsh_dldamen",
        ]));

	set("coor/x", -19150);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>