#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIY "黃金鋸齒刀" NOR, ({ "juchi dao", "juchi", "dao", "blade" }) );
        set_weight(6200);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIY "這是一柄背寬刃薄的黃金鋸齒刀，刀身發出奪"
                            "目的金光，刀刃呈鋸齒狀。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "抽出一柄形如鋸齒的寶刀，頓時"
                                 "只覺金光奪目。\n" NOR);
                set("unwield_msg", HIC "$N" HIC "彈刀清嘯，心中感慨，將黃金"
                                   "鋸齒刀插回刀鞘。\n" NOR);
                set("stable", 100);
        }                                                                                                                    
        init_blade(120);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("blade") != "yinyang-ren" 
           || me->query_skill("yinyang-ren", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 12 + 2);
                return HIC "\n$N" HIC "一聲大喝，手中黃金鋸齒刀一振，頓"
                       "時金光一閃，逼得$n" HIC "連連後退！\n" NOR;

        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIC "\n$N" HIC "將手中黃金鋸齒刀立于胸前，猛地金"
                      "刀一橫，金光晃動之處$n" HIC "只覺殺氣逼人。\n" NOR;
        }
        return damage_bonus;
}