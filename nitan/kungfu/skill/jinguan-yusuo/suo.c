#include <ansi.h>
#include <combat.h>

string name() { return HIY "玄門金鎖" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只有在戰鬥中才能使用。\n");

        if ((level = me->query_skill("jinguan-yusuo", 1)) < 150)
                return notify_fail("你的金關玉鎖不夠熟練，難以施展" + name() + "。\n" NOR);

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n" NOR);

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "突然間$N" HIY "雙手驀的回圈，使出「" HIR "玄門金鎖"
              HIY "」絕技，企圖鎖死$n" HIY "的招數。\n" NOR;

        ap = attack_power(me, "parry");
        dp = defense_power(target, "parry");

        if ( ap / 2 + random(ap) > dp )
        {
                msg += HIR "霎時$n" HIR "只覺招數一緊，雙臂癱軟，全身"
                       "力道竟似被$N" HIR "牢牢鎖住！\n" NOR;
                target->start_busy(ap / 80 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        } else
        {
                msg += HIC "可是$n" HIC "防守嚴密，絲毫不為$N"
                       HIC "的招數所亂。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}