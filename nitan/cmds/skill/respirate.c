// respirate.c

#include <skill.h>

inherit F_CLEAN_UP;

private int respirate_cost;
int respirating(object me);
int halt_respirate(object me);

int main(object me, string arg)
{
        seteuid(getuid());
        
        /*
        if( query("age", me)<24 )
                return notify_fail("你現在還年輕，以後再練吧！\n");
        */
        if( query("pigging", environment(me)) )
                return notify_fail("你還是專心拱豬吧！\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢！\n");

        if (me->is_fighting())
                return notify_fail("戰鬥中吐納，好象只有神仙才能做到。\n");

        if (! arg || ! sscanf(arg, "%d", respirate_cost))
                return notify_fail("你要花多少精修行？\n");

        if (respirate_cost <= 0)
                return notify_fail("你不是神仙！\n");

        if( query("jing", me)<respirate_cost )
                return notify_fail("你現在精不足，無法修行精力！\n");

        if( query("qi", me)*100/query("max_qi", me)<70 )
                return notify_fail("你現在身體狀況太差了，無法集中精神！\n");

        if( query("no_fight", environment(me)) && 
            (query("doing", me) != "scheme" || this_player(1)) )
                return notify_fail("你無法在這個地方安心吐納。\n");

        write("你閉上眼睛開始打坐。\n");
        set_temp("pending/respirate", 1, me);
        set_temp("respirate_cost", respirate_cost, me);
        me->set_short_desc("正坐在地下吐納煉精。");
        message_vision("$N盤膝坐下，開始吐納煉精。\n", me);
        me->start_busy(bind((:call_other, __FILE__, "respirating" :), me),
                       bind((:call_other, __FILE__, "halt_respirate" :), me));
        return 1;
}

int respirating(object me)
{
        int respirate_cost=query_temp("respirate_cost", me);
        int jingli_gain = (int)me->query_skill("force") / 10;
        jingli_gain = 1 + jingli_gain / 2 + random(jingli_gain);

        if (respirate_cost > 0)
        {
                if (jingli_gain > respirate_cost)
                        jingli_gain = respirate_cost;
        
                if( jingli_gain>query("jing", me) )
                {
                        jingli_gain=query("jing", me);
                        respirate_cost = 0;
                        set_temp("respirate_cost", 0, me);
                        me->set_short_desc(0);
                } else
                {
                        set_temp("respirate_cost",
                                     respirate_cost -= jingli_gain, me);
                }
        
                addn("jingli", jingli_gain, me);
                addn("jing", -jingli_gain, me);
        
                if (respirate_cost > 0)
                        return 1;
        }

        set_temp("pending/respirate", 0, me);
        me->set_short_desc(0);
        respirate_cost = 0;
        message_vision("$N吐納完畢，睜開雙眼，站了起來。\n", me);
        if( query("jingli", me)<query("max_jingli", me)*2 )
                return 0;
        else
        {
                if( query("max_jingli", me)>me->query_current_jingli_limit() )
                {
                        write("你的精力修為似乎已經達到了瓶頸。\n");
                        set("jingli",query("max_jingli",  me), me);
                        return 0;
                }
                else
                {
                        addn("max_jingli", 1, me);
                        set("jingli",query("max_jingli",  me), me);
                        write("你的精力增加了！！\n");
                        return 0;
                }
        }
}

int halt_respirate(object me)
{
        tell_object(me, "你將真氣壓回丹田，站了起來。\n");
        tell_room(environment(me), me->name() + "深吸一口氣，站了起來。\n", me);
        respirate_cost = 0;
        if( query("jingli", me)>query("max_jingli", me)*2 )
                set("jingli",query("max_jingli",  me)*2, me);
                        me->set_short_desc(0);
        set_temp("pending/respirate", 0, me);
        me->set_short_desc(0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : respirate|tuna [<耗費「精」的量>]
 
當你的年齡大于24歲以後，可以通過打坐修行，利用「煉精化氣，煉
氣化神，煉神還虛」的方法將你的精轉變成精力。注意：你不能在不
能戰鬥的地方吐納。

See also: exercise
HELP
        );
        return 1;
}
