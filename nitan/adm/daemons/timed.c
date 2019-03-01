// Rewritten by Lonely@chinamud.cn
// timed.c

#include <ansi.h>
#include <localtime.h>
#include <command.h>
#include <mudlib.h>

inherit F_DBASE;

#define CRONTAB         "/adm/etc/crontab"
#define MAZE_DOOR       "/clone/misc/maze_door1"

#define MIN             0
#define HOUR            1
#define WDAY            2
#define MDAY            3
#define MON             4
#define YEAR            5

int gametime;
nosave int realtime;
nosave int tick;
nosave mapping event = allocate_mapping(0);
nosave int *real_time = allocate(6);
nosave int *game_time = allocate(6);
nosave int ready = 0;
protected void init_crontab();

class cron_item
{
        int flag;               // flag 0 現實生活; flag 1 遊戲中
        string time;            // 時間
        string file;            // 觸發物件的文件名
        string func;            // 觸發函數
        string *args;           // 觸發函數中的參數
}

class cron_item *all_items = ({});

protected void out(string str)
{
        log_file("timed", str);
}

void auto_relaim()
{
        int i;
        if (i = reclaim_objects())
                CHANNEL_D->do_channel( this_object(), "sys",
                        sprintf("系統自動清除 %d 個變量。", i));

        // cpu過高則降低mudos心跳
        if( CPU_D->get_current_cpu_cost() >= 85 && query_heartbeat_interval() == 1 )
        {
                set_heartbeat_interval(2);
                log_file("heartbeat", sprintf("System changed mudOS heart beat to 2 at %s\n", TIME_D->replace_ctime(time())));
        } 
        else 
        if( CPU_D->get_current_cpu_cost() <= 60 && query_heartbeat_interval() == 2 )
        {
                set_heartbeat_interval(1);
                log_file("heartbeat", sprintf("System changed mudOS heart beat to 1 at %s\n", TIME_D->replace_ctime(time())));
        }
}

protected void init_crontab()
{
        string *table, *time_zone;
        class cron_item item;
        int flag, legal = 0;
        object ob;
        string *items;
        int i, n;

        all_items = ({});

        if( file_size(CRONTAB) < 0 )
                return;

        items =  filter_array(explode(read_file(CRONTAB), "\n") - ({ "" }), (: $1[0] != '#' :));

        if( !n = sizeof(items) )
                return;

        for( i=0; i<n; i++ ) {
                reset_eval_cost();
                table = explode(items[i]," ");
                if( sizeof(table) < 3 ) {
                        out(sprintf("以下任務格式錯誤：\n%s\n\n",items[i]));
                        continue;
                }
                time_zone = explode(table[0],":");
                if( sizeof(time_zone) < 7 ) {
                        out(sprintf("以下任務時間部分格式錯誤：\n%s\n\n",items[i]));
                        continue;
                }

                if( file_size(table[1]+".c") < 0 ) {
                        out(sprintf("以下任務觸發物件檔案不存在：\n%s\n\n",items[i]));
                        continue;
                }
                if( !ob = find_object(table[1]) )
                        ob = load_object(table[1]);
                if( !ob ) {
                        out(sprintf("以下任務觸發物件無法載入：\n%s\n\n",items[i]));
                        continue;
                }
                if( !function_exists(table[2],ob) ) {
                        out(sprintf("以下任務觸發物件中觸發函數不存在：\n%s\n\n",items[i]));
                        continue;
                }
                if( sscanf(time_zone[0],"%d",flag) ) {
                        if( (flag != 0) && (flag != 1) ) {
                                out(sprintf("以下任務 flag 格式錯誤：\n%s\n\n",items[i]));
                                continue;
                        }

                } else {
                        out(sprintf("以下任務 flag 格式錯誤：\n%s\n\n",items[i]));
                        continue;
                }

                item = new(class cron_item);

                item->file = table[1];
                item->func = table[2];
                item->args = table[3..];
                item->flag = flag;
                item->time = implode(time_zone[1..], " ");
                all_items += ({ item });
        }

        if( sizeof(all_items) )
                ready = 1;
}

// 可取代 call_out 之功能
void add_event(function fevent, int delay_time)
{
        if( !sizeof(event) || !event[fevent] )
                event = ([ fevent : delay_time ]);
        else
                event[fevent] = delay_time;
}

// 執行事件
void exec_event(function fevent)
{
        if( objectp(function_owner(fevent)) )
                evaluate(fevent);

        map_delete(event, fevent);
}

string replace_ctime(int t)
{
        string month, ctime = ctime(t);

        switch(ctime[4..6])
        {
                case "Jan"      :       month = "01";break;
                case "Feb"      :       month = "02";break;
                case "Mar"      :       month = "03";break;
                case "Apr"      :       month = "04";break;
                case "May"      :       month = "05";break;
                case "Jun"      :       month = "06";break;
                case "Jul"      :       month = "07";break;
                case "Aug"      :       month = "08";break;
                case "Sep"      :       month = "09";break;
                case "Oct"      :       month = "10";break;
                case "Nov"      :       month = "11";break;
                case "Dec"      :       month = "12";break;
        }

        return sprintf("%s/%s/%s %s", month, (ctime[8]==' '?"0"+ctime[9..9]:ctime[8..9]), ctime[<4..<1], ctime[11..15]);
}

string season_period(int m)
{
        switch(m)
        {
                case 2..4:      return "春";
                case 5..7:      return "夏";
                case 8..10:     return "秋";
                case 11:        return "冬";
                case 0..1:      return "冬";
                default:        return 0;
        }
}

string week_period(int w)
{
        switch(w)
        {
                case 0:         return "日";
                case 1:         return "一";
                case 2:         return "二";
                case 3:         return "三";
                case 4:         return "四";
                case 5:         return "五";
                case 6:         return "六";
                default:        return 0;
        }
}

string hour_period(int h)
{
        switch(h)
        {
                case 0..5:      return "凌晨";
                case 6..11:     return "上午";
                case 12:        return "中午";
                case 13..18:    return "下午";
                case 19..23:    return "晚上";
                default:        return 0;
        }
}

/* 回傳時間陣列 ({ 分 時 禮 日 月 年 }) */
int *query_gametime_array()
{
        return game_time;
}

int *query_realtime_array()
{
        return real_time;
}

/* 回傳數位時間表示 下午 3:39 */
string gametime_digital_clock()
{
        int h = game_time[HOUR];
        int m = game_time[MIN];

        return hour_period(h)+" "+(h==12 || (h%=12)>9?""+h:" "+h)+":"+(m>9?""+m:"0"+m);
}
string realtime_digital_clock()
{
        int h = real_time[HOUR];
        int m = real_time[MIN];

        return hour_period(h)+" "+(h==12 || (h%=12)>9?""+h:" "+h)+":"+(m>9?""+m:"0"+m);
}

string time_description(string title, int *t)
{
        return sprintf( NOR WHT+title+NOR"%s年，%s，%s月%s日星期%s，%s%s點%s分"NOR
            ,t[YEAR]==1?"元":CHINESE_D->chinese_number(t[YEAR])
            ,season_period(t[MON])
            ,!t[MON]?"元":CHINESE_D->chinese_number(t[MON]+1)
            ,CHINESE_D->chinese_number(t[MDAY]+1)
            ,week_period(t[WDAY])
            ,hour_period(t[HOUR])
            ,CHINESE_D->chinese_number(t[HOUR] > 12 ? t[HOUR]%12 : t[HOUR])
            ,CHINESE_D->chinese_number(t[MIN])
        );
}

string game_time_description()
{
        return time_description(CHINESE_MUD_NAME, game_time);
}

string real_time_description()
{
        return time_description("公元", real_time);
}

int query_game_time()
{
        return gametime*60;
}

int query_real_time()
{
        return realtime;
}

int *analyse_time(int t)
{
        int *ret = allocate(6);
        string ctime;

        ctime = ctime(t);

        sscanf(ctime,"%*s %*s %d %d:%d:%*d %d",ret[MDAY], ret[HOUR], ret[MIN], ret[YEAR]);

        switch(ctime[0..2])
        {
                case "Sun": ret[WDAY] = 0; break;
                case "Mon": ret[WDAY] = 1; break;
                case "Tue": ret[WDAY] = 2; break;
                case "Wed": ret[WDAY] = 3; break;
                case "Thu": ret[WDAY] = 4; break;
                case "Fri": ret[WDAY] = 5; break;
                case "Sat": ret[WDAY] = 6; break;
                default   : return 0;
        }

        switch(ctime[4..6])
        {
                case "Jan": ret[MON] = 0; break;
                case "Feb": ret[MON] = 1; break;
                case "Mar": ret[MON] = 2; break;
                case "Apr": ret[MON] = 3; break;
                case "May": ret[MON] = 4; break;
                case "Jun": ret[MON] = 5; break;
                case "Jul": ret[MON] = 6; break;
                case "Aug": ret[MON] = 7; break;
                case "Sep": ret[MON] = 8; break;
                case "Oct": ret[MON] = 9; break;
                case "Nov": ret[MON] = 10; break;
                case "Dec": ret[MON] = 11; break;
                default   : return 0;
        }
        ret[MDAY] -= 1;
        return ret;
}

void process_crontab(int *timearray, int flag)
{
        int i, n, t, row, divider, fit, timecost;
        string str, script, *timescript;
        object ob;
        mixed args;

        if( !ready )
                return;

        if( !n = sizeof(all_items) )
                return;

        for( row=0; row<n; row++ ) {
                reset_eval_cost();
                if( all_items[row]->flag != flag )
                        continue;

                script = all_items[row]->time;
                timescript = allocate(6);

                // %s%*(( |\t)+) 的意思是 %s(空格 or \t 跳過)接著 + 可以相配一串一個以上符合的單元
                if( sscanf(script, "%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s",
                        timescript[0],
                        timescript[1],
                        timescript[2],
                        timescript[3],
                        timescript[4],
                        timescript[5]) != 11 ) continue;

                for( i=0; i<6; i++ ) {
                        fit = 0;

                        foreach( str in explode(timescript[i], ",") ) {
                                t = to_int(str);

                                // 不同的mudos的undefinedp函數返回的值有區別
                                if( str == "*" || (sscanf(str, "*/%d", divider) && !(timearray[i]%divider)) ) {
                                        fit = 1;
                                        break;
                                }
                                else if( !undefinedp(t) ) {
                                        if( t == timearray[i] ) {
                                                fit = 1;
                                                break;
                                        }
                                }
                        }
                        if( !fit ) break;
                }

                if( !fit )
                        continue;

                ob = find_object(all_items[row]->file);
                if( !ob )
                        ob = load_object(all_items[row]->file);
                if( !ob )
                        continue;
                args = ({ all_items[row]->func }) + all_items[row]->args;
                timecost = time_expression {
                        catch(call_other(ob, args));
                };

                if( timecost > 1000000 )
                        CHANNEL_D->do_channel(this_object(), "sys",
                                sprintf("TIME_D: crontab '%s'(%.6f sec) %s", script, timecost/1000000., all_items[row]->file));

        }
}

// 獨立出來每秒執行函式
void process_per_second()
{

        
}

int reset_gametime(int time)
{
        gametime = time;
}

/* 遊戲時間每一分鐘(即實際時間每2秒)執行一次 process_gametime */
void process_gametime()
{
        game_time = analyse_time(++gametime * 60);
        game_time[YEAR] -= 1970;

        process_crontab(game_time, 1);
}

/* 真實時間每一秒鐘執行一次 process_realtime */
void process_realtime()
{
        mixed *local_time = localtime(realtime);

        real_time = ({
                to_int(local_time[LT_MIN]),
                to_int(local_time[LT_HOUR]),
                to_int(local_time[LT_WDAY]),
                to_int(local_time[LT_MDAY])-1,
                to_int(local_time[LT_MON]),
                to_int(local_time[LT_YEAR]) });
        
        process_per_second();
        
        if( !local_time[LT_SEC] )
                process_crontab(real_time, 0);
}

// 每 1 秒運算一次
// 實際一天等于遊戲一月

void heart_beat()
{
        while(realtime < time())
        {
                realtime++;
                process_realtime();
        }

        // 執行 event 處理
        if( sizeof(event) )
        foreach( function fevent, int delay_time in event )
                if( !--event[fevent] )
                        exec_event(fevent);

        // 每 2 秒相當于遊戲一分鐘, time 每增加 1 代表遊戲一分鐘
        //if( !(++tick % 2) )
                process_gametime();
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "時間精靈");
        //write("時間精靈已經啟動。\n");

        init_crontab();
        
        realtime = time();
        game_time = allocate(6);
        real_time = allocate(6);
        event = allocate_mapping(0);

        process_gametime();
        set_heart_beat(1);
}

void place_boss(string arg)
{
        object ob, startroom;
        object maze_door;
        string filename;

        switch( arg )
        {
        case "pantu" :
                filename = "/d/city/beimen";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/huashan-pantu");
                ob->move(startroom);
                break;
        case "taofan" :
                filename = "/d/beijing/yongdingmen";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/chaoting-taofan");
                ob->move(startroom);
                break;
        case "daoke" :
                filename = "/d/jianzhong/shangu";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/jianzhong-daoke");
                ob->move(startroom);
                break;
        case "dugu" :
                filename = "/d/jianzhong/maigu";
                startroom = get_object(filename);
                if( !(ob = present("dugu qiubai", startroom)) )
                {
                        ob = new("/kungfu/class/misc/dugu-qiubai");
                        ob->move(startroom);
                }
                break;
        case "feizei" :
                filename = "/d/gumu/mumen";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/daomu-feizei");
                ob->move(startroom);
                break;
        case "yanji" :
                filename = "/d/guanwai/beicheng";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/yan-ji");
                ob->move(startroom);
                break;
        case "yangkang" :
                filename = "/d/jiaxing/yanyu";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/yang-kang");
                ob->move(startroom);
                break;
        case "wudu" :
                filename = "/d/wudu/taohua";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/wudu-shengwu");
                ob->move(startroom);
                break;
        case "longnv" :
                filename = "/d/jueqing/qinghuaao";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/xiao-longnv");
                ob->move(startroom);
                break;
        case "gongsun" :
                filename = "/d/jueqing/danfang";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/gongsun-zhi");
                ob->move(startroom);
                break;
        case "fawang" :
                filename = "/d/jueqing/duanchang";
                startroom = get_object(filename);
                if( !(ob = present("jinlun fawang", startroom)) )
                {
                        ob = new("/kungfu/class/misc/jinlun-fawang");
                        ob->move(startroom);
                }
                break;
        case "boguang" :
                filename = "/d/huashan/path1";
                startroom = get_object(filename);
                if( !(ob = present("tian boguang", startroom)) )
                {
                        ob = new("/kungfu/class/misc/tian-boguang");
                        ob->move(startroom);
                }
                break;
        case "ouyangfeng" :
                filename = "/d/kunlun/bainiuling";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/ouyang-feng");
                ob->move(startroom);
                break;
        case "jiangshi" :
                filename = "/d/gaochang/dadian";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/jiangshi-daozhang");
                ob->move(startroom);
                break;
        case "fusang" :
                filename = "/d/xiakedao/xkroad4";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/fusang-wushi");
                ob->move(startroom);
                break;
        case "liulishou" :
                filename = "/d/lanzhou/square";
                startroom = get_object(filename);
                ob = new("/kungfu/class/misc/qicai-liulishou");
                ob->move(startroom);
                break;
        case "sea_dragon" :
                filename = "/d/xiakedao/haibin";
                startroom = get_object(filename);
                ob = load_object("/maze/sea_dragon/npc/dragon");
                maze_door = new(MAZE_DOOR);
                set("maze_entry", "/maze/sea_dragon/maze/entry", maze_door);
                maze_door->move(startroom);
                SCHEDULE_D->set_event(1800, 0, this_object(), "remove_maze", ob->short(), startroom, maze_door);
                break;
        case "golden_dragon" :
                filename = "/d/dragon/spiritgate";
                startroom = get_object(filename);
                ob = load_object("/maze/golden_dragon/npc/dragon");
                maze_door = new(MAZE_DOOR);
                set("maze_entry", "/maze/golden_dragon/maze/entry", maze_door);
                maze_door->move(startroom);
                SCHEDULE_D->set_event(1800, 0, this_object(), "remove_maze", ob->short(), startroom, maze_door);
                break;
        case "god_dragon" :
                filename = "/d/xueshan/shenghu";
                startroom = get_object(filename);
                ob = load_object("/maze/god_dragon/npc/dragon");
                maze_door = new(MAZE_DOOR);
                set("maze_entry", "/maze/god_dragon/maze/entry", maze_door);
                maze_door->move(startroom);
                SCHEDULE_D->set_event(1800, 0, this_object(), "remove_maze", ob->short(), startroom, maze_door);
                break;
        default:
                return;
        }

        /*
        message("vision", HIG "【" HIR "江湖" HIG "】" HIR "有人發現" HIR + ob->short() + HIR "出現在" +
                HIW + startroom->short() + HIY "(" + LOOK_CMD->locate(filename) +
                ")" HIR "一帶活動。\n" NOR, users());
        */
        CHANNEL_D->channel_broadcast("mess", "有人發現" HIR + ob->short() + HIG "出現在" +
                HIW + startroom->short() + HIY "(" + LOOK_CMD->locate(filename) +
                ")" HIG "一帶活動。\n" NOR);
}

void remove_maze(string name, object room, object maze_door)
{
        if ( !room || !maze_door ) return;

        destruct(maze_door);

        /*
        message("vision", HIG"【" HIR"江湖" HIG"】" HIW +
                room->short() + HIW "(" + LOOK_CMD->locate(base_name(room)) + ")一帶出現的" +
                HIR + name + HIR "消失了。\n" NOR, users());
        */
        CHANNEL_D->channel_broadcast("mess", "聽說" + room->short() + HIW "(" + LOOK_CMD->locate(base_name(room)) + ")一帶出現的" +
                HIR + name + HIG "消失了。\n" NOR);
}

int give_money(int count)
{
        mapping ips;
        object pob;
        string ip;
        string *ks;

        CHANNEL_D->channel_broadcast("news",  
                HIG + "系統開始給每個玩家饋贈NT，本次饋贈數量為"+count+"NT…\n" + NOR); 

        count = to_int(count);
        ips = ([ ]);
        //foreach( pob in all_interactive() )
        foreach( pob in users() )
        {
                if( wizardp(pob) || !query("born", pob) ||  
                !environment(pob) ) continue; 

                ip = query_ip_number(pob);
                if( undefinedp(ips[ip]) ) ips[ip] = ({ pob }); else ips[ip] += ({ pob }); 
        }

        if( sizeof(ips) >= 1 ) 
        {
                ks = keys(ips); 
                foreach( ip in ks ) 
                {
                        pob = ips[ip][random(sizeof(ips[ip]))]; 
                        if( MEMBER_D->is_member(pob) )
                                MEMBER_D->db_pay_member(pob, count);  
                        else
                                MEMBER_D->db_create_member(pob, count);
                }
        }
        return 1;
}
string query_name()
{
        return "時間系統(TIME_D)";
}

