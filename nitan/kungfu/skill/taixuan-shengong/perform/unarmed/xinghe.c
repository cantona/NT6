// xinghe.c 星河影動

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count, n;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("太玄神功「星河影動」只能在戰鬥中對對手使用。\n");
 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你手中拿着兵器，無法施展「星河影動」。\n");
                
        if (me->query_skill_prepared("unarmed") != "taixuan-shengong")
                return notify_fail("你現在沒有準備使用太玄神功，無法使用「星河影動」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        ap = (int)me->query_skill("taixuan-shengong", 1);

        if (ap < 180)
                return notify_fail("你的太玄神功火候不夠，無法使用「星河影動」！\n");

        if ((int)me->query_skill("force", 1) < 300)
                return notify_fail("你的內功修為不夠，無法使用「星河影動」！\n");

        n = 5 + ap / 100;

        msg = HIW "$N" HIW "氣沉丹田，雙足一點，身子如旋風般向上卷出，"
              "霎時已向$n" HIW "劈空擊出" + chinese_number(n) +
              "招，招招呼嘯有聲！\n\n" NOR;

        dp = target->query_skill("parry", 1);

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 5;
                msg += HIR "$n" HIR "剛想避開$P" HIR "這如影如風般的攻勢，"
                       "卻發現已被一股巨大的勁力包圍，無從閃避。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "凝神應戰，聚真氣於雙臂，奮力化解$P" HIC
                       "這幾招。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn("neili", -300, me);

        for (i = 0; i < n; i++)
        {
                if (! me->is_fighting(target))   break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(2 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
