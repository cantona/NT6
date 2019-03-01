// xiao-shuzhi.c 小樹枝

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIY"小樹枝"NOR,({ "xiao shuzhi", "shuzhi" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "枝");
                set("value", 0);
                set("material", "bamboo");
                set("long", "這是一枝小樹枝。\n");
                set("wield_msg", "$N拿出一枝$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(3);
        setup();
}