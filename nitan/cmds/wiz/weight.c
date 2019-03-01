// weight.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        object env;
        int origin;
        string msg;
        string to;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        switch (arg)
        {
        case "light":
                if (me->query_weight() < 2)
                        return notify_fail("你已經輕的不能再輕了。\n");
                me->set_weight(me->query_weight() / 2);
                to = "輕";
                break;

        case "heavy":
                if (me->query_weight() >= 128 * 1024)
                        return notify_fail("你無法變得更重了。\n");
                if (! me->query_weight())
                        me->set_weight(1);
                else
                        me->set_weight(me->query_weight() * 2);
                to = "重";
                break;

        case "origin":
                origin=40000+(query("str", me)-10)*2000;
                if (origin > me->query_weight())
                        to = "重"; else
                if (origin < me->query_weight())
                        to = "輕"; else
                        return notify_fail("你的體重沒有任何變化。\n");

                me->set_weight(origin);
                break;

        default:
                help(me);
                return 1;
        }

        tell_object(me, HIM "嘩！你覺得你變得" + to + "了一些。\n" NOR);

        if (objectp(env = environment(me)))
        {
                message("vision", me->name() + "口中念念有詞，不知道"
                        "在幹些什麼。\n", env, ({ env, me }));

                if( userp(env) && !query("env/invisible", me) )
                        tell_object(env, HIM "你忽然覺得身上好像" +
                                         to + "了很多。\n" NOR);
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : miagic <light | heavy | origin>
 
這個指令會使你的重量變化，每次加倍或是減半。如果指明 origin
就恢復原來的體重。
 
HELP );
    return 1;
}