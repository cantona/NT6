#include <ansi.h>
#include <combat.h>

#define  ZHU "「" HIW "誅天剎神" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon2;
        int damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/zhuihun-jian/zhu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHU "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" ZHU "。\n");

        if (me->query_skill_mapped("sword") != "zhuihun-jian") 
                return notify_fail("你沒有激發追魂奪命劍，難以施展" ZHU "。\n");

        if ((int)me->query_skill("zhuihun-jian", 1) < 160)
                return notify_fail("你的追魂奪命劍還不夠嫻熟，難以施展" ZHU "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，難以施展" ZHU "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "突然$N" HIW "一聲冷哼，一個跨步，手中" + weapon->name() +
              NOR + HIW "中攻直進，如閃電一般刺向$n" HIW "！\n" NOR;
        addn("neili", -50, me);

        ap = me->query_skill("zhuihun-jian", 1) +
             me->query_skill("sword", 1);
        dp = target->query_skill("parry");

        me->want_kill(target);
        if (ap / 3 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -200, me);
                damage = 0;

                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "只見$N" HIR "這一劍來勢好快，便聽“嗤"
                               "啦”一聲，劍尖已沒入$n" HIR "咽喉半尺，$n"
                               HIR "咯咯叫了兩聲，軟綿綿的癱了下去。\n" NOR
                               "( $n" RED "受傷過重，已經有如風中殘燭，隨"
                               "時都可能斷氣。" NOR ")\n";
                        damage = -1;
                } else

                if( objectp(weapon2=query_temp("weapon", target)) && 
                   me->query_skill("force") > target->query_skill("parry"))
                {
                        msg += HIR "只聽“嗤啦”一聲，$n" HIR "腕部已被$N"
                               HIR + weapon->name() + NOR + HIR "對穿而過"
                               "，手中" + weapon2->name() + NOR + HIR
                               "再也捉拿不住，脱手而飛！\n" NOR;
                        me->start_busy(random(2));
                        target->start_busy(4);
                        weapon2->move(environment(target));
                } else
                {
                        target->start_busy(1 + random(3));
        
                        damage = ap + (int)me->query_skill("force");
                        damage = damage / 2 + random(damage / 2);
                        
                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIR "$n" HIR "飛身躲閃，然而只聽“嗤啦”"
                               "一聲，$N" HIR + weapon->name() + NOR +
                               HIR "已沒入$n" HIR + limb + "半寸，鮮血"
                               "狂濺而出。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target,
                               WEAPON_ATTACK, damage, 70, pmsg);
                }
        } else 
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，避開了這一招。\n"NOR;
        }

        message_combatd(msg, me, target);
        if (damage < 0) target->die(me);

        return 1;
}
