inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "幻地神珠" NOR, ({"huandi shenzhu", "huandi", "shenzhu", "zhu"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIM "珍奇罕見的寶珠，周身繚繞著五色彩芒。\n" NOR);
                set("unit", "顆");
                set("value", 15000);
                set("can_be_enchased", 1);
                set("magic/type", "fire");
                set("magic/power", 35 + random(16));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
