// hongbao.c 紅包
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"紅包"NOR, ({ "red bag", "hong bao", "bao" }));
        set_weight(500);
        set_max_encumbrance(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個精制的紅紙袋，邊上有燙金的花紋，用來裝賀儀禮金正合適。\n");
                set("value", 1000);
        }
}

int is_container() { return 1; }