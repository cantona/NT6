// xiao.c 瀟湘夜雨

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i, n;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("太玄神功的「瀟湘夜雨」絕技只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("taixuan-shengong", 1);

        if (skill < 180)
                return notify_fail("你的太玄神功修為不夠，不能使用「瀟湘夜雨」！\n");

        if ((int)me->query_skill("force", 1) < 300)
                return notify_fail("你的內功修為還不夠，無法使用「瀟湘夜雨」！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，無法運用「瀟湘夜雨」！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你只有裝備劍才能施展「瀟湘夜雨」！\n");

        n = 4 + skill / 100;

        msg = HIW "$N" HIW "手中" + weapon->name() + HIW "連連晃動，頓時盪起一陣"
              HIW "低沉的有如滾滾雷音的海嘯聲……\n突然間$N" HIW "手中的" +
              weapon->name() + HIW "如一道閃電劃過，瞬間已向$n"
              HIW "唰唰唰連刺" + chinese_number(n) + "劍。\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 6;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < n; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
