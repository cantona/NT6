// wugu.c 無骨

#include <ansi.h>

inherit F_SSERVER;

string name() { return "無骨"; }

int perform(object me, object target)
{
        string msg,force;
        int ap, dp;
        int count;
        int i,j;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「無骨」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「無骨」只能空手使用。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 120)
                return notify_fail("你的化骨棉掌火候不夠，無法使用「無骨」絕招！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，無法使用「無骨」絕招！\n");

        if (! me->query_skill_prepare() &&
            me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你現在沒有準備使用化骨棉掌，無法使用「無骨」絕招！\n");

        if(!stringp(force = me->query_skill_mapped("force"))
                ||force!="busi-shenlong")
                return notify_fail("你沒有使用神龍不死心法，無法使出絕招！\n");

        msg = HIW "只聽得$N關節喀喀作響，掌心隱約透出股黑氣，雙臂變得柔軟無骨一般！\n"NOR;
        ap=attack_power(me, "strike")+me->query_str()*20;
        if (living(target))
                 dp=defense_power(target, "parry")+target->query_dex()*20;
        else     dp = 0;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIW "$n見$P招式怪異，不知該怎麼招架，慌亂中$N的雙掌已到面前。\n"NOR;
        }

        else
        {
                msg += HIW "$n抖擻精神，剎那間已看清$N的招式，從容招架。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        addn("neili", -200, me);
        j = random(6);
        if (j < 3) j = 3;
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 2);
        }

        me->start_busy(1+random(2));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);

        return 1;
}
