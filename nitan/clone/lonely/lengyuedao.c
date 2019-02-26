#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIC "冷月寶刀" NOR, ({ "lengyue baodao", "lengyue", "baodao", "dao", "blade" }) );
        set_weight(6200);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIC "這是一柄形如冷月的寶刀，整個刀身冷氣森森，鋭利無比。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIC "$N" HIC "抽出柄形如冷月的長刀，頓時只覺寒氣逼"
                                 "人，刀光如水，流轉不定。\n" NOR);
                set("unwield_msg", HIC "$N" HIC "彈刀清嘯，心中感慨，將冷月寶刀插回"
                                 "刀鞘。\n" NOR);
                set("stable", 100);
        }
        init_blade(160);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("blade") != "hujia-daofa" ||
            me->query_skill("hujia-daofa", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 12 + 2);
                return HIC "$N" HIC "一聲大喝，手中冷月寶刀一振，頓時漾起一層波瀾，逼"
                       "得$n" HIC "連連後退！\n" NOR;

        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIC "$N" HIC "將手中冷月寶刀破空劃出，霎時竟掀起千層刀芒，寒氣"
                       "逼人，$n" HIC "全身不由得一顫！\n" NOR;
        }
        return damage_bonus;
}