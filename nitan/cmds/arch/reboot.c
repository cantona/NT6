// reboot.c
// created by doing

#include <net/daemons.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

#ifndef STORAGE_D
#define STORAGE_D "/adm/daemons/storaged.c"
#endif

// 啟動的時間
int start_reboot = 0;
int last_notice = 0;

int is_rebooting() { return start_reboot != 0; }

protected void reboot_mud();

int main(object me, string arg)
{
        string str;
        int n;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
        {
                write("指令格式: shutdown [-f] | soon | after <n>\n");
                return 1;
        }

        str = me->name(1) + "(" + query("id", me) + ")";
        if (arg == "-f")
        {
                if (! find_object(SECURITY_D) ||
                    ! find_object(SIMUL_EFUN_OB) ||
                    ! find_object(MASTER_OB))
                        shutdown(0);

                if (! is_root(me))
                {
                        write("你沒有權限強制停止" + LOCAL_MUD_NAME() + "。\n");
                        return 1;
                }

                message_system(str + "強行啟動了" + LOCAL_MUD_NAME() + "。");
                shutdown(0);
                return 1;
        }

        if (wiz_level(me) < 4)
        {
                write("你沒有權限重新啟動" + LOCAL_MUD_NAME() + "。\n");
                return 1;
        }

        if (sscanf(arg, "after %d", n) != 1)
        {
                if (arg != "soon")
                {
                        if (arg != "cancel")
                        {
                                write("參數錯誤，請查看幫助。\n");
                                return 1;
                        }

                        if (start_reboot)
                        {
                                start_reboot = 0;
                                set_heart_beat(0);
                                message_system(str + "取消了啟動，遊戲繼續進行。");
                                write("Ok.\n");
                                return 1;
                        }

                        write("現在MUD正在正常的運行。\n");
                        return 1;
                }
                message_system(str + "重新啟動了" + LOCAL_MUD_NAME() + "。");
                reboot_mud();
        }

        if (n < 1)
        {
                write("沒有這麼短的時間，你不如選擇 soon 立刻啟動。\n");
                return 1;
        }

        if (n > 10)
        {
                write("這麼久？你還是等一會兒再啟動吧。\n");
                return 1;
        }

        start_reboot = time() + n * 60;
        last_notice = time();
        set_heart_beat(1);
        message_system(str + "決定在" + chinese_number(n) +
                       "分鐘以後重新啟動" + LOCAL_MUD_NAME() + "。");
        return 1;
}

protected void heart_beat()
{
        int t;
        int n;
        string str;

        if (! start_reboot) return;

        n = start_reboot - time();
        if (n < 1)
        {
                reboot_mud();
                return;
        }

        if (n >= 60) str = chinese_number(n / 60) + "分鐘"; else
                     str = "";
        if (n % 60) str += chinese_number(n % 60) + "秒";

        t = time() - last_notice;
        if ((n >= 60 && t >= 60) || (n < 60 && n >= 10 && t >= 10) || n < 10)
        {
                message_system(LOCAL_MUD_NAME() + "將在" +
                               str + "以後重新啟動，請抓緊時間處理你的人物。");
                last_notice = time();
        }
}

protected void reboot_mud()
{
        object *user, link_ob;
        int i;

        message_system("遊戲重新啟動，請稍候一分鐘再 login 。\n");

        // 保存所有的守護進程的數據
        reset_eval_cost();
        if (find_object(INTERMUD2_D))INTERMUD2_D->mud_shutdown();
        if (find_object(NAME_D))     NAME_D->mud_shutdown();
        if (find_object(CLOSE_D))    CLOSE_D->mud_shutdown();
        if (find_object(DBASE_D))    DBASE_D->mud_shutdown();
        if (find_object(SKILLS_D))   SKILLS_D->mud_shutdown();
        if (find_object(STORAGE_D))  STORAGE_D->mud_shutdown();
        user = users();
        for (i = 0; i < sizeof(user); i++)
        {
                reset_eval_cost();
                if (! environment(user[i])) continue;
                delete("quest_dg", user[i]);
                delete("quest_kh", user[i]);
                delete("quest_hs", user[i]);
                delete("quest_sn", user[i]);
                delete("quest", user[i]);
                user[i]->save();
                link_ob=query_temp("link_ob", user[i]);
                if (objectp(link_ob)) link_ob->save();
        }

        shutdown(0);
}

int help (object me)
{
        write(@HELP
指令格式: shutdown [-f] | soon | after <n> | cancel

重新起動遊戲。如果採用 -f 參數，則系統強制啟動，而不保存任何
進度，這是供系統出錯時使用的。如果使用了參數soon，則系統將立
刻重新啟動，而使用 after n 則系統將在 n 分鐘以後重新啟動。

使用了 -f 參數則 soon 和 after 無效。

如果使用了 after 參數，可以使用 cancel 參數中止啟動的過程。

HELP );
        return 1;
}
