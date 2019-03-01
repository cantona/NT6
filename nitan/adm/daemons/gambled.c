// Daemon : /adm/daemons/gambled.c
// 博彩系統
// By jjgod for hell. 00/05/07.
// Update by Lonely

#include <ansi.h>

inherit F_SAVE;

#define DATA_FILE               DATA_DIR "gambled"
#define INITING                 "initing"
#define OPENING                 "opening"
#define STOPPED                 "stopped"
#define FINISHING               "finishing"

mapping item_data = ([
 "十強賽冠軍預測" : ([ "long" : "世界杯外圍賽之十強賽馬上就要開始"
                                "了，究竟本次十強賽誰能出線？中國"
                                "隊能否順利沖出亞洲？能否根治恐韓"
                                "恐伊症？請你在你認為可以出線的隊"
                                "伍上下注吧！",
                       "end_time" : 1210996409,
                       "status"   : OPENING,
                       "min_money" : 10000, 
                       "number" : 3,
                       "subject" : ([ "中國隊" : 10, 
                                      "法國隊" : 20, 
                                      "德國隊" : 50, 
                                      "英國隊" : 70, 
                                      "美國隊" : 80, 
                                      "巴西隊" : 100, ]),
                     ]), 
]);

mapping user_data = ([
"wind" : ([ "十強賽冠軍預測" : ([ "team" : ({ "中國隊", "巴西隊",
                                               "法國隊", }),
                                   "money" : 80000, ]),
           ]),
]);

public void change_status(string name, string status);
public string query_status(string name);
public mapping query_item(string name);
private void change_name(string arg, object me, string name);
private void change_long(object me, string arg, string long);
private void change_date(string arg, object me, string name);
private void change_number(string arg, object me, string name);
private void change_money(string arg, object me, string name);
private void change_team_type(string arg, object me, string name);
private void get_name_end(string arg, object me);
/****************************************************************
 *                                                              *
 *            有關本博彩系統(About this Gamble system)          *
 *                                                              *
 *     本博彩系統採用全自動形式，即巫師手動設定一個項目以後，只 *
 * 要等待比賽結束後將比賽結果輸入，就可以完成一整個博彩遊戲的過 *
 * 程。                                                         *
 *                                                              *
 *     單一項目的整個運行流程如下：                             *
 *                                                              *
 *     1、輸入項目內容，此時為創建態(Initing)。                 *
 *     2、開始允許投注，此時為開放態(Opening)。                 *
 *     3、停止繼續投注，此時為停止態(Stopped)。                 *
 *     4、結束這個項目，此時為結束態(Finishing)。               *
 *                                                              *
 *     管理時的調用結構如下：                                   *
 *                                                              *
 *                          管理系統主界面                      *
 *        +----------+----------+----------+----------+         *
 *     創建項目   修改項目   查看投注   結束項目   退出系統     *
 *        |          |          |          |          |         *
 *     輸入名稱   選擇項目   選擇玩家   選擇項目     退出       *
 *        |          |          |          |                    *
 *     輸入描述   修改子項   查詢完畢   刪除完畢                *
 *        |          |          |          |                    *
 *     結束時間   修改完畢      |          |                    *
 *        |          |          |          |                    *
 *     最少投注      |          |          |                    *
 *        |          |          |          |                    *
 *     投注數量      |          |          |                    *
 *        |          |          |          |                    *
 *     創建完畢------+----------+-------返回界面                *
 *                                                              *
 * 儲存數據：                                                   *
 *                                                              *
 *     item_data 映射：項目數據                                 *
 *     user_data 映射：用戶數據                                 *
 *                                                              *
 * 函數列表：                                                   *
 *                                                              *
 *     供外部調用的：                                           *
 *     public void start_manage()  ：進入管理界面               *
 *     public void printf_over()   : 設置結果界面               *
 *     public void do_chip()       ：進入投注界面               *
 *     public void change_status() ：修改項目狀態               *
 *     public string query_status()：查詢項目狀態               *
 *     public mapping query_item() ：獲取項目數據               *
 *     public mapping query_data() ：獲得所有紀錄               *
 *                                                              *
 *     內部私有的：                                             *
 *     private void write_prompt()      ：顯示管理界面          *
 *     private void end_manage()        ：退出管理界面          *
 *     private void get_type()          ：選擇管理類別          *
 *     private void get_name()          ：輸入項目名稱          *
 *     private void select_change_type()：選擇修改類別          *
 *     private void get_long()          ：輸入項目描述          *
 *     private void get_team_number()   ：輸入隊伍數量          *
 *     private void get_team_info()     ：輸入隊伍數據          *
 *     private void get_date_off()      ：輸入結束時間          *
 *     private void get_chip_number()   ：輸入投注數量          *
 *     private void get_name_todel()    ：選擇刪除項目          *
 *     private void get_user()          ：選擇查詢玩家          *
 *     private void get_user_info()     ：獲得玩家信息          *
 *                                                              *
 *     此外，採用 heart_beat 定時判定一個項目是否應該停止，目前 *
 * 的 heart_beat 設定值為 30，即結束時間精確率為 +- 60s。       *
 *                                                              *
 ****************************************************************/
 
// 創建存盤文件
void create()
{
        seteuid(getuid());
        restore();
}

// 返回存盤文件位置
string query_save_file()
{
        return DATA_FILE;
}

void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

// 提示符
private void write_prompt(object me)
{
        write("您打算：" WHT "A" NOR "、創建新的項目 " WHT "B" NOR "、修改舊的項目 "
              WHT "C" NOR "、查看玩家投注 \n" WHT "        D" NOR "、結束一個項目 " WHT
              "E" NOR "、刪除一個項目 " WHT "F" NOR "、退出管理系統 \n");
        write("請選擇：");
        input_to("get_type", me);

}

// 退出管理
private void end_manage()
{
        write("\n您放棄了博彩管理。\n");
        write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
        return;
}

// 進入管理系統
public void start_manage(object me)
{
        write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
        write("\t\t\t  " + MUD_NAME + "博彩管理程序\n\n");
        write_prompt(me);
        return;
}

// 選擇管理的類別
private void get_type(string arg, object me)
{
        array  users, items;
        string msg = "";
        int i, j;
        
        switch (arg)
        {
        case "a": 
        case "A":
                items = keys(item_data);
                msg = "目前的項目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                
                if (! sizeof(items)) msg = "";
                
                write(msg);
                write("\n您打算創建新的博彩項目。\n");
                write("請輸入新建的項目名稱：");
                input_to("get_name", me);
                return;
        case "b": 
        case "B": 
                items = keys(item_data);
                
                if (! sizeof(items))
                {
                        write("\n目前沒有可修改項目。\n\n");
                        
                        write("查詢完畢。\n");
                        write_prompt(me);
                        return;
                }
                
                msg = "目前的項目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                write(msg);
                write("\n您打算修改舊的博彩項目。\n");
                write("請輸入您要修改的項目名稱：");
                input_to("get_name", me);
                return;
        case "c": 
        case "C": 
                users = keys(user_data);
                
                write("您打算查看玩家投注情況。\n");
                
                if (! sizeof(users))
                {
                        write("\n目前沒有任何玩家投注。\n\n");
                        
                        write("查詢完畢。\n");
                        write_prompt(me);
                        return;
                }
                
                write("目前投注的玩家有：\n\n");
                msg = WHT "";
                
                for (i = 0; i < sizeof(users); i++ )
                {
                        msg += sprintf("%10s", users[i]);
                        j++;
                        if (! (j % 5)) msg += "\n";
                }
                write(msg + NOR);
                write("\n\n一共有 " WHT + i + NOR " 名玩家已經投注。\n");
                write("\n請選擇你具體查看的玩家：");
                input_to("get_user", me);
                return;
        case "d": 
        case "D": 
                write("你打算結束一個博彩項目。\n");
                
                items = keys(item_data);
                // 必須是已經停止的項目才行
                items = filter_array(items, (: query_status($1) == OPENING :));
                
                if (! sizeof(items))
                {
                        write("\n目前沒有可修改項目。\n\n");
                        
                        write("查詢完畢。\n");
                        write_prompt(me);
                        return;
                }
                
                msg = "目前的項目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                write(msg);
                write("\n請輸入您要結束的項目名稱：");
                input_to("get_name_end", me);
                return;
        case "e": 
        case "E": 
                write("你打算刪除一個博彩項目。\n");
                
                items = keys(item_data);
                
                if (! sizeof(items))
                {
                        write("\n目前沒有可修改項目。\n\n");
                        
                        write("查詢完畢。\n");
                        write_prompt(me);
                        return;
                }

                msg = "目前的項目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                write(msg);
                write("\n請輸入您要刪除的項目序號：");
                input_to("get_name_todel", me);
                return;
        default: 
                end_manage();
                return;
        }
        
}

// 選擇管理的項目名稱
private void get_name(string arg, object me)
{
        array teams;
        string msg = "", team;
        int i, num;
        mapping item;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        // 修改舊項目
        if (mapp(item_data[arg]) && sizeof(item_data[arg]) >= 5)
        {
                teams = keys(item_data[arg]["subject"]);
                
                for (i = 0; i < sizeof(teams); i++)
                {
                        team = teams[i];
                        msg += sprintf("%10s：" WHT "1 : %d\n" NOR , team, item_data[arg]["subject"][team]);
                }
                
                change_status(arg, INITING);
                write("\n1、名稱：" WHT + arg + NOR "\n"
                      "2、描述：\n\n" WHT + sort_msg(item_data[arg]["long"]) + NOR "\n\n"
                      "3、結束時間：" WHT + CHINESE_D->chinese_time(5, ctime(item_data[arg]["end_time"])) + 
                      (item_data[arg]["end_time"] > time() ? "" : HIR "(已結束)") + NOR "\n"
                      "4、可投注數量：" WHT + item_data[arg]["number"] + " 個\n" NOR 
                      "5、最小投注量：" WHT + item_data[arg]["min_money"] + " 兩黃金\n" NOR 
                      "6、隊伍及賠率：\n\n" + msg + "\n" );
                write("請選擇您要修改的項目：");
                input_to("select_change_type", me, arg);
                return;
        }
        else if (sscanf(arg, "%d", num) == 1  &&
                 mapp(item = item_data[keys(item_data)[num - 1]]) && sizeof(item) >= 5)
        {
                teams = keys(item["subject"]);
                arg = keys(item_data)[num - 1];
                
                for (i = 0; i < sizeof(teams); i++)
                {
                        team = teams[i];
                        msg += sprintf("%10s：" WHT "1 : %d\n" NOR , team, item["subject"][team]);
                }
                
                change_status(arg, INITING);
                write("\n1、名稱：" WHT + arg + NOR "\n"
                      "2、描述：\n\n" WHT + sort_msg(item["long"]) + NOR "\n\n"
                      "3、結束時間：" WHT + CHINESE_D->chinese_time(5, ctime(item["end_time"])) +  
                      (item["end_time"] > time() ? "" : HIR "(已結束)") + NOR "\n"
                      "4、可投注數量：" WHT + item["number"] + " 個\n" NOR 
                      "5、最小投注量：" WHT + item["min_money"] + " 兩黃金\n" NOR
                      "6、隊伍及賠率：\n\n" + msg + "\n" );
                write("請選擇您要修改的項目：");
                input_to("select_change_type", me, arg);
                return;
        }
        // 創建新項目
        else
        {
                item_data[arg] = ([ ]);
                change_status(arg, INITING);
                save();
                write("\n請輸入項目的詳細描述：\n");
                me->edit((: call_other, __FILE__, "get_long", me, arg :));
                return;
        }
}

private void select_change_type(string arg, object me, string name)
{
        switch (arg)
        {
        case "1":
                write("\n你打算修改這個項目的名稱。\n");
                write("你打算改成什麼呢：");
                input_to("change_name", me, name);
                return;
        case "2":
                write("\n你打算修改這個項目的長描述。\n");
                write("你打算改成什麼呢：");
                me->edit((: call_other, __FILE__, "change_long", me, name :));
                return; 
        case "3": 
                write("\n你打算修改這個項目的結束時間。\n");
                write("這個項目將在多少天後結束？");
                input_to("change_date", me, name);
                return; 
        case "4": 
                write("\n你打算修改這個項目的可投注隊伍數。\n");
                write("這個項目允許的投注隊伍數為：");
                input_to("change_number", me, name);
                return; 
        case "5": 
                write("\n你打算修改這個項目的最小投注量。\n");
                write("你打算改成多少呢：");
                input_to("change_money", me, name);
                return;
        case "6": 
                write("\n你打算修改這個項目的隊伍數據。\n");
                write("你要怎麼修改？[" WHT "1" NOR "、修改 " WHT "2" NOR "、刪除]");
                input_to("change_team_type", me, name);
                return;
        default: 
                change_status(name, OPENING);
                write("\n你放棄了修改。\n\n");
                write("修改完畢。\n");
                write_prompt(me);
                return;
        }
}

// 修改項目的名稱
private void change_name(string arg, object me, string name)
{
        mapping item;
        
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        if (mapp(item_data[arg]))
        {
                change_status(name, OPENING);
                write("\n這是一個已存在的項目，不可以修改。\n\n");
                write("你回到了博彩管理主界面。\n");
                write_prompt(me);
                return;
        }
        item = item_data[name];
        item_data[arg] = item;
        map_delete(item_data, name);
        change_status(arg, OPENING);
        save();
        
        log_file("gamble",sprintf("%schangetheitem%s'snameto%son%s.\n",query("id", me),
                           name, arg, ctime(time())));

        write("\n項目 " WHT + name + NOR + " 的名字已經被成功改為了 " WHT + arg + NOR + "。\n\n");
        write("修改完畢，你回到了管理系統主界面。\n");
        write_prompt(me);
        return;
}

// 輸入項目的長描述
private void change_long(object me, string arg, string long)
{
        if (long == "")
        {
                change_status(arg, OPENING);
                end_manage();
                return;
        }

        item_data[arg]["long"] = replace_string(long, "\n", "");
        change_status(arg, OPENING);
        save();
                
        write("\n項目" WHT + arg + NOR "的描述已經被成功改為了\n " WHT + sort_msg(long) + NOR "\n\n");
        write("修改完畢，你回到了管理系統主界面。\n");
        write_prompt(me);
        return;
}

private void change_date(string arg, object me, string name)
{
        int day, time;
        
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", day) || day <= 0)
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請問這個項目將在多少天後結束投注？[格式：" WHT "5" NOR "]");
                input_to("change_date", me, name);
                return;
        }
        
        time = time() + 86400 * day;       
        item_data[name]["end_time"] = time;
        change_status(name, OPENING);
        save();
                
        write("\n項目" WHT + name + NOR "的結束時間已經被成功改為了 " WHT + chinese_number(day) + NOR " 天左右結束。\n\n");
        write("修改完畢，你回到了管理系統主界面。\n");
        write_prompt(me);
        return;
}

private void change_number(string arg, object me, string name)
{
        int number;
        
        if (arg == "")
        {
                change_status(name, OPENING);       
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", number) || number <= 0)
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請輸入允許玩家選擇的隊伍數目：");
                input_to("change_number", me, name);
                return;
        }
        
        item_data[name]["number"] = number;
        change_status(name, OPENING);
        save();
        
        write("\n項目 " WHT + name + NOR + " 的投注隊伍數已經被成功改為了 " WHT + chinese_number(number) + NOR + "個。\n\n");
        write("修改完畢，你回到了管理系統主界面。\n");
        write_prompt(me);
        return;
}

private void change_money(string arg, object me, string name)
{
        int money;
        
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", money) || money <= 0)
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請輸入項目的最少投注黃金量：[格式：" WHT "10000" NOR "]");
                input_to("get_least_money", me, name);
                return;
        }
        
        item_data[name]["min_money"] = money;
        change_status(name, OPENING);
        save();

        write("\n項目 " WHT + name + NOR + " 的最小投注量已經被成功改為了 " WHT + chinese_number(money) + NOR + "。\n\n");
        write("修改完畢，你回到了管理系統主界面。\n");
        write_prompt(me);
        return;
}

// 選擇修改隊伍的數據類型
private void change_team_type(string arg, object me, string name)
{
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        if (arg == "1")
        {
                write("\n你打算修改項目" + name + "的隊伍數據。\n");
                input_to("change_team_info", me, name);
                return;
        }
        else 
        {
                write("\n你打算刪除項目" + name + "的一個隊伍數據。\n");
                input_to("del_team_info", me, name);
                return;
        }
}

// 輸入項目的長描述
private void get_long(object me, string arg, string long)
{
        if (long == "")
        {
                end_manage();
                return;
        }

        item_data[arg]["long"] = replace_string(long, "\n", "");
        save();
        
        write("\n請輸入項目包含的隊伍數目：");
        input_to("get_team_number", me, arg);
        
        return;
}

// 輸入項目的隊伍數
private void get_team_number(string arg, object me, string name)
{
        int times;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        sscanf(arg, "%d", times);
        
        if (times > 20 || times <= 0)
        {
                write("對不起，這個數目是不合法的。\n");
                
                write("請輸入項目包含的隊伍數目：");
                input_to("get_team_number", me, name);
                
                return;
        }
        
        // 初始化隊伍映射
        item_data[name]["subject"] = ([ ]);
        save();
        
        write("\n請輸入第一個隊伍的名稱及賠率[格式：" WHT "中國隊:30" NOR "]：");
        input_to("get_team_info", me, name, times);
        
        return;
}

// 輸入具體一個隊伍的信息
private void get_team_info(string arg, object me, string name, int times)
{
        string team;
        int bonus;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (sscanf(arg, "%s:%d", team, bonus) != 2)
        {
                write("格式錯誤，請重新輸入。\n");
                write("請輸入第一個隊伍的名稱及賠率[格式：" WHT "中國隊:30" NOR "]：");
                input_to("get_team_info", me, name, times);
        
                return;
        }
        
        // 防止出現重復輸入
        if (item_data[name]["subject"][team])
        {
                write("這個隊伍已經輸入過了。\n");
                write("請輸入下一個隊伍的名稱及賠率[格式：" WHT "中國隊:30" NOR "]：");
                input_to("get_team_info", me, name, times);
        
                return;
        }
        
        item_data[name]["subject"][team] = bonus; 
        
        // 如果所有的隊伍都輸入完了
        if (times == sizeof(item_data[name]["subject"]))
        {
                write("\n請問這個項目將在多少天後結束投注？[格式：" WHT "5" NOR "]");
                input_to("get_date_off", me, name);
                return;
        }
        
        write("目前還剩下：" + (times - sizeof(item_data[name]["subject"])) + "個隊。\n");
        
        item_data[name]["subject"][team] = bonus;
        save();
        
        write("\n請輸入下一個隊伍的名稱及賠率[格式：" WHT "中國隊:30" NOR "]：");
        input_to("get_team_info", me, name, times);
        
        return;
}

// 輸入結束的時間
private void get_date_off(string arg, object me, string name)
{
        int day, time;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", day) || day <= 0)
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請問這個項目將在多少天後結束投注？[格式：" WHT "5" NOR "]");
                input_to("get_date_off", me, name);
                return;
        }
        
        time = time() + 86400 * day;
        
        item_data[name]["end_time"] = time;
        save();
        
        write("\n項目" WHT + name + NOR "將在 " WHT + CHINESE_D->chinese_time(5, ctime(time)) +
              NOR " 左右結束。\n\n");
              
        write("請輸入項目的最少投注黃金量：[格式：" WHT "10000" NOR "]");
        input_to("get_least_money", me, name);
        return;
}

// 輸入最少投注量
private void get_least_money(string arg, object me, string name)
{
        int money;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", money) || money <= 0)
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請輸入項目的最少投注黃金量：[格式：" WHT "10000" NOR "]");
                input_to("get_least_money", me, name);
                return;
        }
        
        item_data[name]["min_money"] = money;
        save();
        
        write("\n項目" WHT + name + NOR "的最小投注量是 " WHT + money +
              NOR " 兩黃金。\n\n");
        
        write("請輸入允許玩家選擇的隊伍數目：");
        input_to("get_chip_number", me, name);
        return;
}

// 輸入允許玩家選擇的隊伍數目
private void get_chip_number(string arg, object me, string name)
{
        int number;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", number) 
            || number <= 0
            || number >= sizeof(item_data[name]["subject"]))
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請輸入允許玩家選擇的隊伍數目：");
                input_to("get_chip_number", me, name);
                return;
        }
        
        item_data[name]["number"] = number;
        save();
        
        write("項目" WHT + name + NOR "允許玩家選擇的隊伍數目是 " WHT + chinese_number(number) +
              NOR " 個。\n\n");
              
        // 全部內容編輯完畢
        change_status(name, OPENING);
        save();
        
        log_file("gamble",sprintf("%screateagambleitemcalled%son%s.\n",query("id", me),
                           name, ctime(time())));

        write("全部內容編輯保存完畢。\n");
        
        write("你回到的管理系統主界面。\n"); 
        write_prompt(me);        
        return;
}

// 刪除一個項目
private void get_name_todel(string arg, object me)
{
        int number;
        array names;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", number) || number <= 0)
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請輸入你要刪除的項目序號：");
                input_to("get_name_todel", me);
                return;
        }
        
        names = keys(item_data);
        if (! mapp(item_data[names[number - 1]]))
        {
                write("\n沒有這個項目。\n\n");
                
                write("請輸入你要刪除的項目序號：");
                input_to("get_name_todel", me);
                return;
        }
        
        write("項目" WHT + names[number - 1] + NOR "被成功刪除了。\n\n");
        map_delete(item_data, names[number - 1]);
        log_file("gamble",sprintf("%sdeleteagambleitemcalled%son%s.\n",query("id", me),
                           names[number - 1], ctime(time())));
        save();
        
        write("你回到的管理系統主界面。\n"); 
        write_prompt(me);        
        return;
}

// 玩家投注界面
public void do_chip(object me)
{
        array items = keys(item_data);
        string msg = "目前允許投注的項目有：\n\n";
        int i;
        
        write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
        write("\t\t  「" HIW + MUD_NAME + "博彩公司" NOR "」\n\n");
        
        if (! sizeof(items))
        {
                write("沒有可供下注的項目。\n");
                write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
                return;
        }
        
        for (i = 0; i < sizeof(items); i++)
        {
                // 如果沒有開放
                if (query_status(items[i]) != OPENING)
                        continue;
                msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
        }
        write(msg);
        write("\n請選擇您要參與博彩的項目[" WHT "Enter" NOR " 退出]：");
        input_to("select_name_tochip", me);
        
        return;
}

// 選擇投注的項目
private void select_name_tochip(string arg, object me)
{
        string name, *teams, msg = "";
        int i;
        mapping item;
        string id=query("id", me);
                
        if (arg == "")
        {
                write("\n你放棄了投注。\n");
                write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
                return;
        }

        if (! sscanf(arg, "%d", i) || i <= 0)
        {
                write("\n你發燒了？怎麼可能會有這個項目？\n");
                write("請選擇您要參與博彩的項目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
        
                return;
        }
        
        name = keys(item_data)[i - 1];
        
        if (! mapp(item = item_data[name]))
        {
                write("\n沒發燒？但確實沒有這個項目呀。\n");
                write("請選擇您要參與博彩的項目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
        
                return;
        }
 
        if (mapp(user_data[id]) &&
            sizeof(user_data[id][name]) >= 2)
        {
                teams = user_data[id][name]["team"];
                for (i = 0; i < sizeof(teams); i++)
                {
                        msg += sprintf("%10s：" WHT "1 : %d\n" NOR , teams[i], item["subject"][teams[i]]);
                }                
                write("\n這個項目你不是已經投注了嗎？可不能反悔哦。\n");
                write("\n1、名稱：" WHT + name + NOR "\n"
                        "2、描述：\n\n" WHT + sort_msg(item["long"]) + NOR "\n\n"
                        "3、結束時間：" WHT + CHINESE_D->chinese_time(5, ctime(item["end_time"])) + 
                        (item["end_time"] > time() ? "" : HIR "(已結束)") + NOR "\n"
                        "4、可投注數量：" WHT + item["number"] + " 個\n" NOR 
                        "5、已投注黃金：" WHT + user_data[id][name]["money"] + " 兩黃金\n" NOR
                        "6、隊伍及賠率：\n\n" + msg + "\n" );

                write("請選擇您要參與博彩的項目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
                return; 
        }
                
        if (item["status"] != OPENING)
        {
                write("\n這個項目還沒開放或者是已經停止了，你還是換一個吧。\n");
                write("請選擇您要參與博彩的項目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
        
                return;
        }
        
        /*
        // 投注是分開來一隊一隊的投
        if (mapp(user_data[id]) && 
            arrayp(teams = user_data[id][name]["team"]) && 
            sizeof(teams) >= item_data[name]["number"])
        {
                write("你下注的隊伍已經夠多的了。\n");
                return;
        }
        */                  
        
        teams = keys(item["subject"]);
                
        for (i = 0; i < sizeof(teams); i++)
        {
                msg += sprintf("%10s：" WHT "1 : %d\n" NOR , teams[i], item["subject"][teams[i]]);
        }

        write("\n1、名稱：" WHT + name + NOR "\n"
                        "2、描述：\n\n" WHT + sort_msg(item["long"]) + NOR "\n\n"
                        "3、結束時間：" WHT + CHINESE_D->chinese_time(5, ctime(item["end_time"])) + 
                        (item["end_time"] > time() ? "" : HIR "(已結束)") + NOR "\n"
                        "4、可投注數量：" WHT + item["number"] + " 個\n" NOR 
                        "5、最小投注量：" WHT + item["min_money"] + " 兩黃金\n" NOR
                        "6、隊伍及賠率：\n\n" + msg + "\n" );

        write("請輸入你要投注的隊伍[多個用“" WHT "," NOR "”隔開]：");

        input_to("select_team_tochip", me, name);

        return;
}

// 選擇投注的隊伍
protected void select_team_tochip(string arg, object me, string name)
{
        array teams, all_teams;
        int i, n;
        
        if (arg == "")
        {
                write("\n你放棄了投注。\n");
                write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
                return;
        }

        if (! item_data[name])
        {
                write(name + "\n");
                write("Non data.\n");
                return;
        }

        if (! arrayp(teams = explode(arg, ",")) ||
            ! n = sizeof(teams))
        {
                write("\n輸入格式錯誤，請重新輸入。\n");
                write("請輸入你要投注的隊伍[多個用“" WHT "," NOR "”隔開]：");
                input_to("select_team_tochip", me, name);
                return;
        }
        
        all_teams = keys(item_data[name]["subject"]);
        if (n != item_data[name]["number"])
        {
                write("\n輸入的隊伍數目不符合。\n");
                write("請重新輸入你要投注的隊伍[多個用“" WHT "," NOR "”隔開]：");
                input_to("select_team_tochip", me, name);
                return;
        }
        
        for (i = 0; i < n; i++)
        {
                if (member_array(teams[i], all_teams) == -1)
                {
                        write("\n這個隊伍不屬于這個項目。\n");
                        write("請重新輸入你要投注的隊伍[多個用“" WHT "," NOR "”隔開]：");
                        input_to("select_team_tochip", me, name);
                        return;
                }
        }
        
        user_data+=([query("id", me):([name:(["team":teams])])]);
        
        write("\n你選擇下注的隊伍是" WHT + implode(teams, NOR "、" WHT) + NOR + "。\n\n");
        write("\n請輸入你要下注的黃金：");
        input_to("get_money_tochip", me, name);
        
        return;
}

protected void get_money_tochip(string arg, object me, string name)
{
        string id;
        int money;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", money) || money <= 0)
        {
                write("\n非法的格式，請重新輸入。\n\n");
                
                write("請輸入最少投注黃金量：[格式：" WHT "10000" NOR "]");
                input_to("get_money_tochip", me, name);
                return;
        }
        
        id=query("id", me);
        
        if (count_lt(money, item_data[name]["min_money"]))
        {
                write("你至少要下注" + chinese_number(item_data[name]["min_money"]) + "兩黃金吧。\n");
                input_to("get_money_tochip", me, name);
                return;
        }
        
        if( count_le(query("balance", me),count_mul(money,10000)) )
        {
                write("\n你銀行的存款余額不足，請重新輸入。\n\n");                                 
                write("請輸入最少投注黃金量：[格式：" WHT "10000" NOR "]");
                input_to("get_money_tochip", me, name);
                return;
        }
        
        set("balance", count_sub(query("balance", me),count_mul(money,10000)), me);
        user_data[id][name] += ([ "money" : money ]);                               
        save();
        
        write("投注成功。\n");
        return;
}

// 選擇查詢的玩家
private void get_user(string arg, object me)
{
        mapping user;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        if (! mapp(user = user_data[arg]))
        {
                write("沒有這個投注用戶。\n");
                write("請選擇你具體查看的玩家：");
                input_to("get_user", me);
                return;
        }
        write("用戶 " + WHT + arg + NOR " 參加投注的項目有：\n\n" WHT + implode(keys(user), NOR "/" WHT) + NOR "\n");
        
        write("\n請選擇具體查看的項目：");
        input_to("get_user_info", me, arg);
        
        return;
}

// 獲得玩家的具體信息
private void get_user_info(string arg, object me, string id)
{
        mapping user;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        if (! mapp(user = user_data[id][arg]))
        {
                write("沒有這個項目。\n");
                write("請選擇具體查看的項目：");
                input_to("get_user_info", me, arg);
                return;
        }
        write("\n投注者：" + WHT + id + NOR + "\n");
        write("項目名：" + WHT + arg + NOR + "\n");
        write("投注量：" + WHT + user_data[id][arg]["money"] + NOR " 兩黃金" + NOR + "\n");
        write("投注隊伍：" WHT + implode(user_data[id][arg]["team"], NOR " & " WHT) + NOR + "\n\n");
        
        write("查詢完畢，你回到的管理系統主界面。\n"); 
        write_prompt(me); 
        return;
}

private void get_name_end(string arg, object me)
{
        if (arg == "")
        {
                end_manage();
                return;
        }
              
        change_status(arg, STOPPED);        
        write("修改完畢，你回到的管理系統主界面。\n"); 
        write_prompt(me); 
        return;
}

// 改變項目的狀態
public void change_status(string name, string status)
{
        if (mapp(item_data[name]))
        {
                item_data[name]["status"] = status;
                save();
                return;
        }
        else return;
}

// 查詢項目的狀態
public string query_status(string name)
{
        if (! stringp(name) || name == ""
            || ! mapp(item_data[name]))
        {
                return INITING;
        }
        else
        {
                return item_data[name]["status"];
        }
}

// 返回一個項目內容(以供博彩屋調用)
public mapping query_item(string name)
{
        if (mapp(item_data[name]))
                return item_data[name];
}

// 返回整個數據庫
varargs public mapping query_data(int raw)
{
        if (raw)
                return user_data;
        return item_data;
}
