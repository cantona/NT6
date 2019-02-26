#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        object room;
        object obb;
        int step;
        string site;

        if (duration < 1) return 0;  
        
        me->apply_condition("jobjianlou_limit", duration - 1);  
        room = environment(me);     

        if( query_temp("guo_shoucheng/where", me) )
        if( query_temp("guo_shoucheng/where", me) != query("site", room )
         && !query_temp("guo_shoucheng/job_over", me) )
        {
                message_vision(HIY "一個宋兵跑過來對$N説道：你居然臨陣脱逃，" +
                               "我去報告郭大人！\n" NOR, me);

                set_temp("guo_shoucheng/failed", 1, me);
                me->apply_condition("jobjianlou_limit", 0);  
        }

        if( query_temp("guo_shoucheng/start_job", me )
         && query_temp("guo_shoucheng/where", me) == query("site", room) )
        {
                if (duration % 2 == 0 && duration > 20)     
                {
                        step = random(9) + 1;
                        message_vision(HIY "忽然$N從箭垛口似乎看到城下" HIW + chinese_number(step) +
                                       HIY "箭外有一名" HIR "蒙古箭手" HIY "在探頭探腦。\n" NOR, me);
                        obb = new("/quest/quest5/job2/robber4");
                        obb->move("/d/xiangyang/"+query("site", room)+step);
                        obb->change_ob(me);
                        set("where",query("site",  room), obb);
                } else
                if (duration % 10 == 0)  
                        message_vision(HIY "$N通過箭垛口警惕地巡視着城外的情況，" +
                                       "可是好像沒有發現任何敵情。\n" NOR, me);
        }

        if (me->is_ghost())
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobjianlou_limit", 0);
                return 0;
        }

        if (duration == 1
         && query_temp("guo_shoucheng/where", me) == query("site", room) )
        {
                message_vision(CYN "\n一個守城宋兵跑過來説道：蒙古靼子暫時被擊退了，" +
                               "$N可以回去覆命了！\n"NOR,me);
                if( query_temp("guo_shoucheng/start_job", me) )
                        set_temp("guo_shoucheng/job_over", 1, me);
                delete_temp("guo_shoucheng/start_job", me);
                me->apply_condition("jobjianlou_limit", 0);     
        }
        return CND_CONTINUE;      
}

