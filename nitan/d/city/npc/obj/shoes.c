// shoes.c

#include <armor.h>
#include <ansi.h>

inherit BOOTS;


void create()
{
        set_name(YEL "繡花小鞋" NOR, ({ "shoes" }) );
        set_weight(900);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一雙小巧精緻的繡花鞋。  \n");
                set("material", "cloth");
                set("unit", "雙");
//                set("value", 300);
                set("armor_prop/armor", 1 );
                set("female_only", 1);
        }
        setup();
}
//int query_autoload() { return 1; }
