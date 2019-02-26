/*固定活動管理系統，用於管理每日每週定時活動的啟動和通知
周：
  1、擂台打榜           20:00-23:00  無需啟動
  2、自由戰場           19:30-22:30  無需啟動
  3、幫戰之冰火島遠征   20:00-21:30  需要啟動
  4、襄陽保衞戰         20:30-21:30  需要啟動
  5、幫派大作戰         20:30-22:00  需要啟動
     繽紛週末活動       20:00-23:59  無需啟動
  6、幫戰之冰火島遠征   20:00-21:30  需要啟動
     自由戰場           13:00-20:00  無需啟動
     繽紛週末活動       00:00-23:59  無需啟動
  7、襄陽保衞戰         20:30-21:30  需要啟動
     幫派大作戰         20:30-22:00  需要啟動
     繽紛週末活動       00:00-23:59  無需啟動
*/
#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

#include <ansi.h>

#define MEMBER_D     "/adm/daemons/memberd"
#define STR_SPRINTF    "%-10s%-20s%-20s%-20s\n"

// 記錄周活動顯示的信息，避免重複計算
nosave string strshow = "";
// 記錄time對應的天數
nosave int current_day = 0;

// 函數聲明
public string get_week_num(int dtime);
public void show_week_huodong(string sday);
public void do_channel(string ch, string msg);
public int can_start_huodong(string huodong);

// 通過ctime()返回 Fri Dec 31 17:04:17 2010 取第一個空格前的
nosave mapping week_time = ([
        "Mon"  : "1", 
        "Tue"  : "2",
        "Wed"  : "3",
        "Thu"  : "4",
        "Fri"  : "5",
        "Sat"  : "6",
        "Sun"  : "7",
]);

// 用於顯示的活動列表，不參與計算，僅做顯示
nosave mapping huodong_list = ([
        "1"   :  sprintf(STR_SPRINTF, "週一", "擂台打榜", "19:00-23:00", "help biwu"),
        
        "2"   :  sprintf(STR_SPRINTF, "週二", "自由戰場", "19:00-20:30", "help war_free"),
        
        "3"   :  sprintf(STR_SPRINTF, "週三", "冰火島遠征", "20:00-21:30", "help league.war"),
        
        "4"   :  sprintf(STR_SPRINTF, "週四", "襄陽保衞戰", "21:30-22:30", "help xywar"),
        
        "5"   :  sprintf(STR_SPRINTF, "週五", "繽紛週末活動", "20:00-23:59", "help wkgift") +
                 sprintf(STR_SPRINTF, "    ", "幫派大作戰", "20:00-21:30", "help league.fight"),
                 
        "6"   :  sprintf(STR_SPRINTF, "週六", "繽紛週末活動", "00:00-23:59", "help wkgift") +
                 sprintf(STR_SPRINTF, "    ", "自由戰場", "13:00-20:00", "help war_free") +
                 sprintf(STR_SPRINTF, "    ", "冰火島遠征", "20:00-21:30", "help league.war"),

        "7"   :  sprintf(STR_SPRINTF, "週日", "繽紛週末活動", "00:00-23:59", "help wkgift") +
                 sprintf(STR_SPRINTF, "    ", "襄陽保衞戰", "21:30-22:30", "help xywar") +
                 sprintf(STR_SPRINTF, "    ", "幫派大作戰", "20:00-21:30", "help league.fight"),
]);

// 顯示所有的周活動或指定某日活動
public void show_week_huodong(string sday)
{
        string str;
        int i;

        str = sprintf(HIC + STR_SPRINTF + NOR, "活動日", "活動名", "時間", "幫助文件"); 
        str += "=-----------------------------------------------------------------------------=\n";
        
        if (sday != "all")
        {
                str += HIG + huodong_list[sday] + NOR;
        }
        else
        {
                if (! sizeof(strshow) || current_day != time() / 86400 )
                {
                        strshow = "";
                        for(i = 0; i < sizeof(huodong_list); i ++)
                        {
                                if (get_week_num(time()) == sprintf("%d", i+1))
                                        strshow += HIR + huodong_list[sprintf("%d", i+1)] + NOR;
                                else
                                {
                                        if ((i+1)%2==0) // 分單雙錯開顏色
                                                strshow += HIG + huodong_list[sprintf("%d", i+1)] + NOR;
                                        else
                                                strshow += HIY + huodong_list[sprintf("%d", i+1)] + NOR;
                                }
                        }
                        current_day = time() / 86400;
                }
                str += strshow;
        }
        str += "=-----------------------------------------------------------------------------=\n";
        if (sday == "all")
        {
                str += HIR "紅色部分表示今天的活動！\n" NOR; 
                str =  "\n" HIY + "【炎黃每日活動列表  -- 歡迎參與】\n" + str + NOR;
        }
        write(str);
}

// 返回當前時間是周幾，用字符串返回，週一則是“1”
public string get_week_num(int dtime)
{
        int strweek, strtemp;
        sscanf(ctime(dtime), "%s %s", strweek, strtemp);
        return week_time[strweek];
}


void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(10); // 20秒心跳一次

        set("channel_id", HIY "活動使者" NOR);
}

void remove(){save();}

// 發佈全屏通告
public void do_channel(string ch, string msg)
{
        CHANNEL_D->do_channel(this_object(), ch, msg);
}

public void mud_shutdown(){save();}

/* 每1分鐘次的心跳 用於檢查活動開啟
   通過dbase記錄每個活動上次舉辦的時間，避免因為當機等引起的重複舉行或未舉行
   sday 代表周幾 如週一則sday = "1"
   query("huodong_info/sday, ([
        "活動名1"  : 啟動時間,
        "活動名2"  : 啟動時間,
   ]))
*/
void heart_beat()
{
        string wk, strtime, str_hour, str_min, today;
        string *keys_strtime;
        int nhour, nmin, ntime;
        
        ntime = time(); 
        wk = get_week_num(ntime);
        strtime = MEMBER_D->bjtime(ntime, 0);
        keys_strtime = explode(strtime, ":");
        str_hour = keys_strtime[3];
        str_min = keys_strtime[4];
        sscanf(str_hour, "%d", nhour);
        sscanf(str_min, "%d", nmin);

        today = sprintf("%d", ntime / 86400);
        
        switch(wk) // 星期幾
        {
        case "1": // 擂台打榜活動 19:30-23:30
                if (! query("huodong_info/" + today + "/擂台打榜")) // 還未舉行
                {
                        if (nhour == 19)
                        {
                                // 開始活動
                                do_channel("chat", HIG "比武挑戰活動已經開啟，歡迎上台一展身手，" +
                                                       "詳情見 help biwu 幫助。\n" NOR);
                                // 記錄開始時間
                                set("huodong_info/" + today + "/擂台打榜", ntime);
                        }
                }
        break;
        
        case "2": // "自由戰場", "19:00-22:00"
                if (! query("huodong_info/" + today + "/自由戰場")) // 還未舉行
                {
                        if (nhour == 19)
                        {
                                // 開始活動
                                do_channel("chat", HIG "自由戰場活動已經開啟，為了榮譽而戰吧。" +
                                                       "詳情見 help war_free 幫助。\n" NOR);
                                // 初始化
                                WAR_D->init_all_war();
                                // 記錄開始時間
                                set("huodong_info/" + today + "/自由戰場", ntime);
                        }
                }
        break;
        
        case "3": // "週三", "冰火島遠征",20:00-21:30"
                if (! query("huodong_info/" + today + "/冰火島遠征")) // 還未舉行
                {
                        if (nhour == 20)
                        {
                                // 開始活動
                                if (! LEAGUE_D->is_in_leaguewar())
                                        LEAGUE_D->start_leaguewar();
                                // 記錄開始時間
                                set("huodong_info/" + today + "/冰火島遠征", ntime);
                        }
                }
        break;

        case "4": // "週四", "襄陽保衞戰", "21:30-22:30",
                if (! query("huodong_info/" + today + "/襄陽保衞戰")) // 還未舉行
                {
                        if (nhour == 21 && nmin == 30)
                        {
                                // 開始活動
                                if (XYWAR_D->now_status() == 0)
                                        XYWAR_D->start_xywar();
                                // 記錄開始時間
                                set("huodong_info/" + today + "/襄陽保衞戰", ntime);
                        }
                }
        break;
        
        case "5": //"週五", "繽紛週末活動", "20:00-23:59"
                  //        "幫派大作戰", "20:00-22:00"
                if (! query("huodong_info/" + today + "/幫派大作戰")) // 還未舉行
                {
                        if (nhour == 20)
                        {
                                // 開始活動
                                LEAGUEFIGHT_D->start_leaguefitht();
                                // 記錄開始時間
                                set("huodong_info/" + today + "/幫派大作戰", ntime);
                        }
                }               
        break;
        
        case "6": // 週六
                  //        "週六", "繽紛週末活動", "00:00-23:59"
                  //        "自由戰場", "13:00-20:00"
                  //        "冰火島遠征", "20:00-21:30"
                if (! query("huodong_info/" + today + "/自由戰場")) // 還未舉行
                {
                        if (nhour == 13)
                        {
                                // 開始活動
                                do_channel("chat", HIG "自由戰場活動已經開啟，為了榮譽而戰吧。" +
                                                       "詳情見 help war_free 幫助。\n" NOR);
                                // 初始化
                                WAR_D->init_all_war();                      
                                // 記錄開始時間
                                set("huodong_info/" + today + "/自由戰場", ntime);
                        }
                }
                if (! query("huodong_info/" + today + "/冰火島遠征")) // 還未舉行
                {
                        if (nhour == 20)
                        {
                                // 開始活動
                                if (! LEAGUE_D->is_in_leaguewar())
                                        LEAGUE_D->start_leaguewar();
                                // 記錄開始時間
                                set("huodong_info/" + today + "/冰火島遠征", ntime);
                        }
                }
        break;

        case "7":  // 週日
                  //        "週日", "繽紛週末活動", "00:00-23:59"
                  //        "襄陽保衞戰", "21:30-22:30"
                  //        "幫派大作戰", "20:00-22:30"
                if (! query("huodong_info/" + today + "/襄陽保衞戰")) // 還未舉行
                {
                        if (nhour == 21 && nmin == 30)
                        {
                                // 開始活動
                                if (XYWAR_D->now_status() == 0)
                                        XYWAR_D->start_xywar();
                                // 記錄開始時間
                                set("huodong_info/" + today + "/襄陽保衞戰", ntime);
                        }
                }
                if (! query("huodong_info/" + today + "/幫派大作戰")) // 還未舉行
                {
                        if (nhour == 20)
                        {
                                // 開始活動
                                LEAGUEFIGHT_D->start_leaguefitht();
                                // 記錄開始時間
                                set("huodong_info/" + today + "/幫派大作戰", ntime);
                        }
                }
        break;  

        default:
        return;
        }

        return;
}

// 來自city biwu_dating ,yinghao_dating, xinrui_datin調用
// 是否可以開始比武
public int can_start_huodong(string huodong)
{
        string wk, strtime, str_hour, str_min, today;
        string *keys_strtime;
        int nhour, nmin, ntime;
        
        ntime = time();
        wk = get_week_num(ntime);
        strtime = MEMBER_D->bjtime(ntime, 0);
        keys_strtime = explode(strtime, ":");
        str_hour = keys_strtime[3];
        str_min = keys_strtime[4];
        sscanf(str_hour, "%d", nhour);
        sscanf(str_min, "%d", nmin);
        str_min = keys_strtime[4];
        today = sprintf("%d", ntime / 86400);
        
        switch(huodong)
        {
        case "biwu": // 比武打榜 19:00 - 23:00
                if (wk == "1" && 
                   nhour >= 19 && nhour < 23)return 1;
                else
                {
                        return 0;
                }
        break;
        case "league.war":
        break;
        case "league.fight":
        break;  
        case "war_free": // "週二", "自由戰場", "19:00-22:00" 週六 "自由戰場", "13:00-20:00"
                if (wk == "2" &&
                   nhour >= 19&& 
                   nhour < 22)return 1;
                else if (wk == "6" &&
                        (nhour >= 13 && nhour < 20)
                        )return 1;
                else
                        return 0;
        break;
        case "xywar":
        break;
        
        default:
        return 0;
        }

        return 0;
}
