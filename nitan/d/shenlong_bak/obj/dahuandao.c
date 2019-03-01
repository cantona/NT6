// dahuandao.c  大環刀
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(HIW"大環刀"NOR, ({ "blade","dao" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把明晃晃的大環刀，刀背上還有幾個圓環穿在上面，“嘩棱棱”直響。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N「嘩棱棱」的一聲舉起一把$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n放下。\n");
        }
        init_blade(40);
        setup();
}