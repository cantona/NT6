// panying.c 盤鷹訣

#include <ansi.h>
#include <combat.h>

string name() { return YEL "盤鷹訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 80)
                return notify_fail("你的軟紅蛛索不夠嫻熟，無法施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("你沒有激發軟紅蛛索，無法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = YEL "$N" YEL "使出軟紅蛛索「盤鷹」訣，手腕輕輕一抖，頓時鞭"
              "影重重，完全籠罩$n" YEL "四周！\n";

        me->start_busy(1);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "微作詫異，一時勘破不透$N" HIR "招中"
                       "奧妙，頓被攻了個措手不及！\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，小心應對，並沒有上當。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}