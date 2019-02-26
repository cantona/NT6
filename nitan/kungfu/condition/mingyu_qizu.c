// by sinb

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int i;
        string msg;
        
        if (me->query_condition("killer") &&
            query("no_fight", environment(me)) )
        {
                tell_object(me, HIR "你發現你的明玉功好像受到限制，氣血未能自動恢復！\n" NOR );
        }
        else
        {
                tell_object(me, HIR "你的明玉功發揮了奇效，感覺損失的氣血在慢慢恢復！\n" NOR );
                message_vision(HIW "$N眼睛中射出異樣光芒，身上的傷口奇蹟般地癒合了。\n" NOR, me);
        
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                addn("neili", -100, me);
        }
        
        me->apply_condition("mingyu_qizu", duration - 1);
        
        if( duration < 1 ) 
        {
                message_vision(HIC "$N的「氣足」奇功運行完畢，臉色頓時一片蒼白。\n" NOR, me);

                return 0;
        }
        return CND_CONTINUE;
}
