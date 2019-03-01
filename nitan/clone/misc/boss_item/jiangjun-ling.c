inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "將軍令" NOR, ({"jiangjun ling", "jiangjun", "ling"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", HIY "一塊金色的令牌，上面刻有「德川將軍」的字樣。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
