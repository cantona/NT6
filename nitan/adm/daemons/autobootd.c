// This program is a part of NITAN MudLIB
// autobootd.c

#include <ansi.h>
#include <mudlib.h>
#include <net/daemons.h>

#define REBOOT_TIME     19 // autoboot at 19:00
#define STORAGE_D       "/adm/daemons/storaged.c"

nosave int last_time = 24*60*2; // minute
void reboot_mud();

int query_time() { return last_time; }
void set_time(int time) { last_time = time; }

void pass_time()
{
        if (last_time > 0) last_time -= 1;
}

void create()
{
        mixed *local;
        int t, r;

        seteuid(ROOT_UID);

        CHANNEL_D->channel_broadcast("sys", "自動重起系統已經啟動。\n");

#ifdef REBOOT_TIME
        local = localtime(time());
        t = local[2] * 60 + local[1];
        r = last_time - t + REBOOT_TIME * 60;
        set_time(r);
#endif

        call_out("reboot_mud", 60);
}

void reboot_mud()
{
        int i, last;
        object *user, link_ob;


        pass_time();
        last = query_time();

        if (last > 0 && last < 10)
                message_system(LOCAL_MUD_NAME() + "將在" +
                               chinese_number(last) + "分鐘以後重新啟動，請抓緊時間處理你的人物。");

        if (last > 0)
        {
                remove_call_out("reboot_mud");
                call_out("reboot_mud", 60);
                return;
        }

        // do reboot_mud
        seteuid(getuid());

        message_system("遊戲重新啟動，請稍候一分鐘再 login 。\n");

        // 保存所有的守護進程的數據
        reset_eval_cost();
        if (find_object(DNS_MASTER)) DNS_MASTER->send_shutdown();
        if (find_object(NAME_D))     NAME_D->mud_shutdown();
        if (find_object(FAMILY_D))   FAMILY_D->mud_shutdown();
        if (find_object(CLOSE_D))    CLOSE_D->mud_shutdown();
        if (find_object(DBASE_D))    DBASE_D->mud_shutdown();
        if (find_object(BUNCH_D))    BUNCH_D->mud_shutdown();
        if (find_object(LEAGUE_D))   LEAGUE_D->mud_shutdown();
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

string query_name()
{
        return "重起精靈(AUTOBOOT_D)";
}