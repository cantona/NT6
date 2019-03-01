// follow.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        if (me->is_chatter())
                return 0;

        if( !arg ) return notify_fail("指令格式：follow <某人>|none。\n");

        if( arg=="none")
                if( me->query_leader() ) {
                        me->set_leader(0);
                        write("Ok.\n");
                        return 1;
                } else {
                        write("你現在並沒有跟隨任何人。\n");
                        return 1;
                }

        if( query_temp("is_riding_follow", me) )
                return notify_fail("你還是先從坐騎上下來後在跟隨別人吧。 \n");

        if( !objectp(ob = present(arg, environment(me))) )
                return notify_fail("這裡沒有 " + arg + "。\n");

        if( !ob->is_character() )
                return notify_fail("什麼？跟隨...." + ob->name() + "。\n");

        if( ob==me )
                return notify_fail("跟隨自己？\n");

        me->set_leader(ob);
        message_vision("$N決定開始跟隨$n一起行動。\n", me, ob);

        return 1;
}

int help (object me)
{
        write(@HELP
指令格式 : follow [<生物>|none]
 
這個指令讓你能跟隨某人或生物。
如果輸入 follow none 則停止跟隨。
 
HELP
);
        return 1;
}
