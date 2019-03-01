// exercise.c
// Updated by Lonely

#include <skill.h>

inherit F_CLEAN_UP;

int exercising(object me);
int halt_exercise(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        mapping msg;
        int exercise_cost;
        string force;
        object where;
        int n;

        seteuid(getuid());
        where = environment(me);

        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙著呢。\n");

        if (me->is_fighting())
                return notify_fail("戰鬥中不能練內功，會走火入魔。\n");

        if (! stringp(force = me->query_skill_mapped("force")))
                return notify_fail("你必須先用 enable 選擇你要用的內功心法。\n");

        if (! arg || ! sscanf(arg, "%d", exercise_cost))
                return notify_fail("你要花多少氣練功？\n");

        if (exercise_cost < 10)
                return notify_fail("你的內功還沒有達到那個境界！\n");

        if( query("qi", me)<exercise_cost )
                return notify_fail("你現在的氣太少了，無法產生內息運行全身經脈。\n");

        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("你現在精不夠，無法控制內息的流動！\n");

        if( query("no_fight", environment(me)) && 
            //(query("doing", me) != "scheme" || this_player(1)) )
            (query("doing", me) != "scheme") )
                return notify_fail("你無法在這個地方安心打坐。\n");

        notify_fail("你無法順利的運轉內息。\n");
        if (SKILL_D(force)->do_effect(me))
                return 0;
        
        msg = SKILL_D(force)->exercise_msg(me);
        
        if (! msg || undefinedp(msg["start_self"]))
                write("你坐下來運氣用功，一股內息開始在體內流動。\n");
        else 
                write(msg["start_self"]);

        set_temp("pending/exercise", 1, me);
        set_temp("exercise_cost", exercise_cost, me);
        
        if (! msg || undefinedp(msg["apply_short"]))        
                me->set_short_desc("正坐在地下修煉內力。");
        else
                me->set_short_desc(msg["apply_short"]);

        if (! msg || undefinedp(msg["start_other"]))
                tell_room(environment(me), me->name() + "盤膝坐下，開始修煉內力。\n", me);
        else
                tell_room(environment(me), msg["start_other"], me); 
                                            
        me->start_busy(bind((:call_other, __FILE__, "exercising" :), me),
                       bind((:call_other, __FILE__, "halt_exercise" :), me));
        return 1;
}

int exercising(object me)
{
        mapping msg;
        string force;
        int exercise_cost=query_temp("exercise_cost", me);
/*
        int neili_gain = (int)me->query_skill("force") / 2;

        neili_gain = 1 + neili_gain / 2 + random(neili_gain) +
                     query("exercise_improve", environment(me));
*/
        int neili_gain = (int)me->query_skill("force") * 2;
        if (neili_gain < 0) neili_gain = 1;
        if (exercise_cost > 2*neili_gain) neili_gain = exercise_cost/2;

        if (stringp(force = me->query_skill_mapped("force")))
                msg = SKILL_D(force)->exercise_msg(me);
        
        if (exercise_cost > 0)
        {
                if (neili_gain > exercise_cost)
                        neili_gain = exercise_cost;
                
                if( neili_gain>query("qi", me) )
                {
                        neili_gain=query("qi", me);
                        set_temp("exercise_cost", 0, me);
                        me->set_short_desc(0);
                        exercise_cost = 0;
                } else
                {
                        set_temp("exercise_cost", exercise_cost-=neili_gain, me);
                }
                addn("neili", neili_gain, me);
                addn("qi", -neili_gain, me);
                
                if (exercise_cost > 0)
                {
                        if (! random(3) && mapp(msg) && ! undefinedp(msg["exercise_msg"]))
                                tell_object(me, msg["exercise_msg"]);
                        return 1;
                }
        }

        set_temp("pending/exercise", 0, me);
        me->set_short_desc(0);
        
        if (! msg || undefinedp(msg["finish_self"]))
                tell_object(me, "你只覺內息運轉順暢，將真氣還合丹田，站了起來。\n");
        else
                tell_object(me, msg["finish_self"]);
        
        if (! msg || undefinedp(msg["finish_other"]))
                tell_room(environment(me), me->name() + "運功完畢，深深吸了口氣，站了起來。\n", me);
        else
                tell_room(environment(me), msg["finish_other"], me);
                                        
        if( query("neili", me)<query("max_neili", me)*2 )
                return 0;
        else
        {
                if( query("max_neili", me) >= me->query_current_neili_limit() )
                {
                        write("你的內力修為似乎已經達到了瓶頸。\n");
                        set("neili",query("max_neili",  me), me);
                        return 0;
                } else
                {
                        addn("max_neili", 1, me);
                        set("neili",query("max_neili",  me), me);
                        write("你的內力增加了！！\n");
                        return 0;
                }
        }
}

int halt_exercise(object me)
{
             mapping msg;
        string force;

        if (stringp(force = me->query_skill_mapped("force")))
                msg = SKILL_D(force)->exercise_msg(me);

        if (! msg || undefinedp(msg["halt_self"]))                        
                tell_object(me, "你將真氣壓回丹田，站了起來。\n");
        else 
                tell_object(me, msg["halt_self"]);
                
        if (! msg || undefinedp(msg["halt_other"]))                  
                tell_room(environment(me), me->name() + "深吸一口氣，站了起來。\n", me);
        else
                tell_room(environment(me), msg["halt_other"], me);                        
         
        if( query("neili", me)>query("max_neili", me)*2 )
                set("neili",query("max_neili",  me)*2, me);
        set_temp("pending/exercise", 0, me);
        me->set_short_desc(0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : exercise|dazuo [<耗費「氣」的量> 必須多于 10]

運氣練功，控制體內的氣在各經脈間流動，藉以訓練人體肌肉骨骼的耐
力、爆發力，並且用內力的形式將能量儲備下來。注意：你不能在不能
戰鬥的地方打坐。

HELP );
        return 1;
}
