// jie.c 天劫

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「天劫」只能在戰鬥中對對手使用。\n");
 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「天劫」只能空手使用。\n");
                
        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為還不夠，無法施展天劫。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if( query("qi", me)<800 )
                return notify_fail("你的體力現在不夠！\n");

        if ((int)me->query_skill("shou-yin", 1) < 150)
                return notify_fail("你的手印火候不夠，無法使用天劫！\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，無法使用天劫！\n");

        if (me->query_skill_prepared("hand") != "shou-yin")
                return notify_fail("你現在沒有準備使用手印，無法使用天劫！\n");

        msg = HIW "$N" HIW "一聲暴喝，雙手猛然翻滾，"
              "剎那間只見無數的手印舖天蓋地蜂擁而出，"
              "氣勢恢弘，無與倫比。\n" NOR;
        ap=me->query_skill("strike")+query("str", me)*10;
        dp=target->query_skill("parry")+query("dex", target)*6;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 9;
                msg += HIR "$n" HIR "面對$P" HIR "這排山倒海攻勢，完全"
                       "無法抵擋，唯有退後。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "凝神應戰，竭盡所能化解$P" HIC
                       "這幾掌。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        addn_temp("apply/attack", count, me);

        addn("neili", -300, me);
        addn("qi", -100, me);//WhyIdon'tusereceive_damage?
                                // Becuase now I was use it as a cost
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(5));
        addn_temp("apply/attack", -count, me);

        return 1;
}
