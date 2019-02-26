#include <weapon.h>
#include <ansi.h>

inherit STAFF;

void create()
{
        set_name(HIG "神農鐗" NOR,({ "shennong jian", "shennong", "jian", "staff" }) );
        set_weight(3800);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIG "一柄看似普通的藥鋤，柄上刻着“神農”二字。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIG "$N" HIG "拔出神農鐗握在手裏，四周空氣中"
                                 "頓時充滿濃厚的草藥香味。\n" NOR);
                set("unwield_msg", HIG "$N" HIG "哈哈一笑，將神農鐗收回。\n" NOR);
                set("stable", 100);
        }
        init_staff(130);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("staff") != "shennong-zhang" ||
            me->query_skill("shennong-zhang", 1) < 100)
                return damage_bonus / 2;

        switch (random(8))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("staff") / 12 + 2);
                return HIG "$N" HIG "將手中神農鐗急速揮舞轉動，一股刺鼻的氣味"
                       "頓時撲面而來，$n" HIG "見狀連忙後退！\n" NOR;

        case 1:
                n = me->query_skill("staff");
                victim->receive_damage("qi", n * 2 / 3, me);
                victim->receive_wound("qi", n * 2 / 3, me);
                return HIG "$N" HIG "身形如鬼魅般飄出，手中神農鐗一陣亂舞，猶"
                       "如千百根相似，$n" HIG "見狀不由心生畏懼，只能夠勉強作"
                       "出抵擋！\n" NOR;
        }
        return damage_bonus;
}

