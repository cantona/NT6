// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i;
        
        if (! me->is_fighting())
                return notify_fail("你只能在戰鬥種使用諸天化身步。\n");

        if ((int)me->query_skill("linji-zhuang", 1) < 100)
                return notify_fail("你的臨濟十二莊還不夠火候，使不出諸天化身步。\n");  

        if ((int)me->query_skill("anying-fuxiang", 1) < 100)
                return notify_fail("你的暗影浮香還不夠火候，使不出諸天化身步。\n");  

        if( query("jing", me)<500 )
                return notify_fail("你現在精不夠。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在內力不夠。\n");

        if( query_temp("emei/parry", me) )
                return notify_fail("你正在使用諸天化身步。\n");

        msg = HBYEL "$N使出暗影浮香的諸天化身步，身手登時更加靈巧！\n\n" NOR; 

        addn("neili", -200+random(100), me);
        me->recieve_damage("jing", 50);
        
        message_combatd(msg, me);
        
        i = me->query_skill("linji-zhuang", 1) / 5;
        
        addn_temp("apply/dex", i, me);
        addn_temp("apply/con", i, me);
        set_temp("emei/parry", i, me);
        
        remove_call_out("remove_effect");
        call_out("remove_effect", 1, me, (int)me->query_skill("force") / 3);
        return 1;
}

void remove_effect(object me, int count)
{
        int i;
        
        if (! me) return;
        if (! me->is_fighting()
        ||  me->query_skill_mapped("dodge") != "anying-fuxiang" 
        ||  count < 1)
        {
                i=query_temp("emei/parry", me);
                addn_temp("apply/dex", -i, me);
                addn_temp("apply/con", -i, me);
                delete_temp("emei/parry", me);
                tell_object(me, HIW "你停止了諸天化身步，深深的吸了口氣。\n" NOR);
                return;
       }
       call_out("remove_effect", 1 ,me ,count -1);
}
