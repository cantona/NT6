// shield.c 易筋經金剛不壞體

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;


        if( query("family/family_name", me) != "少林派" &&
            (!query("reborn/fams", me) || member_array("少林派", query("reborn/fams", me)) == -1) )
                return notify_fail("你不是少林弟子，無法使用易筋經絕技。\n");

        if (target != me)
                return notify_fail("你只能用易筋經來激發金剛不壞體 \n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠。\n");

        if ((int)me->query_skill("yijinjing", 1) < 40)
                return notify_fail("你的易筋經等級不夠。\n");

        if( query_temp("shield", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "雙目突然精芒暴漲,身上驀地湧起"
                        HIY "一股凜冽金光。\n" NOR, me);

        addn_temp("apply/armor", skill*5/2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill * 5 / 2 :), skill);


        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "金光隱隱退去,你恢復原來的樣子。\n");
        }
}
