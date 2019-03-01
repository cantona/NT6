#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(NOR + YEL "厚背紫金刀" NOR,({ "houbei dao", "houbei", "dao", "blade" }) );
        set_weight(4800);
        if (clonep())
                destruct(this_object());
        else {
                set("long", YEL "這是一柄厚背紫金八卦刀，刀縫浮動著淡紫色的"
                            "光澤。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", YEL "$N" YEL "一聲清嘯，「唰」地一聲抽出厚"
                                 "背紫金刀，一股寒氣撲面湧來。\n" NOR);
                set("unwield_msg", YEL "$N" YEL "輕哼一聲，將手中厚背紫金刀"
                                 "插回背後。\n" NOR);
                set("stable", 100);
        }
        init_blade(140);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("blade") != "bagua-dao" ||
            me->query_skill("bagua-dao", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 10 + 2);
                return YEL "$N" YEL "一聲大喝，手中厚背紫金刀按照八卦方位連"
                       "連斬出，劃出一道道金芒，逼得$n" YEL "連連後退！\n"
                       NOR;

        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return YEL "$N" YEL "手中厚背紫金刀按照八卦方位連連斬出。$n"
                       YEL "見周圍刀影重重向自己聚攏，不由得心生畏\n懼，只能夠"
                       "勉強作出抵擋！\n" NOR;
        }
        return damage_bonus;
}