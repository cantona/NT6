// junquest_song
// Updated by Lonely

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{      
        object room, jiang;  
        string temp;
        int liangcao;
        mapping jiangjun;

        room = environment(me);
 
        if (duration < 1) return 0;

        if (me != WAR_D->query_king())
        {
                me->apply_condition("junquest_song", 0);
                return 0;
        }

        if( (time()-query_temp("jun_quest/last_jiang", me))>500 )
        {
                jiangjun=query_temp("jun_quest/jiang", me);

                temp = read_file("/d/city2/song/liangcao", 1, 1);
                liangcao = atoi(temp);
                if( !jiangjun || sizeof(jiangjun)<query("degree_jungong", me)*2 )
                if (liangcao > 300 && objectp(room)
                && file_name(room) == "/d/city2/sying1")
                {
                        set_temp("jun_quest/last_jiang", time(), me);
                        tell_object(me,
                                    HIR "新征一批的宋軍到了，趕快加緊訓練吧！！！\n" NOR); 
                        liangcao = liangcao - 50;
                        temp = sprintf("%d", liangcao);
                        write_file("/d/city2/song/liangcao", temp, 1);
                        jiang = new("/d/city2/song/songb");
                        jiang->move(room);
                        jiang->change_ob();
                }
        }

        if (duration == 1)  
        {
                WAR_D->remove_enemy();     
                tell_object(me, HIR "蒙古大軍久攻不下，終于撤軍了！！！\n" NOR);
                tell_object(me, HIR "恭喜你勝利完成此次出征任務，擊敗來犯蒙軍實乃我朝之棟樑啊！！！\n" NOR);    
                WAR_D->give_bouns();
        }
        me->apply_condition("junquest_song", duration - 1); 

        return CND_CONTINUE;      
}

