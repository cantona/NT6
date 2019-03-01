// go.c

#include <ansi.h>
#include <command.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;
void send_exits(object me, object env);

int main(object me, mapping info)
{
        string arg;
        object env;
        object ob;
        mapping exits;

        if (! objectp(env = environment(me)) || env == find_object(VOID_OB))
        {
                MESSAGE_D->tell_user(me, FUN_NOTICE, "你現在處在縹緲的"
                                     "虛空中，四周一片茫茫，沒什麼地方好去的。\n");
                return 1;
        }

        arg = info[ARG];
        if (! stringp(arg))
        {
                send_exits(me, env);
                return MESSAGE_D->error_msg("你要去哪裡？\n");
        }

        if( !mapp(exits=query("exits", env)) )
        {
                send_exits(me, env);
                return MESSAGE_D->error_msg("這裡四周都沒有出口，你無路可走。\n");
        }

        if (! exits[arg])
        {
                send_exits(me, env);
                if( query("outdoor", env) )
                        return MESSAGE_D->error_msg("你抬腿想走，卻看到一堵牆。\n");
                else
                        return MESSAGE_D->error_msg("這個方向沒有出口。\n");
        }

        call_other(exits[arg], "???");
        if (! find_object(ob = exits[arg]))
        {
                send_exits(me, env);
                return MESSAGE_D->error_msg("系統遇到了錯誤，無法完成你的操作。\n");
        }

        if( !wizardp(me) || !query("env/invisible", me) )
        {
                message("vision", me->name() + "飄飄忽忽的離開這裡。\n",
                        environment(me), ({ me }));
                message("vision", me->name() + "飄飄忽忽的遊盪了過來。\n",
                        ob, ({ me }));
        }

        if (! me->move(ob))
        {
                send_exits(me, env);
                return MESSAGE_D->error_msg("你無法移動到指定的地點。\n");
        }

        return 1;
}

void send_exits(object me, object env)
{
        if( mapp(query("exits", env)) )
                // notice the user all the exits
                MESSAGE_D->tell_user(me,FUN_EXITS,implode(keys(query("exits", env)),"\n"));
}
