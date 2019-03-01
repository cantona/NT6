// huashen.c 化身萬千

#include <ansi.h>

inherit F_SSERVER;

string name() { return "化身萬千"; }

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「化身萬千」只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你只有空手才能使用「化身萬千」。\n");

        skill = me->query_skill("tianmo-zhang", 1);

        if (skill < 120)
                return notify_fail("你的天魔掌法修為太低，現在不能使用「化身萬千」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法使出「化身萬千」！\n");

        msg = HIC "$N" HIC "突然身形變快，雙掌翻飛幻化出無數掌影，一股巨大"
              HIC "的氣浪連綿不斷，一層接一層壓向$n" HIC "。\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 3;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
