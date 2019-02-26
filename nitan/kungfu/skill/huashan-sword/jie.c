// This program is a part of NITAN MudLIB
// jie.c 華山劍法「截手式」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "截手式" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if ((level = me->query_skill("huashan-sword", 1)) < 30)
                return notify_fail("你的華山劍法不夠嫻熟，無法施展" + name() + " 。\n");

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("你沒有激發華山劍法，無法施展" + name() + "。\n");

        if( query("neili", me)<60 )
                return notify_fail("你現在真氣不夠，無法使用「截手式」。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n但見$N" HIW "長劍一勒，使出華山劍法絕技之"
              "「" HIG "截手式" HIW "」，轉折之際天衣無縫，一\n"
              "劍既出，後着源源傾瀉，如大浪躍灘，層層疊疊，迅"
              "然撲向$n" HIW "！\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "瘁不及防，連連倒退"
                       "幾步，一時間無法回手！\n" NOR;
                target->start_busy(level / 80 + 3);
        } else
        {
                if( objectp(weapon=query_temp("weapon", target)) )
                        msg += CYN "但是$p" CYN "識破了$P" CYN "的用意，"
                               "自顧將手中的" + weapon->name() +
                               CYN "舞成一團光花，$P"
                               CYN "一怔之下再也攻不進去。\n" NOR;
                else
                        msg += CYN "但是$p" CYN "雙手戳點刺拍，將$P"
                               CYN "的來招一一架開。\n" NOR;

                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
