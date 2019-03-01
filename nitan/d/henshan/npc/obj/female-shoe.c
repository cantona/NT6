#include <armor.h>
#include <ansi.h>

inherit BOOTS;

void create()
{
        set_name(HIM "繡花小鞋" NOR, ({ "flower shoes", "shoes"}) );
        set_weight(900);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "雙");
                set("long", "一雙女人穿的縫製得很精美的繡花鞋。\n");
                set("value", 0);
                set("armor_prop/armor", 1 );
                set("female_only", 1);
        }
        setup();
}