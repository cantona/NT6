// log.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string wiz_status;
        mapping log;
        string *ks;
        object *obs;
        string msg;
        int i;
        int flag;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg || arg == "")
                return notify_fail("請你指明一個玩家。\n");

        seteuid(getuid());
        if (arg == "?")
        {
                log=query("log_by", get_object(EXAMINE_D));
                msg = "";
                if (mapp(log) && sizeof(log) > 0)
                {
                        ks = keys(log);
                        flag = 0;
                        for (i = 0; i < sizeof(ks); i++)
                        {
                                if (wiz_level(me) < wiz_level(log[ks[i]]))
                                        continue;

                                if (! flag)
                                {
                                        msg +=HIW "\n目前記錄的情況如下：\n"
                                              HIY "────────────────────────\n" NOR;
                                        flag = 1;
                                }
                                msg += sprintf("%s%-14s  目前被  %-14s 記錄日誌。\n" NOR,
                                        (wizhood(me) == "(player)") ? CYN : HIY,
                                        ks[i], log[ks[i]]);
                        }
                }

                obs = filter_array(users(), (: $1->is_loging_now() :));
                obs = sort_array(obs, (: wiz_level($1) - wiz_level($2) :));
                flag = 0;
                for (i = 0; i < sizeof(obs); i++)
                {
                        string nid;

                        if (! flag)
                        {
                                msg += HIW "\n目前正在記錄的使用者情況如下：\n"
                                       HIY "────────────────────────\n" NOR;
                                flag = 1;
                        }

                        nid=obs[i]->name(1)+"("+query("id", obs[i])+")";
                        msg += sprintf("%s%-20s  " HIC "%-10s  %s\n" NOR,
                                       wizardp(obs[i]) ? HIY : CYN,
                                       nid,
                                       environment(obs[i]) ? environment(obs[i])->short() : "未知地點",
                                       interactive(obs[i]) ? HIG + query_ip_name(obs[i]) : HIR "斷線");
                }
                if (! flag)
                        msg += "目前沒有在線玩家被記錄日誌。\n";
                else
                        msg += "\n";
                write(msg);
                return 1;
        }

        if (file_size(DATA_DIR + "login/" + arg[0..0] + "/" + arg + __SAVE_EXTENSION__) < 0)
                return notify_fail("咦... 沒有這個玩家啊！\n");

        if (wiz_level(me) < wiz_level(arg))
                return notify_fail("你不能為自己權限高的人紀錄日誌。\n");

        if (wizhood(arg) == "(admin)" && ! me->is_admin())
                return notify_fail("你不能記錄天神的日誌。\n");

        if( EXAMINE_D->start_log_player(arg,query("id", me)) )
        {
                write("開始記錄(" + arg + ")的日誌。\n");
                return 1;
        }

        return 0;
}

int help (object me)
{
        write(@HELP
指令格式: log <player> | ?
 
記錄 <player> 的日誌，日誌文件生成在 /log/user/player 下面。
如果沒有聲明停止記錄該玩家的日誌，系統將一直記錄下去，即使
退出後重新連線進入也不會停止。

如果輸入 ? 作為參數，列出當前記錄的情況。
 
HELP );
        return 1;
}
