// version.c

#include <getconfig.h>
#include <version.h>

inherit F_CLEAN_UP;

void show_version();

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int ver;

        if (arg == "stop" || arg == "cancel")
        {
                if (! SECURITY_D->valid_grant(me, "(admin)"))
                        return 0;

                if (VERSION_D->clear_syn_info())
                        write("清除了版本精靈正在的同步信息。\n");
                else
                        write("目前版本精靈沒有任何同步信息。\n");

                return 1;
        }

        if (arg == "sync" || arg == "SYNC")
        {
                if (! SECURITY_D->valid_grant(me, "(arch)"))
                {
                        write("你沒有權限同步" + LOCAL_MUD_NAME() +
                              "的版本。\n");
                        return 1;
                }

                if (arg == "sync" &&
                    intp(ver=query("VERSION_NO", get_object(VERSION_D))) && 
                    time() > ver && time() - ver < 86400)
                {
                        write("這個版本是最近一天生成的，你現在沒有必要再同步。\n");
                        return 1;
                }

                return VERSION_D->synchronize_version();
        }

        if (arg && sscanf(arg, "get %s", arg))
        {
                if (! SECURITY_D->valid_grant(me, "(admin)"))
                {
                        write("你沒有權限讀取服務器上的文件。\n");
                        return 1;
                }

                return VERSION_D->fetch_file(arg);
        }

        show_version();

        return 1;
}

void show_version()
{
        int ver;
        mapping si;
        int i;
        string k;
        int percent;

        if (! VERSION_D->is_version_ok())
        {
                write("目前版本正在同步中。\n");
                return;
        }

        if( !intp(ver=query("VERSION_NO", get_object(VERSION_D))) || !ver )
        {
                write(sprintf("%s目前運行的版本不祥。\n",
                              LOCAL_MUD_NAME()));
                return;
        }

        write(sprintf("%s目前運行的版本是：%O[%s 生成]\n",
                      LOCAL_MUD_NAME(), ver, ctime(ver)));
        if (wiz_level(this_player()) > wiz_level("(arch)") &&
            VERSION_D->is_release_server())
        {
                si = VERSION_D->query_socket_info();
                if (! mapp(si) || sizeof(si) < 1)
                        write("目前沒有其它站點在版本版本。\n");
                else
                {
                        write("目前有 " + sizeof(si) + " 個站點在同步版本中。\n");
                        i = 1;
                        foreach (k in keys(si))
                        {
                                if (si[k][FILE_SIZE] < 1)
                                        percent = 100;
                                else
                                        percent = si[k][FILE_POS] * 100 / si[k][FILE_SIZE];
        
                                if (percent > 100)
                                        percent = 100;

                                write(sprintf("%d. %s  正在傳送：%s(%d%%)\n",
                                              i, si[k][SUB_SITES],
                                              stringp(si[k][FILE_NAME]) ? si[k][FILE_NAME] : "未知文件",
                                              percent));
                        }
                        // 顯示下一個同步信息
                }
        }
}

int help(object me)
{
        write(@HELP
指令格式 : version [sync] | get <file>
 
這個指令會顯示遊戲目前所用的 MudLib 版本。如果指明了sync參數，
則系統將嘗試同步最新的版本。注意：在運行中同步是不可靠的，因
為系統不能自動的更新已經載入內存的對象，只有等所有內存中的對
象更新以後，版本才真正的同步了。因此同步完版本最好是重新啟動
MUD 或是手工更新(update)那些不同的地方。

使用 version get <file> 可以讀取服務器上 /version/  路徑下面
的某個文件。
 
HELP );
        return 1;
}
