inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "碧魄冰晶" NOR, ({"bipo bingjing", "bipo", "bingjing"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "晶瑩剔透的寒晶，寒氣刺骨，乃天界極品。\n" NOR);
                set("unit", "塊");
                set("value", 12000);
                set("can_be_enchased", 1);
                set("magic/type", "cold");
                set("magic/power", 55 + random(16));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
