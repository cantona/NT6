inherit F_CLEAN_UP;
#include <mudlib.h>
#include <getconfig.h>
#include <ansi.h>
#include <command.h>
#define SCALE   (1.0/10.0)
#define STATUS  "系統函數庫改寫中，遊戲正完善中"

string memory_expression(int m);
string dotime();

int count_ppls();

void create() { seteuid(getuid(this_object())); }

#ifdef LONELY_IMPROVED
string query_rusage_message()
{
        mapping networkstats = network_stats();
        return sprintf("已接收 %d 封包(%.2f/sec)，已傳送 %d 封包(%.2f/sec)",
                networkstats["incoming packets total"],
                to_float(networkstats["incoming packets total"])/uptime(),
                networkstats["outgoing packets total"],
                to_float(networkstats["outgoing packets total"])/uptime());
}
#endif

int main(object me)
{
        float value;
        mapping r;

        if( time()-query_temp("scan_time", me)<10
           && ! wizardp(me))
                return notify_fail("等等，系統喘氣中……\n");

        r = rusage();
        value = SCALE * (r["utime"] + r["stime"]) / uptime();

        write(NOR + WHT "\n\t\t         .__________ 系 統 資 訊 __________.\n");
        write(NOR + WHT "\t\t ─────────────────────────\n");
        write(NOR + WHT "\t\t 遊戲的識別名稱：  " + MUD_NAME + "\n");
        write(NOR + WHT "\t\t 界面系統的版本：  " + __VERSION__ + "\n");
        write(NOR + WHT "\t\t 系統函數庫版本：  " + MUDLIB_VERSION_NUMBER + "\n");
        printf(NOR + WHT "\t\t CPU 使用百分比：  %f %% 被這個遊戲使用中\n", value );
        write(NOR + WHT "\t\t CPU 的負擔狀況：  " + query_load_average() + "\n");
        printf(NOR + WHT "\t\t 共使用的記憶體：  %s bytes\n", memory_expression(memory_info()) );
        write(NOR + WHT "\t\t 線上使用者總數：  " + sizeof( users() ) + "  個人在線上\n");
        write(NOR + WHT "\t\t 注冊使用者總數：  " + DATABASE_D->db_count_user() + "  個人在本遊戲注冊\n");
        write(NOR + WHT "\t\t 載入的物件總數：  " + sizeof( objects() ) + " 個物件\n");
        write(NOR + WHT "\t\t 心跳總數的資訊：  " + sizeof(heart_beats()) + " 個\n");
        write(NOR + WHT "\t\t 延遲呼叫數資訊：  " + sizeof(call_out_info()) + " 個\n");
        write(NOR + WHT "\t\t 系統負載的資訊：  " + query_load_average() + "\n");
#ifdef LONELY_IMPROVED
        write(NOR + WHT "\t\t 訊息傳輸的資訊：  " + query_rusage_message() + "\n");
#endif
        write(NOR + WHT "\t\t 連續執行的時間：  " + dotime() + "\n");

        set_temp("scan_time", time(), me);

        return 1;
}

string memory_expression(int m)
{
        float mem;

        mem = m;
        if( mem<1024 ) return m + "";
        if( mem<1024*1024 )

                return sprintf("%.2f K", (float)mem / 1024);
        return sprintf("%.3f M", (float)mem / (1024*1024));
}

int count_ppls()
{
        int count,i;
        string *dir;
        string *ppls;

        seteuid(getuid());

        dir = get_dir(DATA_DIR + "login/");
        for(i=0; i<sizeof(dir); i++) {
        ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
        count += sizeof(ppls);
        }
        return count;
}

string dotime()
{
        int t, d, h, m, s;
        string time;

        t = uptime();
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if (d) time = chinese_number(d) + "天";
        else time = "";

        if (h) time += chinese_number(h) + "小時";
        if (m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒\n";

        return time;
}

int help() {

   write(@HELP
指令格式：mudinfo

這個指令將會顯示有關這個 Mud 的一些系統資訊。

HELP
        );
         return 1;
}

