#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(NOR + WHT "墨劍" NOR, ({ "mo jian", "mo", "jian" }) );
        set_weight(14000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", WHT "一柄通體墨黑的長劍，劍身透著奇異的光澤。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", WHT "只見$N" WHT "單袖輕輕一抖，手中已多了一柄通"
                                 "體墨黑的長劍。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "微微一笑，將手中的墨黑長劍插回腰"
                                 "間。\n" NOR);
                set("stable", 100);
        }
        init_sword(90);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("sword") != "shangqing-jian" ||
            me->query_skill("shangqing-jian", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 12 + 1);
                return WHT "$N" WHT "反轉墨劍劍身，接連劃出數朵劍花，頓時劍光四射，攻得$n"
                       WHT "措手不及！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return WHT "$N" WHT "一聲冷哼，手中墨劍中宮直進，霎時一道劍氣至墨劍劍尖電"
                       "射而出，貫向$n" WHT "！\n" NOR;
        }
        return damage_bonus;
}