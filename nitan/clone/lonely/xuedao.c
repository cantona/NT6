#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIR "血刀" NOR,({ "xue dao", "dao", "xue", "blade" }) );
        set_weight(6000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIR "這是一把纏在腰間的寶刀，刀鋒帶着淡淡的"
                            "血影。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("material", "steel");
                set("no_sell", "這…這不是血刀門的東西嗎？我還要腦袋，你"
                               "自個留着吧！");
                set("wield_msg", HIR "$N" HIR "一聲陰笑，抽出一柄血紅色"
                               "的單刀高高揚起，空氣中頓時瀰漫出一股殺氣"
                               "。\n" NOR);
                set("unwield_msg", HIR "$N" HIR "一聲輕哼，將手中血刀插"
                               "回背後。\n" NOR);
                set("stable", 100);
        }
        init_blade(160);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("blade") != "xuedao-dafa" ||
            me->query_skill("xuedao-dafa", 1) < 100)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 10 + 2);
                return HIR "$N" HIR "一聲大喝，手中血刀凌空劈斬而出，劃"
                       "出一道道血色刀芒，直逼得$n" HIR "連連後退！\n"
                       NOR;
        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$n" HIR "見周圍血光漫天，刀影重重，不由得心"
                       "生畏懼，只能夠勉強作出抵擋！\n" NOR;
        }
        return damage_bonus;
}

