inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "冰火珠" NOR, ({"binghuo zhu", "binghuo", "zhu"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "拳頭大小的圓形寶珠，捧在手心只覺忽冷忽熱。\n" NOR);
                set("unit", "顆");
                set("value", 9000);
                set("can_be_enchased", 1);
                set("magic/type", "fire");
                set("magic/power", 60 + random(11));
        }
        setup();
}

int query_autoload()
{
        return 1;
}