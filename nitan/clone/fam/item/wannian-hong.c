#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "萬年紅" NOR, ({"wannian hong"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "此乃萬年紅，為宮廷禁品，天下間最上乘的顏料。\n" NOR);
                set("unit", "盒");
                set("value", 8000);
        }
}

int query_autoload()
{
        return 1;
}

