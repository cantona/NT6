// gold.c
#include <ansi.h>
inherit MONEY;

void create()
{
        set_name(HIY "金元寶" NOR, ({"yuanbao", "yuanbao_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "yuanbao");
                set("long", HIY "一塊金黃色的元寶，閃閃發亮，拿在手裡沉甸甸的。\n" NOR);
                set("unit", "些");
                set("base_value", 1000000);
                set("base_unit", "塊");
                set("base_weight", 1);
        }
        set_amount(1);
}

