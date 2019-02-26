// break -「以柔破鋼」
// made by deaner

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int exert(object me, object target)
{
        string msg;
        object target_w;

        target_w=query_temp("weapon", target);

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能對戰鬥中的對手使用「以柔破鋼」。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正在發愣，是進攻的好時機！\n");

        if ((int)me->query_skill("lingyuan-xinfa", 1) < 150)
                return notify_fail("你的靈元心法火候不夠，還不會使用「以柔破鋼」。\n");

        msg = HIC "$N" HIC "沉肩滑步，自丹田中升起一股陰柔之氣"
              "順着血脈經絡傳至雙手勞宮穴，接着這股陰柔之氣就"
              "激射而出，噴向$n" HIC "手中的兵刃！\n" NOR;
        me->start_busy(2);

        if( query_temp("weapon", target) || query_temp("secondary_weapon", target) )
        {
                if( random(query("combat_exp", me))>
                    query("combat_exp", target)/3 )
                {
                        msg += HIW "結果$p" HIW "手中的" +
                               query("name", target_w)+
                               "與這股陰柔之氣一碰竟被震落在地上！\n" NOR;
                        target_w->unequip();
                        target_w->move(environment(target));
                        target->reset_action();
                        target->start_busy((int)me->query_skill("lingyuan-xinfa") / 20);
                } else
                {
                        msg += CYN "可是$p" CYN "急急拆招，躲了"
                               "開去，使$P" CYN "的計謀沒有得逞。\n" NOR;
                }
                message_combatd(msg, me, target);
                return 1;
        }
        return notify_fail(target->name() + "目前是空手，沒什麼必要施展「以柔破鋼」。\n");
}