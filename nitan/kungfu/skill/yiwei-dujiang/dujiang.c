#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

inherit F_CLEAN_UP;

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if( query_temp("dujiang", me) )
                return notify_fail("你已經運起「一葦渡江」了。\n");

        if ((int)me->query_skill("yiwei-dujiang", 1)< 150)
                return notify_fail("你的一葦渡江等級不夠，難以施展此項絕技！\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法不夠使用「一葦渡江」絕技！\n");

        if ((int)me->query_skill("force", 1)< 150)
                return notify_fail("你的內功火候不夠，難以施展此項絕技！\n");

        if ((int)me->query_skill("dodge", 1)< 150)
                return notify_fail("你的輕功修為不夠，不會使用此項絕技！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠使用「一葦渡江」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你此時的內力不足！\n");

        msg = HIB "$N" HIB "運起心意氣混元功，施展「一葦渡江」絕技,"
                  "身形一展，整個人頓時凌空飄起，身體變得越來越輕。\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("yiwei-dujiang", 1);
        cnt =(int)( (int)me->query_condition("drunk") / 3);

        count = skill / 50 + cnt;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("dex", count, me);
        set_temp("dujiang", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("dujiang", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("dujiang", me);
                tell_object(me, "你的「一葦渡江」運功完畢，將內力收回丹田。\n");
        }
}
