// lian.c 連字訣

#include <ansi.h>

string name() { return "連字訣"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int time;
        int count;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + name() + "」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("必須拿劍才能施展「" + name() + "」。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真氣不夠，無法施展「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 200)
                return notify_fail("你的太極神功火候不夠，難以施展「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 200)
                return notify_fail("你的太極劍還不到家，無法使用「" + name() + "」。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你沒有激發太極劍法，無法使用「" + name() + "」。\n");

        time = me->query_skill("taiji-jian") / 20;
        if (time > 10) time = 10;
        if (time < 1) time = 1;

        msg = HIC "$N" HIC "一聲長嘯，靈台清明，凝神歸元，使出太極劍中的「" + name() + "」。\n"
              HIY "手中" + weapon->name() + HIY "招式陡然變得凌厲無比，一轉念"
              HIY "間已然攻出" + chinese_number(time) + "招！\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("taiji-jian", 1) / 2;
        addn("apply/attack", skill, me);
        addn("apply/damage", skill, me);
        addn("neili", -(time*100), me);

        for (i = 0; i < (time); i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn("apply/attack", -skill, me);
        addn("apply/damage", -skill, me);
        me->start_busy(1+ random(3));
        return 1;
}
