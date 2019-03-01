#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

void create()
{
        set_name(HIY "日月金輪" NOR, ({ "riyue jinlun", "riyue", "jinlun", "lun" }));
        set_weight(30000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIY "金輪法王的隨身兵器，乃是由金銀銅鐵錫五柄"
                            "法輪組成。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "將日月金輪高舉在手中，空氣"
                                 "中頓時沁出一股寒氣。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "一聲冷笑，將日月金輪收回"
                                 "懷中。\n" NOR);
                set("stable", 100);
        }
        init_hammer(180);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("hammer") != "riyue-lun" ||
            me->query_skill("riyue-lun", 1) < 100)
                return damage_bonus / 2;

        switch (random(16))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("hammer") / 10 + 2);
                return HIY "霎時$N" HIY "手中日月金輪黃芒暴漲，氣勢如虹，$n"
                       HIY "不由得心中一緊，攻勢頓時緩滯！\n" NOR;

        case 1:
                n = me->query_skill("hammer");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return HIY "$N" HIY "一聲嗔喝，手中日月金輪陡然化作五輪，從"
                       "五個不同的方位一齊襲向$n" HIY "！\n" NOR;
        }
        return damage_bonus;
}