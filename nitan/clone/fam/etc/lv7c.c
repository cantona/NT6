inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIB "青龍牙" NOR, ({"qinglong ya", "qinglong", "ya"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB "通體深藍的的象牙狀物體，傳説是龍的牙齒。\n" NOR);
                set("unit", "根");
                set("value", 50000);
                set("can_be_enchased", 1);
                set("magic/type", "magic");
                set("magic/power", 35 + random(16));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
