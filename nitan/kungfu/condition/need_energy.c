// need_energy.c

#include <condition.h>
#include <ansi.h>

int dispel() { return 0; }

int update_condition(object me, int duration)
{
        object ob;
        
        if( query("food", me)>0 && query("water", me)>0 )
                return 0;

        if (! environment(me) ||
            environment(me)->is_chat_room())
                return CND_CONTINUE;

        if (duration == 4)
        {
                if( objectp(ob=find_player(query("owner", me))) )
                        tell_object(ob,HIR"你的魔幻獸("+query("name", me)+HIR+")快要餓死了！\n"NOR);
                        
                message_vision(HIY "$N" HIY "看起來又飢又渴，已經疲憊不堪。\n" NOR, me);
        }
        else
        if (duration == 7)
        {
                if( objectp(ob=find_player(query("owner", me))) )
                        tell_object(ob,HIR"你的魔幻獸("+query("name", me)+HIR+")快要餓死了！\n"NOR);
                                        
                message_vision(HIY "$N" HIY "看起來又飢又渴，處於死亡的邊緣。\n" NOR, me);
        }
        else
        if (duration >= 21)
        {
                if( objectp(ob=find_player(query("owner", me))) )
                        tell_object(ob,HIY"你的魔幻獸("+query("name", me)+HIY+")已經餓死了！\n"NOR);
                
                me->receive_damage("qi", 0);
                me->unconcious();
                return 0;
        } 
                                              
        me->apply_condition("need_energy", duration + 1);
        return CND_CONTINUE;
}
