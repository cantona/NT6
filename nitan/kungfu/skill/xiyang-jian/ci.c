// ci.c 刺劍

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
                return notify_fail("「刺劍」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
                
        if ((int)me->query_skill("xiyang-jian", 1) < 70)
                return notify_fail("你的西洋劍術不夠嫻熟，不會使用「刺劍」。\n");
                                
        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠高，難以運用「刺劍」。\n");
                        
        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，不能使用「刺劍」。\n");

        if (me->query_skill_mapped("sword") != "xiyang-jian")
                return notify_fail("你沒有激發西洋劍術不夠嫻熟，不能使用「刺劍」。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "\n$N" HIC "一聲呼哨，手中的" +
              weapon->name() + HIC "猶如一道電光閃向$n" HIC "的胸前。\n"NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap * 2 / 3);
                addn("neili", -70, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "$n" HIR "急忙招架，卻是慢了一步，被這"
                                           "一劍正好刺中胸口，鮮血飛濺！\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "然而$p" CYN "眼明手快，不慌不忙的將$P"
                       CYN "的劍招架開。\n"NOR;
                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
