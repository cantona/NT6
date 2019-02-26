// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "追魂爪" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" + name() + "。！\n");

        if (me->query_skill_mapped("claw") != "sanyin-zhua")
                return notify_fail("你所用的並非三陰蜈蚣爪，不能施展" + name() + "！\n");

        if (me->query_skill_prepared("claw") != "sanyin-zhua")
                return notify_fail("你所備的並非三陰蜈蚣爪，不能施展" + name() + "！\n");

        /*
        if (me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你所用的並非化功大法，施展不出" + name() + "！\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 120)
                return notify_fail("你化功大法修為太差，不能運用" + name() + "！\n");
        */

        if (me->query_skill("sanyin-zhua", 1) < 120)
                return notify_fail("你三陰蜈蚣爪修為太差，不能運用" + name() + "！\n");

        if( query("neili", me) <= 400 )
                return notify_fail("你的內力不夠使用追魂爪！\n");

        message_combatd(HIB "$N忽然嘿嘿乾笑幾聲，雙袖狂舞捲起地上黃沙飛揚令人看不出要從何處出招，\n"
                        "突然$N尖叫一聲，聲未停影先至向着$n撲來，雙爪連抓數爪，其速之快令$n無從躲閃。\n"
                        NOR, me, target);

        level = me->query_skill("sanyin-zhua", 1) + me->query_skill("finger", 1);

        addn_temp("apply/attack", level, me);
        addn_temp("apply/unarmed_damage", level, me);

        for (i = 0; i < 5 + random(5); i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -level, me);
        addn_temp("apply/unarmed_damage", -level, me);

        me->start_busy(2 + random(2));
        return 1;
}
