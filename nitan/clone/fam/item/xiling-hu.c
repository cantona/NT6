#include <ansi.h>

inherit ITEM;


void create()
{
        set_name(HIY "吸靈壺" NOR, ({"xiling hu", "xiling", "hu"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一個散發著奇特光彩的玉壺，據說可以吸收蓬萊仙果中蘊涵的神力。\n\n" NOR);
                set("unit", "個");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}
