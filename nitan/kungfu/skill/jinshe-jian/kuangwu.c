//金蛇劍--金蛇狂舞 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("金蛇狂舞只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功不夠嫻熟，不能使用金蛇狂舞。\n");

        if ((int)me->query_skill("jinshe-jian", 1) < 150)
                return notify_fail("你的金蛇劍法不夠嫻熟，不能使用金蛇狂舞。\n");


        if( query("neili", me)<400 )
                return notify_fail("你現在內力太弱，不能使用金蛇狂舞。\n");

        if (me->query_skill_mapped("sword") != "jinshe-jian")
                return notify_fail("你沒有激發金蛇劍法，不能使用金蛇狂舞。\n");

        if (!living(target))
                return notify_fail("對方已經這樣了，不用這麼費力吧。\n");

        msg = HIY "$N" HIY "當下不及細想，身隨劍走，綿綿而上,使出一招“金蛇狂舞”，"
              "手中的" + weapon->name() + HIY "揮出無數彎曲的劍刃,如影隨形,永無止歇!。\n" NOR;
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                me->start_busy(2);
                    if (!target->is_busy())
                target->start_busy(1 + random(2));

                damage = damage_power(me, "sword");
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                       HIR "劍光一閃," HIR "$n" HIR "的胸口赫然留下一道彎彎血痕! \n" NOR);

                                         
        } else
        {
                me->start_busy(3);
                msg += CYN "$p" CYN "瞧不清敵招來路，驚惶中只得連連倒退! \n" NOR;
                      
        }
        message_combatd(msg, me, target);

        return 1;
}
