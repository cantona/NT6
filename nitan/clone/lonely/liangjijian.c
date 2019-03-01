#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW "兩極劍" NOR,({ "liangji jian", "liangji", "jian", "sword" }) );
        set_weight(6500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "一柄鋒利的長劍，劍脊中分，一半呈火紅色，另"
                                "一半卻白如寒雪。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "$N" HIW "一聲長嘆，抽出一柄紅白相間的"
                                 "長劍握在手中。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "一聲輕哼，將手中的兩極劍插"
                                 "回背後。\n" NOR);
                set("stable", 100);
        }
        init_sword(150);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill("sword") < 160)
                return damage_bonus / 2;

        if (me->query_skill_mapped("sword") != "qiankun-jian" &&
            me->query_skill_mapped("sword") != "zhengliangyi-jian")
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 14 + 2);
                return HIW "$N" HIW "反轉兩極劍劍身凌空劈劃而出，頓時劍尖透"
                       "過數道寒芒，直逼得$n" HIW "連連後退！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return HIR "$N" HIR "手中兩極劍中宮直進，連續刺出，劍尖頓時"
                       "透出一道熾熱的劍氣，直湧$n" HIR "而去！\n" NOR;
        }
        return damage_bonus;
}