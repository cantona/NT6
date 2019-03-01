// da-shugan.c

#include <weapon.h>;
#include <ansi.h>;
inherit CLUB;

void create()
{
        set_name(HIY"大樹幹"NOR,({ "da shugan", "shugan" }) );
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 0);
                set("material", "bamboo");
                set("long", "這是一根幹掉的的大樹幹。\n");
                set("wield_msg", "$N拿出一根$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_club(8);
        setup();
}