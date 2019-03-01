// lian.c　夫妻刀法絕招：連綿不絕
// By Alf, Last Update 2001.05

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("你只能對戰鬥中的對手使用這一絕招。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( (int)me->query_skill("fuqi-daofa", 1) < 40 )
                return notify_fail("依你目前的功力，還使不出這一絕招。\n");

        if( random(query("combat_exp", me))>query("combat_exp", target)/20 )
        {
                attack_time = random((int)me->query_skill("fuqi-daofa", 1) / 20);
                if(attack_time < 1)
                        attack_time = 1;

        msg = HIC "$N淡然一笑，刀勢驟然加快，招數首尾相銜，連綿不絕的攻向$n！\n" NOR;
        msg += HIM "$n看不清招式來路，頓時手忙腳亂，抵擋不及，瞬間已接連中招！\n" NOR;

                for(i = 0; i < attack_time; i++)
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                message_combatd(msg, me, target);
                me->start_busy(3);
                addn("neili", -100, me);
        }

        else
        {
        msg = HIC "$N淡然一笑，刀勢驟然加快，招數首尾相銜，連綿不絕的攻向$n！\n" NOR;
        msg += HIY"可是$n早有防備，見招拆招，守御得水潑不進，將來招一一化解。\n" NOR;
                message_combatd(msg, me, target);
                me->start_busy(3);
        }

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

