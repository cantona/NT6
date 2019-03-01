#include <ansi.h>

#include <login.h>

int update_condition(object me, int duration)
{
        object room;
        object ob;
          object obb;
        object* inv;
        int i;
                
        ob=this_player();
        room = environment(ob);     

        if( query_temp("where", me)){
        if( query_temp("where", me) != environment(me)){
                message_vision(HIY"一個宋兵跑過來對$N說道：叫你守城，你卻到處閒逛，我去報告郭大人！\n"NOR,me);
                set_temp("job_failed", 1, me);
                return 0;
        }
        }

        if( query_temp("start_job", me)){
        message_vision(HIY"$N正站在城牆上密切注視著城下"HIR"蒙古兵"HIY"的一舉一動。\n"NOR,ob);
        }
        me->apply_condition("jobshadi_limit", duration - 1);

        if(duration<1)
        {
                message_vision(CYN"\n一個守城宋兵跑過來說道：蒙古靼子暫時被擊退了，$N可以回去復命了！\n"NOR,ob);
        if( query_temp("start_job", me)){
                set_temp("job_over", 1, ob);
        }
                delete_temp("start_job", ob);
                inv=all_inventory(room);
                for (i = 0; i < sizeof(inv); i++) {
                     obb=inv[i];
                        if (obb->is_character()) {
                        if( query("ygjg", obb) == ob)destruct(obb);
                    }
                        continue;
                }
                return 0;
        }
        return 1;
}