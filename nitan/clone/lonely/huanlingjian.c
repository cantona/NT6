#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW "幻靈劍" NOR, ({ "huanling jian", "huanling", "sword" }));
        set_weight(4000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "劍身優美細長，散發着淡青銀光。\n" NOR);
                set("unit", "柄");
                set("value", 40000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "銀光劃過，幻靈劍已落入$N" HIW "手中。\n" NOR);

                set("unwield_msg", HIW "天地忽暗，$N" HIW "手中的幻靈劍已悄然隱沒 。\n" NOR);
                set("stable", 100);
        }                                                                                                                    
        init_sword(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("sword") != "xiaoyao-jian" ||
            me->query_skill("xiaoyao-jian", 1) < 120)
                return damage_bonus / 2;

        if (random(5) == 1)
        {
               n = me->query_skill("sword");
               victim->receive_damage("qi", n * 3 / 5, me);
               victim->receive_wound("qi", n * 2 / 7, me);
               return HIW "$N" HIW "一聲冷哼，手中幻靈劍猶如靈蛇一般遊走不定，霎時一道劍氣至劍尖激"
                      "射而出，貫向$n" HIW "！\n" NOR;
        }
        return damage_bonus;
}