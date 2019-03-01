// luan.c 亂刀訣

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
                return notify_fail("「亂刀訣」只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("必須拿刀才能施展「亂刀訣」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法施展「亂刀訣」！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展「亂刀訣」！\n");

        if ((int)me->query_skill("dongyang-dao", 1) < 80)
                return notify_fail("你的東洋刀法還不到家，無法使用亂刀訣！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "\n$N" HIY "嘿嘿一聲冷笑，手中的" + weapon->name() +
              HIY "左突右伸，刀刀都從意想不到的地方砍向$n"
              HIY "！\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(5));
        return 1;
}
