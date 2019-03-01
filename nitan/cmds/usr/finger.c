// finger.c

inherit F_CLEAN_UP;

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object *ob;

        if( !wizardp(me) && time()-query_temp("last_finger", me)<10 )
                return notify_fail("系統氣喘噓地嘆道：慢慢來 ....\n");  

        set_temp("last_finger", time(), me);

        if (! arg)
        {
                if( query("jing", me)<50 )
                        return notify_fail("你的精神無法集中。\n");

                if (! wizardp(me))
                        me->receive_damage("jing", 50);

                me->start_more(FINGER_D->finger_all());
        } else
        if (arg == "-m")
        {
                if (! wizardp(this_player()))
                        return notify_fail("你無權使用 -m 參數。\n");
                ob = filter_array(users(), (: $1->name() != $1->name(1) :));
                me->start_more(FINGER_D->user_list(ob), 0);
        } else
        {
                if( query("jing", me)<15 )
                        return notify_fail("你的精神無法集中。\n");

                if (! wizardp(me))
                        me->receive_damage("jing", 15);

                if ((arg == "lonely") && ! wizardp(me))
                        return notify_fail("沒有這個玩家。\n");

                write(FINGER_D->finger_user(arg));
        }
        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : finger [-m] [使用者姓名]
 
這個指令，如果沒有指定使用者姓明，會顯示出所有正在線上玩家
的連線資料。反之，則可顯示有關某個玩家的連線，權限等資料。
如果使用了 -m 參數，可以列出使用面具的玩家。
 
see also : who
HELP );
    return 1;
}