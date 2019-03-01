#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

void create()
{
        set_name(NOR + WHT "玄鐵棋盤" NOR,({ "xuantie qipan", "xuantie", "qipan", "pan" }) );
        set_weight(30000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", WHT "一個黑黝黝的棋盤，看起來毫不起眼。提在手中感覺非常的沉\n"
                            "重，仔細一看，整個棋盤竟然是用玄鐵鑄成。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", WHT "$N" WHT "從背後取出一個黑黝黝的棋盤高舉在手中，霎"
                                 "時空氣中竟沁入一陣寒氣。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "哈哈一笑，將手中的玄鐵棋盤收回。\n" NOR);
                set("stable", 100);
        }
        init_hammer(160);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("hammer") != "fenglei-panfa" ||
            me->query_skill("fenglei-panfa", 1) < 100)
                return damage_bonus / 2;

        switch (random(16))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("hammer") / 10 + 2);
                return WHT "$N" WHT "跨前一步，手中玄鐵棋盤配合風雷盤法一陣亂舞，$n" WHT "只"
                       "覺得眼花繚亂，不由心生畏懼！\n" NOR;

        case 1:
                n = me->query_skill("hammer");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return WHT "$N" WHT "猛的一聲爆喝，手中玄鐵棋盤竟然幻作一道長虹向$n" WHT "貫"
                       "去！\n" NOR;
        }
        return damage_bonus;
}