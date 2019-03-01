// This program is a part of NITAN MudLIB
// sui.c 隨字訣

#include <ansi.h>

string name() { return "隨字訣"; }

inherit F_SSERVER;

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

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

        if ((int)me->query_skill("taiji-jian", 1) < 100)
                return notify_fail("你的太極劍法不夠嫻熟，不會使用「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 80)
                return notify_fail("你的太極神功火候不夠，難以施展「" + name() + "」。\n");

        if( query("neili", me)<query("max_neili", me)/50 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("tjj_sui", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("taiji-jian");
        msg = HIC "$N使出太極劍法「隨」字訣，劍圈逐漸縮小，手中" + weapon->name() +
              HIC "幻出道道光環，將周身護住。\n" NOR;
        message_combatd(msg, me, target);

        addn_temp("apply/attack", -skill/6, me);
        addn_temp("apply/defense", skill*6, me);
        set_temp("tjj_sui", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill/6, skill*6 :), skill);

        addn("neili", -query("max_neili", me)/50, me);
        if(me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
        addn_temp("apply/attack", a_amount, me);
        addn_temp("apply/defense", -d_amount, me);
        delete_temp("tjj_sui", me);
        tell_object(me, HIG "你的「" + name() + "」運行完畢，將內力收回丹田。\n" NOR);
}
