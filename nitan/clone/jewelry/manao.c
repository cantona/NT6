// manao.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM"瑪瑙"NOR, ({ "ma nao", "manao" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一塊晶瑩古雅的瑪瑙。\n");
                set("unit", "塊");
                set("value", 70000 );
        }

}
