// team command: with

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;

        if (! arg ||
            ! (ob = present(arg, environment(me))) ||
            ! living(ob) ||
            ! ob->is_character() ||
            ob == me)
                return notify_fail("你想和誰成為伙伴？\n");

        if (! pointerp(me->query_team()) || me->is_team_leader())
        {
                if (sizeof(me->query_team()) >= 12)
                        return notify_fail("你這個隊伍裡面的人實在是太多"
                                           "了，大家都照顧不過來了。\n");

                if( me == query_temp("pending/team", ob) )
                {
                        if (! pointerp(me->query_team()))
                        {
                                ob->add_team_member(me);
                                message_vision("$N決定加入$n的隊伍。\n", me, ob);
                                MYGIFT_D->check_mygift(me, "newbie_mygift/zudui"); 
                                MYGIFT_D->check_mygift(ob, "newbie_mygift/zudui"); 
                        } else
                        {
                                me->add_team_member(ob);
                                message_vision("$N決定讓$n加入隊伍。\n", me, ob);
                                MYGIFT_D->check_mygift(me, "newbie_mygift/zudui"); 
                                MYGIFT_D->check_mygift(ob, "newbie_mygift/zudui"); 
                        }
                        delete_temp("pending/team", ob);
                        return 1;
                } else
                {
                        /*
                        if( query("level", ob)<query("level", me)-10 || 
                            query("level", ob)>query("level", me)+10 )
                                return notify_fail("你們的角色等級相差較大，無法組隊。\n");
                        */
                                
                        message_vision("$N邀請$n加入$P的隊伍。\n", me, ob);
                        tell_object(ob, YEL "如果你願意加入，請用 team with " +
                                    query("id", me)+"。\n"NOR);
                        set_temp("pending/team", ob, me);
                        return 1;
                }
        } else
                return notify_fail("只有隊伍領袖可以邀請別人加入。\n");
}
