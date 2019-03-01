#include <ansi.h>
#include <combat.h>

int is_scborn() { return 1; }

string name() { return HIC "劍靈之哀傷" NOR; }

int perform(object me, string skill, string arg)
{

        int armor, damage, sk;
        string msg;
        
        if( query_temp("special2/aishang", me) )
                return notify_fail("你已經處于極度的哀傷當中了，稍後再施展吧。\n");
        
        set_temp("special2/aishang", 1, me);
        
        armor = 3000;
        damage = 50000;
        sk = 500;
        
        addn_temp("apply/armor", armor, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/sword", sk, me);
        addn_temp("apply/parry", sk, me);
        addn_temp("apply/dodge", sk, me);
        addn_temp("apply/force", sk, me);

        msg = HIY "$N" HIY "輕撫「劍靈之哀傷」，剎那間，渾身散發出淡藍色的光芒，一直藍色的蝴蝶從$N" HIY "身體內升起，不斷煽動著翅膀。"
              "蝴蝶漸漸地化作一個仙子的模樣，凝視著$N" HIY "身上的「劍靈之哀傷」，慢慢地滴下眼淚 …… $N" HIY "不由自主地一陣哀傷，似"
              "乎在此刻與劍靈合為一體！\n" NOR;
        message_vision(sort_msg(msg), me) ;
        
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, armor, damage, sk :), 600);   

        return 1;
}

void remove_effect(object me, int armor, int damage, int skill)
{
        if (! objectp(me))return;

        if( query_temp("special2/aishang", me) )
        {                       
                addn_temp("apply/armor", -1*armor, me);
                addn_temp("apply/damage", -1*damage, me);
                addn_temp("apply/sword", -1*skill, me);
                addn_temp("apply/parry", -1*skill, me);
                addn_temp("apply/dodge", -1*skill, me);
                addn_temp("apply/force", -1*skill, me);
                delete_temp("special2/aishang", me);
                tell_object(me, HIG "你劍靈之哀傷施展完畢。\n" NOR);
        }
}
