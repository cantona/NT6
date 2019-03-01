#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if( query_temp("gui_yuan", me) )
                return notify_fail("你已經運起「九陰歸元」了。\n");

        if ((int)me->query_skill("shexing-lifan", 1)< 150)
                return notify_fail("你的蛇行貍翻等級不夠，難以施展此項絕技！\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法不夠使用「九陰歸元」絕技！\n");

        if ((int)me->query_skill("force", 1)< 150)
                return notify_fail("你的內功火候不夠，難以施展此項絕技！\n");

        if ((int)me->query_skill("dodge", 1)< 150)
                return notify_fail("你的輕功修為不夠，不會使用此項絕技！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠使用「九陰歸元」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你此時的內力不足！\n");

        msg = HIW "$N" HIW "運起九陰真氣，雙臂骨骼一陣爆響，身形一展，整"
                  "個人頓時凌空飄起，速度變得異常敏捷。\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("shexing-lifan", 1);
        cnt =(int)( (int)me->query_condition("drunk") / 3);

        count = skill / 50;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("apply/str", count, me);
        addn_temp("apply/dex", count, me);
        set_temp("gui_yuan", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("gui_yuan", me) )
        {
                addn_temp("apply/str", -amount, me);
                addn_temp("apply/dex", -amount, me);
                delete_temp("gui_yuan", me);
                tell_object(me, "你的「九陰歸元」運功完畢，將內力收回丹田。\n");
        }
}
