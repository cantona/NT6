// say.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;
        mixed msg;

        if (me->ban_say(0))
                return 0;

        env = environment(me);
        if (! arg)
        {
                write("你自言自語不知道在説些什麼。\n");
                message("sound", me->name() + "自言自語不知道在説些什麼。\n",
                        env, me);
                return 1;
        }

        if( msg=query("no_say", env) )
        {
                if (stringp(msg))
                {
                        write(msg);
                        return 1;
                }

                write("這個地方不能講話。\n");
                return 1;
        }

        if( query("doing", me) == "scheme" )
        {
                if( query("jing", me)<100 )
                        return notify_fail("你現在的精神不濟，等一會兒吧。\n");
                addn("jing", -50, me);
        }

        write(CYN "你説道：" + arg + "\n" NOR);
        message("sound", CYN + me->name() + "[" + capitalize(query("id", me))+ "]" + CYN "説道：" +  arg + "\n" NOR,
                env, me);

        // The mudlib interface of say
        all_inventory(env)->relay_say(me, arg);
        me->add_msg_log("say", "你説道: "HIG+arg+NOR"\n");
        (all_inventory(env)-({ me }))->add_msg_log("say", me->query_idname()+"説道: "HIG+arg+NOR"\n");

        me->ban_say(1);

        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: say <訊息>
 
説話，所有跟你在同一個房間的人都會聽到你説的話。如果你設置了
auto_say參數，那麼系統會自動的將你輸入的非命令和表情動詞作為
你講的話處理。如果你設置了pure_say參數，那麼除非你輸入用 '/'
字符打頭的命令，否則系統都將當作你説的話來處理。
 
注: 本指令可用 ' 取代.
 
HELP
        );
        return 1;
}
