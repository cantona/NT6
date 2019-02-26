// jiang.c 神龍天降

#include <ansi.h>

inherit F_SSERVER;
string name() { return "神龍天降"; }

int perform(object me, object target)
{
        object weapon;
        string msg,force;
        int damage,sk1,sk2,exp1,exp2,skill,dp,ap;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「神龍天降」只能在戰鬥中使用。\n");


        skill = (int)me->query_skill("shenlong-jian",1);

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( skill < 300 )
                return notify_fail("你的神龍劍法不夠嫻熟，不會使用「神龍天降」。\n");

        if( (int)me->query_skill("busi-shenlong", 1) <100
                 && (int)me->query_skill("shenlong-xinfa", 1)<100)
                return notify_fail("你的內功火候不夠，無法發揮劍法威力。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在內力太弱，不能使用絕招。\n");

        if ( me->query_skill_mapped("force") != "busi-shenlong"
                 && me->query_skill_mapped("force") != "shenlong-xinfa")
                 return notify_fail("你沒有運用神龍教系列內功！\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        msg = CYN "$N後躍一步，手捏劍決，口中唸唸有詞，突然大喝一聲「神龍天降」！！\n"NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if( !target->is_busy() )
                {
                        if(skill<350)
                                target->start_busy(1 + random(2));
                        else
                                target->start_busy(1 + random(3));
                }
                damage = damage_power(me, "sword");

                target->receive_damage("qi", damage/2,me);
                target->receive_damage("jing", damage/3,me);
                target->receive_wound("jing", damage,me);
                addn("neili", -damage, me);
                msg += HIY"$N的劍法頓時變得詭異十分，幻出朵朵劍花，猶如數條金龍，迅速向$n飛去！\n"
                       "$n試圖避開劍招，可全身僵硬不能動彈，疑惑中已經身中數劍，精神愈加恍惚起來！\n"NOR;
                me->start_busy(3);
        }
        else
        {
                msg += CYN"$n頓感身體被制，情知不妙，立刻攝守神元，終於突破對方控制。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}

