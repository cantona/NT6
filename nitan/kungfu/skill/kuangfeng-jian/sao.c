// kuang.c 風掃落葉

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "風掃落葉" NOR; }

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
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對！\n");

        if( query("neili", me)<180 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "！\n");

        if ((int)me->query_skill("kuangfeng-jian", 1) < 100)
                return notify_fail("你的狂風劍法還不到家，無法施展" + name() + "！\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你的輕功修為不足，無法施展" + name() + "！\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "大喝一聲，手中的" + weapon->name() +
              HIC "猶如狂風疾電一般劈刺向$n" HIC "！\n"
              HIR "霎時間只見劍氣層層疊疊如波浪般洶湧而起，$n"
              HIR "只覺得呼吸登時不暢。\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -150, me);

        count = me->query_skill("sword") / 2;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(2) == 1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}
