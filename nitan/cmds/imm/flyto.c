// flyto.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string home;
        object obj;
        string msg;

        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;

        if (! arg) return notify_fail("你要飛到哪兒去？\n");

        obj = MESSAGE_D->find_user(arg);
        if (! obj) obj = find_living(arg);
        if (! obj || ! me->visible(obj))
        {
                arg=resolve_path(query("cwd", me),arg);
                if (! sscanf(arg, "%*s.c")) arg += ".c";
                if (! (obj = find_object(arg)))
                {
                        if (file_size(arg) >= 0)
                                return me->move(arg);
                        return notify_fail("沒有這個玩家、生物、或地方。\n");
                }
        }

        while (obj && obj->is_character())
                       obj = environment(obj);

        if (obj == environment(me))
                return notify_fail("不就在你面前麼？亂飛個啥？\n");

        if (! obj) return notify_fail("這個物件沒有環境可以 flyto。\n");
        tell_object(me, "咦，怎麼還不起飛呢？……\n");
        tell_object(me, "呵呵呵呵，飛了飛了！小小巫師飛呀飛……！\n");
        if( !query("env/invisible", me) )
                message("vision", me->name() + "輕飄飄的飛了起來。\n",
                        environment(me), ({ me }));
        tell_object(me, "到了？到了！降落嘍！！！\n");
        if( !query("env/invisible", me) )
                message("vision", me->name() + "從天上慢慢的落了下來。\n", obj);
        me->move(obj);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : flyto <目標>
HELP);
            return 1;
}