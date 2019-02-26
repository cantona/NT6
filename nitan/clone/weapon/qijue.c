#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIY "七絕針" NOR, ({ "qijue zhen", "zhen", "needle" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根黃金製成的針，鑲在一個指環上。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N從口袋中拈出一根$n套在小手指上。\n");
                set("unwield_msg", "$N將手上的$n摘下來。\n");
        }
        init_sword(40);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int damage;

        if (victim->query_condition("snake_poison",1)< 50)
        {
                victim->apply_condition("snake_poison", 290);   
                return HIR "$n只覺得傷口上一麻！\n" NOR;
        }
}
