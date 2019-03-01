// endlog.c
// created by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string wiz_status;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("請你指明一個玩家。\n");

        wiz_status = SECURITY_D->get_status(me);

        seteuid(getuid());

        if( EXAMINE_D->end_log_player(arg,query("id", me)) )
        {
                write("停止記錄(" + arg + ")的日志。\n");
                return 1;
        }

        return 0;
}

int help(object me)
{
        write(@HELP
指令格式: endlog <player>
 
停止記錄 <player> 的日志。如果這個玩家被設置為永久記錄日志，
則該項設置將取消。除了 admin，只有等級不亞于開始記錄日志者的
巫師才能夠取消記錄日志。
 
HELP );
        return 1;
}