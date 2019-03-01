// surrender.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        
        if( !me->is_fighting() )
                return notify_fail("投降？現在沒有人在打你啊....？\n");

        ob=query_temp("last_opponent", me);
        if( objectp(ob) && living(ob) && ob->is_killing(me) ) {
                message_vision("$N向$n求饒，但是$N大聲說道："
                        + RANK_D->query_rude(me) + "廢話少說，納命來！\n", ob, me);
                return 1;
        }

        me->remove_all_enemy();
        if( query("score", me) >= 50 )
                addn("score", -50, me);
        else
                set("score", 0, me);

        message_vision( HIW "\n$N說道：「不打了，不打了，我投降....。」\n\n" NOR, me);
        return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : surrender
 
這個指令可以讓你向敵人投降而終止戰鬥。
 
HELP
    );
    return 1;
}
 