#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIY "金蜈鈎" NOR,({ "jinwu gou", "gou", "jinwu", "jin" }) );
        set_weight(3500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIY "一柄金光閃閃的鈎子，很是鋒利，頂端好似一隻"
                            "蛇頭。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "冷笑一聲，從背後抽出一柄奇形"
                                 "怪狀的金鈎連揮數下，頓時金芒四射。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "一聲輕哼，將手中金蜈鈎插回"
                                 "背後。\n" NOR);
                set("stable", 100);
        }
        init_sword(130);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("sword") != "jinwu-goufa" ||
            me->query_skill("jinwu-goufa", 1) < 100)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIY "$N" HIY "將手中金蜈鈎凌空劈斬而出，劃出一道華麗"
                       "的金芒，直逼得$n" HIY "連連後退！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return HIY "$N" HIY "一聲厲嘯，身形沖天而起，手中金蜈鈎金光"
                       "四射，連刺$n" HIY "全身各處要穴！\n" NOR;
        }
        return damage_bonus;
}