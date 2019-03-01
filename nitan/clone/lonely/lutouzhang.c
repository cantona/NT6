#include <weapon.h>
#include <ansi.h>

inherit STAFF;

void create()
{
        set_name(NOR + WHT "鹿頭杖" NOR,({ "lutou zhang", "lutou", "zhang" }) );
        set_weight(800);
        if (clonep())
                destruct(this_object());
        else {
                set("long", NOR + WHT  "一根粗長的木杖，上方呈鹿頭狀。\n" NOR);
                set("unit", "根");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "wood");
                set("wield_msg", WHT "$N" WHT "將手中鹿頭杖猛地揮舞幾圈，然後拿在手中。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "大喝一聲，將鹿頭杖取下矗在地上。\n" NOR);
                set("stable", 100);
        }
        init_staff(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("staff") != "lutou-zhang" ||
            me->query_skill("lutou-zhang", 1) < 100)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("staff") / 10 + 2);
                return WHT "$N" WHT "將手中鹿頭杖揮舞得風聲呼呼，竟將$n" WHT "籠罩！\n" NOR;

        case 1:
                n = me->query_skill("staff");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return HIR "$N" HIR "飛身而起，手中鹿頭杖從天而下，砸向$n" HIR "！\n" NOR;
        }
        return damage_bonus;
}