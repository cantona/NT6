// This program is a part of NITAN MudLIB
// fei.c 飛仙術

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "飛仙術"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛇島飛仙術只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" &&
            query("skill_type", weapon) != "staff" )
                return notify_fail("你必須持劍或杖才能施展蛇島飛仙術！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠！\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 100)
                return notify_fail("你的蛇島奇功的修為法還不到家，無法使用飛仙術！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        switch (random(3))
        {
        case 0:
                msg = HIY "$N" HIY "怪叫一聲，手中的" + weapon->name() +
                      HIY "一晃，化作數道光影飛向$n" HIY "！\n" NOR;
                break;

        case 1:
                msg = HIY "$N" HIY "口中念念有詞，手中的" + weapon->name() +
                      HIY "越使越快，漸漸形成一團光芒，籠罩了$n" HIY "！\n" NOR;
                break;

        default:
                msg = HIY "$N" HIY "怪笑兩聲，欺身近來，步法極其怪異，手中的" +
                      weapon->name() + HIY "忽然擊出，一連數招逼向$n" HIY "！\n" NOR;
                break;
        }

        message_combatd(msg, me, target);
        addn("neili", -100, me);
        count = me->query_skill("shedao-qigong", 1) / 2;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(2));
        return 1;
}


