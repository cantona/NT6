// This program is a part of NITAN MudLIB
// chan.c 靈蛇纏身

#include <ansi.h>

inherit F_SSERVER;

string name() { return "靈蛇纏身"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「靈蛇纏身」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("運用「靈蛇纏身」手中必須持杖！\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠！\n");

        if ((int)me->query_skill("staff") < 80)
                return notify_fail("你的杖法還不到家，無法使用「靈蛇纏身」！\n");

        if (target->is_busy())
                return notify_fail("對方正忙着呢，你還是加緊進攻吧！\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "$N" HIG "手中的" + weapon->name() +
              HIG "不住的顫動，活現一條靈蛇，纏向$n" HIG "，難以捉摸。\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "倉皇之下只有嚴守門户，無暇反擊！\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += HIC "可是$p" HIC "看破了$N" HIC
                       "的虛招，巧妙的運用身法躲過了$P的攻擊！" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
