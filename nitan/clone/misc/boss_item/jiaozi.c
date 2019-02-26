inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "交子" NOR, ({"jiaozi"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", HIC "交子是古代最早的紙幣，是倭寇搜刮民財的證據。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
