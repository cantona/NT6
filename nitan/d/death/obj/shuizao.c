#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(GRN "水藻" NOR, ({ "shui zao", "shui", "zao"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一叢生長在碧水寒潭裡的耐寒水藻。\n" NOR);
                set("unit", "叢");
                set("value", 0);
                set("no_get", "你試著拔了一下，結果它根深蒂固，你居然沒拔動。\n");
        }
}