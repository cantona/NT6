// action_d.c
// 活動精靈，負責發起和關閉每日的活動
// 這個daemon我傾向于做成廣播器和活動狀態的容器
// 他本身什麼也不做，其他系統從他這裡獲取某個活動是否開啟的狀態

#include <localtime.h>
#include <ansi.h>

mapping action_settings = ([]);
mapping active_actions = ([]);
int setup();
int get_minute_by_string(string time);
void check_action_startend();

void create()
{
        seteuid(getuid());
        if( setup() ) {
                CHANNEL_D->channel_broadcast("sys", "活動精靈已經啟動。");
                check_action_startend();
                SCHEDULE_D->set_event(600, 1, this_object(), "check_action_startend");
        }
}

void check_action_startend()
{
        mixed *ltime;
        int now_min;
        int tmp;

        tmp = 0;
        ltime = localtime(time());
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN]; // 當前分鐘，這裡要用localtime(獲取本地時間)

        // 逐個setting做判斷，60秒一次，這個效率可以接受
        foreach( string key in keys(action_settings) ) {
                // 當前時間在開始時間以前，那麼什麼也不做
                if( now_min<action_settings[key]["start"] )
                        continue;
                // 當前時間在結束時間之後，則需要試試是否應該關閉它
                if( now_min>=action_settings[key]["end"] ) {
                        // 存在于活躍列表，則結束之
                        if( !undefinedp(active_actions[key]) ) {
                                map_delete(active_actions,key);
                                // 廣播
                                message("system", HIY "【活動】本日活動："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]已經結束。\n" NOR, users());
                        } // 否則什麼也不做
                        continue;
                }
                // 考慮到create的情況，所以當時間落在start和end之間的時候，需要多一個判斷

                if( undefinedp(active_actions[key]) ) {
                        tmp ++;
                        active_actions[key] = action_settings[key]["times"];// 獲得倍率
                        // 廣播
                        message("system", HIY "【活動】本日活動："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]已經開始（本活動將持續約"+chinese_number(action_settings[key]["end"]-now_min)+"分鐘）。\n" NOR, users());
                }
        }
        if( !tmp && !random(3) ) {// 平均每三分鐘announc一次
                foreach( string key in keys(active_actions) ) {
                        message("system", HIY "【活動】當前活動："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]進行中（本活動將持續約"+chinese_number(action_settings[key]["end"]-now_min)+"分鐘）。\n" NOR, users());
                }
        }
}
//測試接口，獲取所有的action列表
mixed query_action_settings()
{
        return action_settings;
}

// 給查詢指令留的接口
string str2(int i)
{
        return (i<10)?("0"+i):(""+i);
}

string query_action_string()
{
        string ret;
        mixed *ltime;
        int now_min;

//      if(!sizeof(active_actions))
//              return HIY"當前沒有正在進行中的活動。\n"NOR;

        ltime = localtime(time());
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN];
/*      ret = HIY"當前正在進行中的活動有：\n";
        foreach(string key in keys(active_actions)) {
                ret += action_settings[key]["name"]+"："+chinese_number(action_settings[key]["times"])+"倍[剩余"+chinese_number(action_settings[key]["end"]-now_min)+"分鐘]\n";
        }
        ret += NOR;
        return ret;
*/
        ret = HIY"目前"+MUD_NAME+"提供的活動包括：\n";
        foreach( string key in keys(action_settings) ) {
                ret += "\t"+action_settings[key]["name"]+"："+str2(action_settings[key]["start"]/60)+":"+str2(action_settings[key]["start"]%60)+"～"+str2(action_settings[key]["end"]/60)+":"+str2(action_settings[key]["end"]%60)+"（"+chinese_number(action_settings[key]["times"])+"倍）";
                if( active_actions[key] ) {
                        ret += HIG"-當前進行中-剩余"+chinese_number(action_settings[key]["end"]-now_min)+"分鐘\n"HIY;
                } else {
                        ret +=HIG"-當前未開啟\n"HIY;
                }
        }

        return ret+NOR;
}

// 這裡是其他系統調用查詢當前是否處于某個活動中的接口，返回的是倍率
int query_action(string action)
{
        if( undefinedp(active_actions[action]) )
                return 0;
        else
                return active_actions[action];
}

int get_minute_by_string(string time)
{
        int hour,minute;
        hour = atoi(time[0..1]);
        minute = atoi(time[2..3]);
        return hour*60+minute;
}

int setup()
{
        mixed file;
        mixed tmp;

        // 這裡應該判斷是否有文件
        if( !(file = read_file("/adm/etc/action_list")) )
                return 0;
        // 過濾win的換行符
        file = replace_string(file,"\r","");
        file = explode(file,"\n");
        file = filter_array( file , (: $1[0] != '#' :) );
        foreach( string line in file ) {
                //確保不是空行
                if( strlen(line) ) {
                        // action_list形如：
                        // action_name:chinese_name:starttime:endtime:times
                        // task_reward:多倍TASK獎勵:1500:1700:2
                        // 活動英文標識:活動中文名:開始時間:結束時間:倍率
                        // 時間應該形如0830(前兩位表示小時-24小時制，後兩位表示分鐘)，並且開始時間應當小于結束時間
                        // 這裡假設配置文件是對的。。。
                        tmp = explode(line, ":");
                        action_settings[tmp[0]] = ([]);
                        action_settings[tmp[0]]["name"] = tmp[1];
                        action_settings[tmp[0]]["start"] = get_minute_by_string(tmp[2]);//一天的第幾分鐘
                        action_settings[tmp[0]]["end"] = get_minute_by_string(tmp[3]);  //一天的第幾分鐘
                        action_settings[tmp[0]]["times"] = atoi(tmp[4]);
                }
        }
        return 1;
}

string query_name()
{
        return "活動精靈(ACTION_D)";
}
