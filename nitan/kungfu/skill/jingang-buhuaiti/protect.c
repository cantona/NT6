#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string name() { return "金剛不壞"; }
int perform(object me, object target)
{
        int skill;

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("jingang-buhuaiti", 1) < 100)
                return notify_fail("你的金剛不壞護體神功修為不夠。\n");

        if( query_temp("jingangbuhuai", me) )
                return notify_fail("你已經運起金剛不壞護體神功了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "只聽$N" HIY "高呼佛號，全身肌肉緊縮，霎那間皮膚竟猶如鍍金一般，發出燦燦金光。\n" NOR, me);

        addn_temp("apply/armor", skill/2, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("jingangbuhuai", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("jingangbuhuai", me) )
        {
                addn_temp("apply/armor", -(amount/2), me);
                addn_temp("apply/defense", -(amount/3), me);
                delete_temp("jingangbuhuai", me);
                tell_object(me, "你的金剛不壞護體神功運行完畢，將內力收回丹田。\n");
        }
}
