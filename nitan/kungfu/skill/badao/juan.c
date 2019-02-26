#include <ansi.h>
#include <combat.h>

#define CHAN "「" HIC "龍捲風" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" CHAN "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((level = me->query_skill("badao", 1)) < 500)
                return notify_fail("你的霸刀不夠嫻熟，難以施展" CHAN "。\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你沒有激發霸刀，難以施展" CHAN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣不夠，難以施展" CHAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "負刀而立，猛然間，刀鋒一轉，一股強勁的刀氣奔騰而出，猶如龍捲風般呼嘯而至，將$n" HIC "籠罩。\n" NOR;

        addn("neili", -300, me);
        if (random(level) + 200 > (int)target->query_skill("dodge", 1) / 2)
        {
                msg += HIR "結果$p" HIR "被$P" HIR "鬧個手忙腳亂，"
                       "驚慌失措，呆在當場，不知如何應對！\n" NOR;
                target->start_busy(level / 20 + 5);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，鎮"
                       "定逾恆，全神應對自如。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}