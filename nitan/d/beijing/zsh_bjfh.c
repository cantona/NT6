//zsh_bjfh.c
#include <ansi.h>

inherit ROOM;

#define PLACE "bje"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"紫衫會大廳"NOR);
        set("long", @LONG
這裏是紫衫會設在北京的分會，大廳裏掛滿了各種字畫，一股書
香氣息迎面撲來。廳中一青年男子手捧一書籍，正漫步而吟。房間牆
壁上有一塊牌子(paizi)。凡紫衫會成員均可以在這裏取得各種任務去
完成。
LONG );

        set("objects", ([ 
               "/d/beijing/npc/zsh_duan"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "north" : "/d/beijing/zsh_bjdamen",
        ]));

	set("coor/x", -2770);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>