// lian.c 西洋連環劍

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「連環劍」只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("必須拿劍才能施展「連環劍」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法施展「連環劍」！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展「連環劍」！\n");

        if ((int)me->query_skill("xiyang-jian", 1) < 80)
                return notify_fail("你的西洋劍術還不到家，無法使用連環劍！\n");

        if (me->query_skill_mapped("sword") != "xiyang-jian")
                return notify_fail("你沒有激發西洋劍術，無法使用連環劍！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "\n$N" HIC "狂喝一聲，只見上一劍、下一劍、左一劍、右一劍、當中一劍，一起刺向$n"
              HIC "！\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(5));
        return 1;
}
