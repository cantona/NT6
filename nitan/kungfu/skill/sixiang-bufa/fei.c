#include <ansi.h>

inherit F_SSERVER;

string name() { return HIY "飛天神行" NOR; }


void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count, cnt, skill;

        if( query_temp("fei_tian", me) )
                return notify_fail("你已經運起" + name() + "了。\n");

        if ((int)me->query_skill("sixiang-bufa", 1) < 150)
                return notify_fail("你的四象步法等級不夠，難以施展" + name() + "。\n");

        if ((int)me->query_dex() < 33)
                return notify_fail("你的身法不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge", 1) < 150)
                return notify_fail("你的輕功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你此時的內力不足，難以施展" + name() + "。\n");

        msg = HIY "$N" HIY "足尖輕點地面，凌空躍起，身形頓時變得飄忽不定，難以捉摸。\n\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("sixiang-bufa", 1);
        cnt = (int)((int)me->query_condition("drunk") / 3);

        count = skill / 20;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("dex", count, me);
        set_temp("fei_tian", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("fei_tian", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("fei_tian", me);
                tell_object(me, "你的" + name() + "運行完畢，將內力收回丹田。\n");
        }
}
