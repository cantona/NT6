#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIW "飛馬靴" NOR, ({ "feima xue", "feima", "xue" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", HIW "一雙做工奇特人間罕見的寶靴子，蘊藏著神奇的力量。\n");
                set("value", 2000000);
                set("armor_prop/armor", 200);
                set("armor_prop/dex", 1); //後天身法+1
                set("armor_prop/int", 2); //後天悟性+2
                set("material", "boots");
        }
        setup();
}

int query_autoload()
{
        return 1;
}
