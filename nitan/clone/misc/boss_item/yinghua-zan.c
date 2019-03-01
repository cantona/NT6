inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "《櫻花讚》" NOR, ({"yinghua zan", "yinghu", "zan"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", HIM "這是一本寫有《櫻花讚》的曲譜。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
