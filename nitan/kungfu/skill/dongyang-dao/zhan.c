// zhan.c 迎風一刀斬

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「迎風一刀斬」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
                
        if ((int)me->query_skill("dongyang-dao", 1) < 70)
                return notify_fail("你的東洋刀法不夠嫻熟，不會使用「迎風一刀斬」。\n");
                                
        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠高，難以運用「迎風一刀斬」。\n");
                        
        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，不能使用「迎風一刀斬」。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "\n$N" HIC "大喝一聲，眼中兇光畢露，手中的" +
              weapon->name() + HIC "化作一道光弧直劈而下，正是扶桑密學「迎風一刀斬」。\n"NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("force");
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "只覺得腦中轟的一下，渾"
                                           "身血脈登時不暢，不禁“哇”的吐了一口鮮血。\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += HIC "然而$p" HIC "運足中氣，硬接下了這一刀，絲毫無傷。\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
