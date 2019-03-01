// This program is a part of NITAN MudLIB
// jingtian.c  白虹驚天 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        string msg;

        if (! me->is_fighting())
                return notify_fail("「白虹驚天」只能在戰鬥中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                        return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("shenghuo-xuanming", 1) < 100)
                return notify_fail("你的聖火玄冥功火候還不到家, 不能使用這一絕技 !\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候還不到家, 不能使用這一絕技 !\n");

        if ((int)me->query_skill("baihong-jianfa", 1) < 100)
                return notify_fail("你的逍遙劍法火候還不到家, 不能使用這一絕技 !\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠！\n");

        msg = HIC "\n$N長嘯一聲，手彈長劍，身形飄忽不定，使的正是白虹驚劍法的絕技「白虹驚天」！\n" NOR;
        message_combatd(msg, me);

        me->clean_up_enemy();
        ob = me->select_opponent();
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);

        addn("neili", -random(150)-50, me);
        me->start_busy(1 + random(4));      
        return 1;
}