// haha
// f.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string msg;
        string target;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg) return notify_fail("你要控制誰做什麼？\n");

        if (sscanf(arg, "%s to %s", target, arg) != 2 ||
            ! objectp(ob = find_player(target)) &&
            ! objectp(ob = present(target, environment(me))) &&
            ! objectp(ob = find_living(target)))
        {
                // 沒有這個對象，查看最後一次的控制對象
                if( !objectp(ob=query_temp("last_control", me)) )
                        return notify_fail("這裡沒有這個人可供你控制。\n");
                if (stringp(target)) arg = target + " " + arg;
        }

        if (ob == me)
                return notify_fail("控制自己？....你好象不太正常啊。\n");

        if (wiz_level(me) <= wiz_level(ob) &&
            wiz_level(ob) && ! is_root(me))
                return notify_fail("你不能控制權限比自己高的巫師。\n");

        set_temp("last_control", ob, me);
        delete_temp("notify_fail", ob);
        if (! ob->force_me(arg))
        {
                ob->command(arg);
                if( !stringp(msg=query_temp("notify_fail", ob)) )
                        msg = ob->name(1) + "無法執行你的命令。\n";
                write(msg);
        }

        return 1;
}

int help(object me)
{
        write( @HELP
指令格式: f <sb> to do sth.

這個指令讓你控制另外一個人物進行動作，如果你是連續控制某個人，
那麼以後不需要在輸入這個ID。
HELP );
        return 1;
}

