// honglian.c 火燄刀  紅蓮火

#include <ansi.h>
inherit F_SSERVER;

string name() { return "紅蓮火"; }

void remove_effect(object me, int amount);

int perform(object me)
{
        int count, skill;
        skill = me->query_skill("longxiang-gong");

        /*
        if( !me->is_fighting() )
                return notify_fail("「紅蓮火」只能在戰鬥中的使用。\n");
        */

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能運用「紅蓮火」！\n");

        if( query_temp("honglian", me) )
                return notify_fail("你正在使用「紅蓮火」。\n");

        if( (int)me->query_skill("huoyan-dao", 1) < 180 )
                return notify_fail("你的火燄刀不夠嫻熟，還不能領會「紅蓮火」之訣竅。\n");

        if ( me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("你必須使用火燄刀來施展「紅蓮火」。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為太弱，使不出「紅蓮火」。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣不夠，使不出「紅蓮火」。\n");

        if( userp(me) && (int)me->query_skill("longxiang-gong", 1) < 100 )
                return notify_fail("你的龍象般若神功等級不夠高，使不出「紅蓮火」。\n");

        if( me->query_skill_mapped("force") != "longxiang-gong" && me->query_skill_mapped("force") != "xiaowuxiang")
                return notify_fail("你所使內功于火燄刀心法不符，使不出「紅蓮火」。\n");

        if( userp(me) && (int)me->query_skill("lamaism", 1) < 150 )
                return notify_fail("你對密宗心法的領悟不夠，無法使用「紅蓮火」。\n");

        me->receive_damage("qi", 0);
        message_combatd(RED"\n$N" RED "祭起火燄刀之「紅蓮火」絕技，精純的內力呈紅色緩緩湧出，于身前三尺之處\n"
                        RED "飄盪無定的真氣定在半空，虛無縹緲，不可捉摸！\n"NOR,me);
        count = skill / 2;


        addn("neili", -300, me);
        addn("jing", -50, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/strike", count/2, me);
        set_temp("honglian", 1, me);
        me->start_call_out( (: call_other,  __FILE__, "remove_effect", me, count :), skill/3 );

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("honglian", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/strike", -amount/2, me);
                delete_temp("honglian", me);
                tell_object(me,HIR "你身前飄盪無定的火炎隱隱退去。\n"NOR);
        }
}
