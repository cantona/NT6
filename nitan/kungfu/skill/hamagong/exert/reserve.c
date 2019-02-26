// reserve.c 蛤蟆功經脈倒轉

#include <ansi.h>

inherit F_CLEAN_UP;

void show_effect(object me, int a_amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if ((int)me->query_skill("hamagong", 1) < 120)
                return notify_fail("你的蛤蟆功不夠嫻熟，不會經脈倒轉。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠。\n");

        if( query_temp("reverse", me) )
                return notify_fail("你已經倒轉經脈了。\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "忽地雙手撐地倒立，逆運經脈，頓時"
              "內息暗生，防禦力大增。\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/defense", skill/4, me);
        addn_temp("apply/armor", skill/2, me);
        addn_temp("apply/dispel_poison", skill/2, me);
        addn_temp("apply/reduce_poison", 10, me);//提高10%的抗毒
        set_temp("reverse", skill, me);

        addn("neili", -100, me);
        if (me->is_fighting())
                me->start_busy(2);

        me->start_call_out((: call_other, __FILE__, "show_effect", me, skill / 3 :), 10);
        return 1;
}

void show_effect(object me, int skill)
{
        if( !query_temp("reverse", me) )
               return ;

        skill=query_temp("reverse", me);

        if( query("neili", me)<200 )
        {
              write(HIG "你逆運經脈，內力耗盡，猛然間氣血上湧，你感覺自己內力受到了損傷。\n" NOR);
              addn("max_neili", -1, me);
              set("neili", 0, me);
              delete_temp("hmg_dzjm", me);
              addn_temp("apply/defense", -skill/4, me);
              addn_temp("apply/armor", -skill/2, me);
              addn_temp("apply/dispel_poison", -1*(skill/2+30), me);
              addn_temp("apply/reduce_poison", -10, me);

              return;
        }

        addn("neili", -200, me);

        me->start_call_out((: call_other, __FILE__, "show_effect", me, skill / 3 :), 10);

        return;
}
