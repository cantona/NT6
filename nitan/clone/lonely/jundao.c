#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(WHT "闖王軍刀" NOR, ({ "chuangwang jundao", "chuangwang", "jundao", "dao", "blade" }) );
        set_weight(6200);
        if (clonep())
                destruct(this_object());
        else {
                set("long", WHT "這是闖王所使用過的刀，上面刻有幾行小字。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", WHT "$N" WHT "縱聲大笑，從腰間抽出一柄頗為古舊的彎刀。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "環顧四周，輕嘆一聲，將闖王軍刀插回腰間。\n" NOR);
                set("stable", 100);
        }
        init_blade(120);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("blade") != "chuangwang-dao" ||
            me->query_skill("chuangwang-dao", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 12 + 2);
                return WHT "$N" WHT "一聲怒喝，手中闖王軍刀橫劈而出，刀勢凜冽，頓時將$n"
                       WHT "逼退數步！\n" NOR;

        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n / 2, me);
                victim->receive_wound("qi", n / 2, me);
                return WHT "$N" WHT "橫轉手中闖王軍刀，刀鋒頓時勾勒出一道凌厲的勁芒，直"
                       "湧$n" WHT "而去！\n" NOR;
        }
        return damage_bonus;
}