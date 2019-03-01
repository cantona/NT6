#include <weapon.h>
#include <ansi.h>

inherit PIN;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIR "葵花針" NOR, ({ "kuihua zhen", "kuihua", "zhen", "pin" }));
        set_weight(30);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "根");
                set("long", HIR "一根血紅色的細針，也不知道是用什麼金屬鑄成。\n" NOR);
                set("value", 800000);
                set("no_sell", "你窮瘋了？居然連針也賣得出手。");
                set("material", "silver");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", (: do_unwield :));
                set("stable", 100);
        }
        init_pin(160);
        setup();
}

string do_wield()
{
        object me = this_player();
        int lvl;

        lvl = me->query_skill("pixie-jian", 1) + me->query_skill("kuihua-mogong", 1);

        addn_temp("apply/attack", lvl/2, me);
        addn_temp("apply/dodge", lvl/2, me);
        return HIR "$N" HIR "單手一抖，亮出一根血紅色的細針。\n" NOR;
}

string do_unwield()
{
        object me = this_player();
        int lvl;

        lvl = me->query_skill("pixie-jian", 1) + me->query_skill("kuihua-mogong", 1);

        // 這裡計算有bug
        addn_temp("apply/attack",-lvl/2, me);
        addn_temp("apply/dodge",-lvl/2, me);
        return HIR "$N" HIR "一聲冷笑，收起了葵花針。\n" NOR;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill("sword") < 250)
                return damage_bonus / 2;

        if (me->query_skill_mapped("sword") != "pixie-jian" &&
            me->query_skill_mapped("sword") != "kuihua-mogong")
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 16 + 2);
                return random(2) ? HIR "只見$N" HIR "腰枝猛擺，幻出無數身影，$n"
                                   HIR "招架頓時散亂，不由連退數步！\n" NOR:

                                   HIR "$N" HIR "一聲冷笑，單手輕輕一彈，紅光飛"
                                   "射，$n" HIR "登時如遭電擊，全身酸麻！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return random(2) ? HIR "$n" HIR "只見眼前紅光躍動，有若鬼魅，但"
                                   "覺胸口一陣刺痛，濺出幾滴鮮血！\n" NOR:

                                   HIR "$N" HIR "身形一晃，已不見了蹤影，卻聽$n"
                                   HIR "一聲慘叫，葵花針竟已入體半分！\n" NOR;

        case 2:
                return HIR "$N" HIR "身形飄忽，化作一簇紅芒急速躍動，$n"
                       HIR "霎時只覺眼花繚亂，無從招架！\n" NOR;

        case 3:
                return HIR "只見$N" HIR "驀地裡疾沖上前，瞬間已至$n" HIR
                       "跟前，陰笑兩聲，又隨即躍開！\n" NOR;
        }
        return damage_bonus;
}
