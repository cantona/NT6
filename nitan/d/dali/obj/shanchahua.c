//shanchahua.c
inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR"山茶花"NOR, ({"cha hua", "hua"}));
        set("unit", "朵");
        set("long", "一株盛開的茶花，幾朵不同色的大花開放在一枝，看來定然十分名貴不是凡品。\n");
        set("value", 10);
        setup();
}
