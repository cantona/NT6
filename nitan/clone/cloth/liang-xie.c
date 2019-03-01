// liang-xie.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIC "涼鞋" NOR, ({ "liang xie", "xie" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", "一雙細帶黑皮平底小涼鞋。\n");
                set("value", 1);
                set("material", "boots");
                set("armor_prop/dodge", 5);
        }
        setup();
}

int query_autoload() { return 1; }
