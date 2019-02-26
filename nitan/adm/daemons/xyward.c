
#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <localtime.h>
#include <getconfig.h>

#define WARRING           2
#define THEEND            0
#define WAIT_START        3
#define XYNPC            "/kungfu/class/generate/xiangyang/"
#define GIFT_EXP_BASE    10000         
#define GIFT_POT_BASE    10000
#define GIFT_MAR_BASE    3000
#define GIFT_WEI_BASE    10000
#define GIFT_YUE_BASE    10000 
#define DB_D             "/adm/daemons/dbd"

#define MEMBER_D         "/adm/daemons/memberd"

// 東邪，西毒，南帝，北丐可隨機增援
#define DONGXIE          "/kungfu/class/generate/xiangyang/huang"
#define XIDU             "/kungfu/class/generate/xiangyang/ouyangfeng"
#define NANDI            "/kungfu/class/generate/xiangyang/yideng"
#define BEIGAI           "/kungfu/class/generate/xiangyang/hong"

// 楊過和小龍女
#define YANGGUO          "/kungfu/class/generate/xiangyang/yang"
#define LONGNV           "/kungfu/class/generate/xiangyang/longnv"

// 增加的蒙古兵
#define MORE_SOLDIER     10
// 調動襄陽守軍間隔
#define MOVE_WAIT        60

// 增加的襄陽士兵數量
#define ADD_XY_SOLDIER   120

// 增派蒙古兵次數
#define ADD_MGB_TIMES    3

// 增加蒙古兵時間間隔
#define ADD_MGB_WAIT     120

// 測試標誌
#define TEST             0

// 是否允許開放標誌
#define ALLOW_START      1

inherit F_DBASE;

int status = 0;                // 襄陽戰狀態
int start_status = 0;          // 系統狀態，1 表明開始，則不再重複調用
int sign_up_status = 0;        // 報名標誌
string *p = ({});             // 參加襄陽戰的玩家物件列表

int start_time = 0;           // 襄陽保衞戰開始時間
int attack_time = 0;          // 蒙古人開始攻城時間
        
int tiemuzhen = 0;            // 本次是否出現鐵木真

int n_mg_tq = 0, n_mg_zb = 0, n_mg_gb = 0 , n_mg_bb = 0;// 騎兵、哲別、弓兵、步兵數量
int n_xy_sb = 0; // 襄陽士兵

int n_xy_sb2; // 襄陽士兵最初數量
int n_mg_sb2; // 蒙古士兵最初數量

int add_mgb_times = 0; // 增援蒙古兵次數
int query_add_mgb_times(){return add_mgb_times;}

int last_add_mgb_time = 0; // 上次增援蒙古兵時間
int last_combat_change_time = 0; // 上次調整戰術的時間
int add_xyb_flag = 0; // 增派襄陽士兵標誌

public int query_add_xyb_flag(){return add_xyb_flag;}

// 江湖人士增援的消息
string xy_msg1 = "----";
string query_xy_msg1(){return xy_msg1;}

// 1 為襄陽  2 為蒙古
int who_win; // 襄陽保衞戰誰勝利

// 襄陽保衞戰序列號 RAN_NUM
// 該序列號在每次開始前隨機產生，作用是標註本次襄陽保衞戰鬥的唯一性
// 每殺死一個蒙古並則做設置 /xywar/RAN_NUM/point, point根據殺死的蒙古兵等級來設置
int RAN_NUM = 0;

public int get_who_win(){return who_win;}
public int set_who_win(int who){who_win = who;} 
public void player_die(string id);
public int get_ran_num(){return RAN_NUM;} // 獲取本次襄陽保衞戰序列號

object xy_guojing; // 郭靖
int guojing_moved = 0; // 郭靖是否已經與蒙古人交戰

// 新增蒙古援軍所在方位，攻擊方向則反向（由巫師動態控制）
string yb_attack_where = "none";
string query_yb_attack_where() { return yb_attack_where; }
string set_yb_attack_where(string str_where) { return yb_attack_where = str_where; }


// /kungfu/class/generate/xiangyang/guo.c 調用
public int if_guojing_moved()
{
        return guojing_moved;
}

// 免死調用
int die_xywar(object me)
{
        me->delete_override("die");

        // 保衞戰已經結束則沒有死亡保護
        if (status == THEEND)return 0;
        
        me->move("d/city/wumiao");

        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("eff_jing"));
        me->set("jingli", me->query("max_jingli"));        

        me->revive();
        tell_object(me, BLINK + HIG "你已經退出襄陽保衞戰！\n" NOR);
        player_die(me->query("id"));
        
        me->save();
        
        return 1;        
}

// 移動NPC到蒙古軍營前對軍營其他PLAYER做清理
void clear_junying()
{
        object room;
        object *ob;
        int i, j;
        
        for (i = 1; i < 4; i ++)
        {
                if (! objectp(room = find_object("/d/xiangyang/junying" + sprintf("%d", i))))
                        room = load_object("/d/xiangyang/junying" + sprintf("%d", i));
                
                if (! objectp(room))
                {
                        log_file("xywar_clear_junying", "junying" + sprintf("%d", i) + " load object fail.\n");
                        return;
                }

                ob = all_inventory(room);        
                
                if (! sizeof(ob))continue;
                
                // 將在軍營的所有玩家移動的武廟
                for (j = 0; j < sizeof(ob); j ++)
                {
                        if (playerp(ob[j]))
                        {
                                ob[j]->move("/d/city/wumiao");
                                continue;
                        }                        
                }                        
        }                                                        
        
        XYWAR_D->xywar_message(HIW "蒙古軍營清理完畢！\n" NOR);
}

// 設置報名參加襄陽保衞戰的玩家免除死亡
void set_no_die(object me)
{
        me->set_override("die", (: call_other, __FILE__, "die_xywar", me:));

        return;
}


int is_guojing_died = 0;     // 郭靖是否死亡

string xysb_poision = "襄陽城內四周";

void start_xywar();                // 襄陽戰開始
void reset_data();                 // 襄陽戰結束後重新設置數據
string xywar_message(string msg);  // 襄陽戰報
void set_now_status(int flag);     // 設置戰鬥狀態

void combat_xjtuibing();          // 戰術：虛假退兵
void combat_sdjixi();             // 戰術：聲東擊西

string more_soldier_poision;  // 某一方向上士兵多MORE_SOLDIER名

string player_leader; // 玩家將領的ID

int last_move_xysolder = 0; // 上次調動襄陽守軍的時間
int query_last_move_xysolder(){ return last_move_xysolder;}

// 四大門駐並地點
mapping doors = ([
        "west"  :      "/d/xiangyang/guandao_1",
        "east"  :      "/d/zhongzhou/toyy",
        "south" :      "/d/xiangyang/caodi6",
        "north" :      "/d/xiangyang/caodi3",
]);

mapping doors_name = ([
        "west"  :      "白虎門",
        "east"  :      "青龍門",
        "south" :      "朱雀門",
        "north" :      "玄武門",
]);

string random_doors_name()
{
        string *keys_name;
        
        keys_name = keys(doors_name);
        
        return doors_name[keys_name[random(sizeof(keys_name))]];
}

// /kungfu/class/generate/xiangyang/guo.c random_move()調用
public mixed get_doors()
{
        return doors;
}

// 襄陽士兵四大門駐並地點
mapping doors2 = ([
        "west"  :      "/d/xiangyang/westgate1",
        "east"  :      "/d/xiangyang/eastgate1",
        "south" :      "/d/xiangyang/southgate1",
        "north" :      "/d/xiangyang/northgate1",
]);
              
mapping doors2_name = ([
        "west"  :      "白虎內門",
        "east"  :      "青龍內門",
        "south" :      "朱雀內門",
        "north" :      "玄武內門",        
]);
       
// 襄陽最接近中央廣場的四個地點
mapping doors3 = ([
        "west"  :      "/d/xiangyang/westjie1",
        "east"  :      "/d/xiangyang/eastjie1",
        "south" :      "/d/xiangyang/southjie1",
        "north" :      "/d/xiangyang/anfupailou",
]);

mapping doors3_name = ([
        "west"  :      "襄陽城西大街",
        "east"  :      "襄陽城東大街",
        "south" :      "襄陽城南大街",
        "north" :      "安撫府牌樓",        
]);

// 四大門的兵力數量
// ({ 鐵騎、哲別、弓兵、 步兵  })
mapping n_soldier = ([
        "west"  :      ({0, 0, 0, 0}),
        "east"  :      ({0, 0, 0, 0}),
        "south" :      ({0, 0, 0, 0}),
        "north" :      ({0, 0, 0, 0}),
]);

// 將方向反向
public string re_poision(string p)
{
        if (! sizeof(p))return "";
        
        switch(p)
        {
                case "west":
                        return "east";
                case "east":
                        return "west";
                case "north":
                        return "south";
                default:
                        return "north";                                                
        }
}

// 襄陽戰結束
void xywar_over()
{
        status = THEEND;
        xywar_message(HIR "提示：本次襄陽保衞戰由於報名人數不足，宣告結束。\n" NOR);
        reset_data();           // 襄陽戰結束後重新設置數據

        return;
}

// 保衞戰失敗
// 蒙古勝利
public void war_fail()
{        
        who_win = 2;;
        
        call_out("xywar_message", 4, HIY "本次襄陽保衞戰以殘敗收場，蒙古人長驅直入，佔領了襄陽，從此生靈塗炭，民不聊生 ……！\n");
        call_out("xywar_message", 5, HIY "而參與那次慘烈的襄陽保衞戰的義士們卻永遠不會被後人所遺忘！\n");

        set_now_status(THEEND);

        return;
}

// 獎勵所有參戰玩家
void gift_to_player()
{
        object dob;
        int i, n;
        string str_ran_num;
        
        
        n = sizeof(p);
        
        // 將本次襄陽保衞戰序列號轉化為字串
        str_ran_num = sprintf("%d", RAN_NUM);
        
        for (i = 0; i < n; i ++)
        {
                dob = find_player(p[i]);
                
                if (! objectp(dob))continue;
                
                // 設置功勛
                dob->add("xywar/win", 1);

                // 根據戰鬥中殺敵數量來進行獎勵，一個未殺則獎勵設置為最低
                if (dob->query("xywar/xy_" + str_ran_num))
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : GIFT_EXP_BASE + dob->query("xywar/xy_" + str_ran_num),
                                           "pot"      : GIFT_POT_BASE + dob->query("xywar/xy_" + str_ran_num) / 2,
                                           "weiwang"  : GIFT_WEI_BASE + dob->query("xywar/xy_" + str_ran_num) / 20,
                                           "score"    : GIFT_YUE_BASE + dob->query("xywar/xy_" + str_ran_num) / 20,
                                           "mar"      : GIFT_MAR_BASE + dob->query("xywar/xy_" + str_ran_num) / 20,
                                           "prompt"   : "你在襄陽保衞戰勝利後"]), 999);
                        dob->delete("xywar/xy_" + str_ran_num);
                }
                else
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : GIFT_EXP_BASE,
                                           "pot"      : GIFT_POT_BASE,
                                           "weiwang"  : GIFT_WEI_BASE,
                                           "score"    : GIFT_YUE_BASE,
                                           "mar"      : GIFT_MAR_BASE,
                                           "prompt"   : "你在襄陽保衞戰勝利後"]), 999);                                         
                }
                dob->save();

                /*
                // 根據經驗來劃分獎勵
                if (dob->query("combat_exp") >= 30000000)
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : GIFT_EXP_BASE + random(GIFT_EXP_BASE / 2),                                           
                                           "pot"      : GIFT_POT_BASE + random(GIFT_POT_BASE / 2),                                       
                                           "weiwang"  : GIFT_WEI_BASE + random(GIFT_WEI_BASE / 2),                               
                                           "score"    : GIFT_YUE_BASE + random(GIFT_YUE_BASE / 2),  
                                           "mar"      : GIFT_MAR_BASE + random(GIFT_MAR_BASE / 2),                           
                                           "prompt"   : "你在襄陽保衞戰勝利後"]), 999);
                else
                        GIFT_D->delay_bonus(dob,                                              
                                        ([ "exp"      : GIFT_EXP_BASE / 2 + random(GIFT_EXP_BASE / 3),                                           
                                           "pot"      : GIFT_POT_BASE / 2 + random(GIFT_POT_BASE / 3),                                       
                                           "weiwang"  : GIFT_WEI_BASE / 2 + random(GIFT_WEI_BASE / 3),                               
                                           "score"    : GIFT_YUE_BASE / 2 + random(GIFT_YUE_BASE / 3),  
                                           "mar"      : GIFT_MAR_BASE / 2 + random(GIFT_MAR_BASE / 3),                           
                                           "prompt"   : "你在襄陽保衞戰勝利後"]), 999);                                                           
         */
        }
        
}

// 保衞戰勝利
// 襄陽勝利
// 獎勵所有參戰玩家
public void war_win()
{
        who_win = 1;
        
        gift_to_player();
        
        set_now_status(THEEND);
        
        call_out("xywar_message", 4, HIW "由於襄陽守軍及玩家地奮力抵抗，終於擊退了蒙古軍，襄陽保衞戰勝利！\n");

        return;
}

// 蒙古人佔領中央廣場
void arrived_center()
{
        if (status == THEEND)return;

        war_fail();

        xywar_message(HIR "蒙古人已佔領襄陽中央廣場，本次襄陽保衞戰以襄陽失陷告終！\n" NOR);                
        
}

// 由於報名玩家剩餘不到五名，戰鬥失敗
void war_end_player()
{
        if (status == THEEND)return;
                
        xywar_message(HIR "由於參與襄陽保衞戰的玩家已剩餘不到五名，難以繼續抵抗蒙古人的攻勢。" NOR);
        xywar_message(HIR "蒙古人長驅直入，佔領了襄陽，從此生靈塗炭，民不聊生 ……" NOR);
        xywar_message(HIR "而參與那次慘烈的襄陽保衞戰的義士們卻永遠不會被後人所遺忘！\n" NOR);
        
        set_now_status(THEEND);
                
}

// 外部調用 /kungfu/class/generate/xiangyang/xyshibing.c調用
// 判斷目前是否受到調動
public int is_moved()
{
        if (xysb_poision == "襄陽城內四周")return 0;
        
        return 1;
}

// 襄陽士兵目前的位置
// 外部可調用
public string xy_soldier_poision(string para)
{
        if (xysb_poision == "襄陽城內四周")
                return xysb_poision;

        switch(para)
        {
                // 返回地名
                case "name" :
                        return doors3_name[xysb_poision];
                
                // 返回方位
                case "poision" :
                        return xysb_poision;
                
                case "env" :
                        return doors3[xysb_poision];

                default:return "error";                                                
        }
}

// 蒙古軍總數量
int total_menggu_soldier(string route)
{
        int i, j, total = 0;
        string *key_n_soldier;
        int *route_n_soldier;

        key_n_soldier = keys(n_soldier);

        // 返回襄陽士兵總數
        if (route == "xiangyang")
        {
                return n_xy_sb;
        }
        
        // 返回蒙古士兵總數
        if (route == "total")
        {
                for (j = 0; j < sizeof(key_n_soldier); j ++ )
                {
                        for (i = 0; i < sizeof(n_soldier[key_n_soldier[j]]); i ++)
                        {
                                total = total + n_soldier[key_n_soldier[j]][i];
                        }
                }

                return total;
        }
        
        // 某一移動方向上的蒙古軍總數量
        if (stringp(route))
        {
                route_n_soldier = n_soldier[route];

                if (sizeof(route_n_soldier))
                {
                        for (i = 0; i < sizeof(route_n_soldier); i ++ )
                        {
                                total = total + route_n_soldier[i];
                        }
                }

                return total;
        }
}

// key = "max" || key = "min"
// 返回n_soldier 中士兵力量最強或最弱的組
// 其中士兵 參數為1、弓兵為2, 哲別為3，騎兵為4
string max_min_n_soldier(string keys)
{
        int i, j, power_w, power_e, power_s, power_n;
        int max_tmp1, max_tmp2, min_tmp1, min_tmp2;
        int max_result, min_result;
        string smax_tmp1, smax_tmp2, smin_tmp1, smin_tmp2;
        string smax_result, smin_result;
        string key_n_soldier;

        if (keys != "max" && keys != "min")return "NULL";

        power_w = 0;
        for (i = 0; i < 4; i ++)
        {
                power_w = power_w + n_soldier["west"][i];
        }
        power_e = 0;
        for (i = 0; i < 4; i ++)
        {
                power_e = power_e + n_soldier["east"][i];
        }
        power_n = 0;
        for (i = 0; i < 4; i ++)
        {
                power_n = power_n + n_soldier["north"][i];
        }
        power_s = 0;
        for (i = 0; i < 4; i ++)
        {
                power_s = power_s + n_soldier["south"][i];
        }

        max_tmp1 = power_w >= power_e ? power_w : power_e;
        smax_tmp1 = power_w >= power_e ? "west" : "east";
        max_tmp2 = power_n >= power_s ? power_n : power_s;
        smax_tmp2 = power_n >= power_s ? "north" : "south";
        
        min_tmp1 = power_w <= power_e ? power_w : power_e;
        smin_tmp1 = power_w <= power_e ? "west" : "east";
        min_tmp2 = power_n <= power_s ? power_n : power_s;
        smin_tmp2 = power_n <= power_s ? "north" : "south";

        max_result = max_tmp1 >= max_tmp2 ? max_tmp1 : max_tmp2;
        smax_result = max_tmp1 >= max_tmp2 ? smax_tmp1 : smax_tmp2;
        min_result = min_tmp1 <= min_tmp2 ? min_tmp1 : min_tmp2;
        smin_result = min_tmp1 <= min_tmp2 ? smin_tmp1 : smin_tmp2;

        if (keys == "max")
        {
                return smax_result;
        }

        if (keys == "min")
        {
                return smin_result;

        }

}

// 蒙古士兵死亡通告，用於系統判斷每組軍隊數量
// 襄陽士兵通告，用於系統判斷襄陽士兵總數量
void soldier_die(string route, int which)
{
        if (route == "xiangyang") // 襄陽士兵死亡
        {
                n_xy_sb -= 1;
                if (n_xy_sb <= 0)n_xy_sb = 0;
                return;
        }

        // route 代表west, east, south, north中的一種， which 代表兵種
        if (route != "west" &&
            route != "north" &&
            route != "south" &&
            route != "east")return;

        // 0 代表騎兵、1代表哲別、2代表弓兵、3代表步兵
        if (which < 0 || which > 3)return;
        
        // 將ROUTE反一次
        route = re_poision(route);
        
        n_soldier[route][which] -= 1;
        


        if (n_soldier[route][which] <= 0)n_soldier[route][which] = 0;

        return;
}

// 判斷郭靖是否已經死亡
int is_guojing_die()
{
        return is_guojing_died;
}

// 郭靖死亡
// 郭靖死亡後所有襄陽士兵自動撤退
void guojing_die()
{
        is_guojing_died = 1; // 標誌郭靖已死亡
}

// 報名參加襄陽戰
void sign_up(string id)
{
        if (! sizeof(p)) p = ({});

        p += ({ id });

        return;
}


// 返回已報名的人數
public int n_sign_up(){return sizeof(p);}

// 返回報名的數組
public string *p_sign_up(){return p;}

// 檢查某ID是否報名狀態仍然有效
int if_sign_up(string id)
{
        if (! sizeof(p))return 0;

        if (member_array(id, p) != -1)return 1;

        return 0;
}

// 外部調用，玩家死亡後從襄陽保衞站報名中刪除
public void player_die(string id)
{
        if (! stringp(id))return;
        if (! if_sign_up(id))return;
        
        p -= ({ id });
        
        return;
}

// 檢查離線的報名玩家並刪除之
void sub_check_player()
{
        int i;
        for (i = 0; i < sizeof(p); i ++ )
        {
                if (! objectp(find_player(p[i])))
                {
                        p -= ({ p[i] });
                        return sub_check_player();
                }
        }
        
        if (sizeof(p) < 5 && status == WARRING && ! TEST)war_end_player();
        
}

// 檢查離線的報名玩家並刪除之
// 調用 sub_check_player()執行
void check_player()
{
        int i;
        remove_call_out("check_player");
        call_out("check_player", 10); // 檢查參加襄陽戰的玩家

        if (! sizeof(p))return;

        sub_check_player();

        return;
}

// 返回各種狀態
// 1=襄陽勝利 | -1=蒙古勝利
// 2=進行中   | 0=結束或未開始
// 3=等待進攻
int now_status(){return status;}

// 設置各種狀態
void set_now_status(int flag)
{
        // 如果狀態為結束戰鬥
        if (flag == THEEND)
        {
                status = THEEND;
                call_out("xywar_message", 10, HIG "本次襄陽保衞戰已結束，系統將於1分鐘內釋放資源，襄陽恢復平靜。");
                reset_data(); // 初始化所有數據
        }

        status = flag;
}

// 報名標誌，1=可以報名  0=不可以報名
int sign_up_status(){return sign_up_status;}

// 設置報名標誌
void set_sign_up_status(int flag){sign_up_status = flag;}

// 退兵標誌
int dest_status()
{
        if (status == THEEND)
        {
                return 1;
        }

        return 0;
}

// 過濾不接受故事信息的人
int filter_listener(object ob)
{
            // 計劃中不接收
        if (ob->query("doing") == "scheme") return 0;
        return 1;
}

// 襄陽戰系統通告
void xywar_message(string msg)
{
        string prompt;
        object *listeners;

        prompt = HIY "【襄陽戰報】" NOR;
        listeners = filter_array(users(), (: filter_listener :));
        message( "story",  prompt + HIC + msg + "\n" NOR, listeners );
}

void do_attack_msg(string msg)
{
        if (status == THEEND)return;
        
        xywar_message(msg);
}

// 郭靖通告：過濾沒有報名的人
int filter_listener2(object ob)
{
        if (member_array(ob->query("id"), p) == -1)return 0;

        return 1;
}

// 郭靖通告
void guojing_message(string msg)
{
        string prompt;
        object *listeners;

        prompt = HIY "【郭靖】" NOR;
        listeners = filter_array(users(), (: filter_listener2 :));
        message( "story",  prompt + HIR + msg + "\n" NOR, listeners );
}

// 每月1日和15日晚上8點30開始
void check_time()
{
        string *str_bjtime,bjtime1;
        
        remove_call_out("check_time");
        call_out("check_time", 15);

        // 如果發現戰鬥開始標誌
        if (start_status)return;

        // 1小時內不能重複自動啟動
        if (time() - DB_D->query_data("xywar/last_auto_start") < 36000)
                return;
                
        // 檢查是否到了啟動時間，如果是則設置開始標誌
        // 返回北京時間 (年:月:日:時:分:秒)
        bjtime1 = MEMBER_D->bjtime(time(), 0);
        str_bjtime = explode(bjtime1, ":");
        
        // 每月1日，或15日20：30分開始
        if (str_bjtime[2] == "1" || str_bjtime[2] == "15")
        {
                if (str_bjtime[3] == "20" && str_bjtime[4] == "30")
                        DB_D->set_data("xywar/start", 1);
        }

        // 檢查開始標誌，並啟動
        if (DB_D->query_data("xywar/start"))
        {                
                DB_D->set_data("xywar/start", 0);
                DB_D->set_data("xywar/last_auto_start", time());
                log_file("xywar", "xywar 於 " + ctime(time()) + " 自動啟動！\n");
                start_xywar();
        }
}

void create()
{
        seteuid(getuid());
        set("channel_id", "襄陽戰鬥系統");
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "系統已經啟動。");
        
        if (! ALLOW_START)return;
        
        remove_call_out("check_time");
        call_out("check_time", 10); // 檢查襄陽戰開始時間
        remove_call_out("check_player");
        call_out("check_player", 10); // 檢查參加襄陽戰的玩家
        remove_call_out("check_combatd");
        call_out("check_combatd", 30); // 戰鬥戰術系統總控函數
}

// 戰鬥戰術系統總控文件，用於控制蒙古軍隊戰術軍隊調整
void check_combatd()
{
                int total, w, e, s, n;
                int xytotal;
                string max_route;
                string dj_name;
                
                remove_call_out("check_combatd");
                call_out("check_combatd", 10);

                // 襄陽戰結束
                if (status == THEEND)return;
                
                // 各門人數及總人數
                total = total_menggu_soldier("total");
                xytotal = total_menggu_soldier("xiangyang");
                w = total_menggu_soldier("west");
                e = total_menggu_soldier("east");
                s = total_menggu_soldier("south");
                n = total_menggu_soldier("north");
                
                // 襄陽士兵死傷過半提示
                if (xytotal < n_xy_sb2 / 2 && ! guojing_moved)
                {
                        xywar_message(HIW "宋軍探子：報！！目前我宋軍已經死傷過半，情況十分危急。\n" NOR);

                        // 
                        if (! is_guojing_die())
                        {
                                xywar_message(HIW "郭靖：好，既然如此，我郭某誓與襄陽共存亡 ……" NOR);
                                xywar_message(HIR "聽説郭靖親自上陣，與蒙古人決一死戰。\n" NOR);
                                
                                call_out("xywar_message", 2, HIY "蒙古將領：蒙古勇士們向前衝啊，宋軍已經潰不成軍了。\n");

                                // 將guojing 移動到蒙古人最多的地方
                                if (objectp(xy_guojing))
                                {
                                        max_route = max_min_n_soldier("max");
                                        xy_guojing->move(doors[max_route]);

                                        // 設置移動方向
                                        xy_guojing->set("route", re_poision(max_route));

                                        // 已經移動標誌
                                        guojing_moved = 1;                                        
                                }
                        }
                }

                // 正在戰鬥中，適時調整戰術
                /*
                */
                if (status == WARRING || (status == WAIT_START && total_menggu_soldier("total") < 120))
                {
                        // 1.  蒙古軍隊數量少於80時派兵增援
                        if (add_mgb_times < ADD_MGB_TIMES &&
                               time() - last_add_mgb_time >= ADD_MGB_WAIT &&
                               (status == WARRING || status == WAIT_START) &&
                               total_menggu_soldier("total") < 120)                        
                        {
                                last_add_mgb_time = time();
                                call_out("xywar_message", 2, HIW "蒙古探子：報！宋軍得江湖人士支持，頑強抵抗，我軍目前傷亡慘重！");
                                call_out("xywar_message", 4, HIW "蒙古將領“嗯”了一聲：看來，我們應該採取一些行動了，傳令放狼煙……");
                                call_out("xywar_message", 5, HIY "襄陽探子：報！蒙古人已放出狼煙，加派援軍進攻襄陽！");
                                call_out("combat_add_soldier", 7);
                                        
                        }
                        
                        // 2.  蒙古軍隊進攻3分鐘後開始調整戰術
                        if (time() - attack_time > 180 && 
                            time() - last_combat_change_time > 90 && // 距離上次戰術調整時間為90秒
                            random(5) == 1)
                        {
                                last_combat_change_time = time();
                                
                                switch(random(5))
                                {
                                        // 虛假退兵
                                        case 0:
                                                combat_xjtuibing();
                                                break;
                                        // 聲東擊西
                                        default :
                                                combat_sdjixi();
                                                break;                                        
                                }
                        }

                        // 蒙古人全滅，則襄陽勝利
                        if (total_menggu_soldier("total") <= 0)
                        {
                                xywar_message(HIG "蒙古軍已經全軍覆沒！");
                                war_win();
                                return;
                        }
                        
                        // 防禦30分鐘則代表襄陽勝利
                        if (time() - attack_time > 1800)
                        {
                                xywar_message(HIG "郭靖：襄陽城經過眾多玩家及將士的努力，已經堅守超過30分鐘");
                                xywar_message(HIG "郭靖：蒙古人糧草輜重已經消耗殆盡，只得暫時退兵！");
                                war_win();
                                return;                                
                        }
                }

                // 正在等待進攻
                if (status == WAIT_START)
                {
                        if (random(3) == 1)
                        {
                                switch(random(10))
                                {
                                        case 0:
                                                xywar_message("郭靖：蒙古人正在調配軍隊，請保衞襄陽的義士做好相關準備，隨時備戰。");
                                                xywar_message("黃蓉：各位守城玩家請各自分配好任務，準備隨時迎擊蒙古軍，誓死保衞襄陽。\n");
                                                break;
                                        case 1:
                                                xywar_message("郭靖：蒙古的千夫長在從軍前都是一代成名的武學宗師，萬萬不可輕視。");
                                                xywar_message("郭靖：玩家只要守(guard)住路口，蒙古人便無法通過，但被攔截的蒙古人會主動攻擊守住路口的玩家。");
                                                xywar_message("黃蓉：蒙古千夫長不主動攻擊經驗在2億以下的玩家，同時經驗在2億以下的玩家即使守(guard)住路口\n"
                                                              "            後，也無法攔截住千夫長。\n");
                                                
                                                break;
                                        case 2:
                                                xywar_message("蒙古探子：襄陽城內突然集聚了大量江湖人士，看來他們想死守城池。");
                                                if (tiemuzhen)dj_name = "成吉思汗";
                                                else dj_name = "蒙古將領";
                                                xywar_message(dj_name + "：哼，兩軍交鋒豈同江湖撕鬥，一羣烏合之眾必將死於亂箭之下。\n");                                        
                                                break;                
                                        case 3:
                                                xywar_message("黃蓉：參戰的玩家在殺死任意蒙古人後都會獲得一定的經驗和潛能獎勵。");
                                                xywar_message("黃蓉：如果襄陽保衞戰勝利則所有參戰玩家（不包括中途退出的）都將獲得豐富的獎勵\n");
                                                break;
                                        case 4:
                                                xywar_message("黃蓉：在對抗蒙古人時系統會自動關閉參戰玩家的戰鬥信息，中途切勿打開，以免影響遊戲速度。\n");
                                                break;
                                        case 5:
                                                xywar_message("黃蓉：蒙古人詭計多端，在戰鬥中會隨時調整戰術，也可能會派兵增援。");
                                                xywar_message("黃蓉：玩家將領請根據雙方戰鬥狀況隨時做出戰略調整，指揮各參戰玩家抵抗蒙古人進攻。\n");                                                
                                                break;
                                        case 6:
                                                xywar_message("郭靖：玩家將領可在本次襄陽保衞戰中使用一次兵符，使用後可增加120名襄陽守軍。");
                                                xywar_message("郭靖：使用兵符的指令是 " HIY "xy add xyb " HIC "。\n");
                                                break;
                                        case 7:
                                                xywar_message("郭靖：一旦玩家與蒙古人對面，蒙古人則會自動叫殺，佩帶隱身符則可隱身於蒙古人中，不被主動攻擊。\n");
                                                break;
                                        case 8:
                                                if (tiemuzhen)
                                                {
                                                        xywar_message("郭靖：郭某自幼跟隨大汗鐵木真馳騁大漠，彎弓射鵰，不想今日卻對戰沙場。");
                                                        xywar_message("郭靖：不過國難當頭，蒙古人殺掠成性，今日郭某將誓死保衞我大宋江山，死守襄陽。");
                                                        xywar_message("郭靖：參戰玩家可選出數名高手偷襲蒙古軍營，只要殺死成吉思汗鐵木真蒙古人便不攻自破。\n");
                                                        break;
                                                }
                                                xywar_message("郭靖：郭某自幼跟隨大汗鐵木真馳騁大漠，與蒙古哲別彎弓射鵰，不想今日卻對戰沙場。");
                                                xywar_message("郭靖：不過國難當頭，蒙古人殺掠成性，今日郭某將誓死保衞我大宋江山，死守襄陽。");
                                                xywar_message("郭靖：蒙古哲別在蒙古語中為“神射手”，其箭法精準，切忌不可輕視。");
                                                xywar_message("郭靖：如果可能玩家在集中優勢兵力解決千夫長後應集中全力將哲別消滅。\n");
                                                break;
                                        case 9:
                                                xywar_message("襄陽城四周已經瀰漫着濃烈的硝煙味，城民早已各自收拾細軟，隨時準備趁亂逃命，場面一片混亂。");
                                                break;
                                        default:
                                                xywar_message(HIW "蒙古軍士：三軍已集合完畢，糧草輜重、刀槍箭矢已點算完畢，隨時可以開戰。" NOR);
                                                xywar_message(HIY "襄陽軍士：我軍已集合完畢，四城門均要道均已有重兵把守，我軍誓於蒙古人周旋到底。\n" NOR);
                                                
                                                break;                                                                                                                                
                                }
                        }
                }

                /*
                戰術：蒙古軍隊可在戰鬥中根據條件改變戰術
                1、聲東擊西
                2、虛假退兵
                3、增派兵力
                */
}

// 襄陽戰結束，重置相關數據
void reset_data()
{
            p = ({});                 // 參加襄陽戰的玩家物件列表
        status = THEEND;          // 襄陽戰狀態
        start_status = 0;         // 系統狀態 恢復到未開始狀態
        sign_up_status = 0;       // 報名標誌
            tiemuzhen = 0;            // 本次是否出現鐵木真
        n_mg_tq = 0;
        n_mg_zb = 0;
        n_mg_gb = 0;
        n_mg_bb = 0;              // 騎兵、哲別、弓兵、步兵數量
        n_xy_sb = 0;              // 襄陽士兵數量        
        is_guojing_died = 0;      // 郭靖是否死亡標誌

        add_mgb_times = 0;             // 增援蒙古兵次數
        add_xyb_flag = 0;              // 增援襄陽士兵次數標誌
        last_add_mgb_time = 0;         // 上次增援蒙古兵時間
        guojing_moved = 0;             // 郭靖是否已經與蒙古人交戰
        xysb_poision = "襄陽城內四周"; // 襄陽守軍駐紮地
        player_leader = "";            // 玩家將領的ID
        last_move_xysolder = 0;        // 上次調動襄陽守軍的時間
        start_time = 0;                // 襄陽保衞戰開始時間
        attack_time = 0;               // 蒙古人開始攻城時間
        who_win = 0;                   // 誰勝利
        xy_msg1 = "----";              // 襄陽增援消息，楊過等
        yb_attack_where = "none";      // 新增蒙古兵攻擊方向

}


// 蒙古人開始進攻襄陽
void do_attack()
{
        if (status == THEEND)return;

        xywar_message(HIR "蒙古人開始圍攻襄陽城！" NOR);
        attack_time = time();
        status = WARRING;
}

// 播報蒙古軍戰報
// 大約每分鐘播放一次，直到開始攻城
void do_combatd_message(int i)
{
        string dj_name;
        if (tiemuzhen)
        {
                dj_name = "成吉思汗";
        }
        else
                dj_name = "蒙古大將";

        if (status == THEEND)return;
        
        switch(i)
        {
                case 1:
                        xywar_message(dj_name + "：傳我號令，全軍在此紮營，五分鐘後全軍開始圍攻襄陽城！");
                        break;
                // 報告蒙古人總軍力
                case 2:
                        xywar_message("宋軍探子：本次蒙古軍隊總數量約為：" + HIY + sprintf("%d", total_menggu_soldier("total"))  + HIC "　人！並分四"
                                  "路，分別駐紮在朱雀門，白虎門，青龍門及玄武門外。");
                        if (tiemuzhen)
                        {
                                xywar_message(HIR "宋軍探子：本次蒙古軍由成吉思汗鐵木真親自率領。" NOR);
                        }
                        break;
                //
                case 3:
                        xywar_message("宋軍探子：襄陽城內宋軍已調配完畢，隨時準備迎擊蒙古軍。");
                        break;
                //
                case 4:
                        xywar_message("郭靖：請報名參加襄陽保衞戰的玩家自行組織，守住四大門路口，防止蒙古人攻入襄陽中央廣場。");
                        break;
                //
                case 5:
                        xywar_message("宋軍探子：蒙古軍隊已開始進行調動，隨時會有所行動。");
                        break;
                case 6:
                        xywar_message(dj_name + "：傳我號令，全軍於３０秒後開始進攻襄陽城。");
                        xywar_message(HIR "蒙古人於30秒後開始進攻襄陽城，請注意守好相關路口。" NOR);
                        xywar_message(HIY "戰鬥中請使用指令 " HIR "xy" HIY " 隨時查看戰況詳情。" NOR);
                        if (tiemuzhen)
                        {
                                xywar_message(HIG "勝利條件：1、殺死成吉思汗\t       " HIM "失敗條件：1、蒙古人佔領襄陽中央廣場\n" HIG
                                              "\t              2、防守蒙古人攻擊30分鐘\t         " HIM "2、所有參加襄陽保衞戰的玩家剩餘不到五名\n" HIG
                                              "\t              3、全部殲滅蒙古人\n" 
                                              HIG "\t              4、蒙古人退兵\n" NOR);
                        }
                        else
                        {
                                xywar_message(HIG "勝利條件：1、防守蒙古人攻擊30分鐘\t       " HIM "失敗條件：1、蒙古人佔領襄陽中央廣場\n" HIG
                                              "\t              2、全部殲滅蒙古人。\t       " HIM "          2、所有參加襄陽保衞戰的玩家剩餘不到五名\n" 
                                              HIG "\t              3、蒙古人退兵\n" NOR);                                
                        }

                        // 30秒後蒙古軍開始進攻
                        remove_call_out("do_attack");
                        call_out("do_attack", 30);

                        call_out("do_attack_msg", 22, HIM "城外發出漫天戰鼓之聲，蒙古軍士蠢蠢欲動。");
                        call_out("do_attack_msg", 26, HIM "一聲犀利地號角聲響起，萬山雷動，捲起漫天狂沙，蒙古人軍隊已開始調動。");
                        
                        return;
                        break;

        }
        i += 1;
        remove_call_out("do_combatd_message");
        if (TEST)call_out("do_combatd_message", 2, i);
        else call_out("do_combatd_message", 50 + random(11), i);

        return;
}

// 停止報名，檢查報名是否達到人數要求
void check_sign_up()
{
        string dj_name; // 大將的姓名        
        object ob;
        
        // 停止報名
        sign_up_status = 0;

        xywar_message(HIY "郭靖：各位江湖義士，很感謝大家的支持，現在停止報名，並公佈我軍統計的報名人數！" NOR);
        xywar_message(HIW "襄陽副將：本次總共有 " HIY + chinese_number(sizeof(p)) + HIW " 位玩家報名參加襄陽保衞戰！" NOR);

        // 檢查離線玩家，從報名中刪除之
        sub_check_player();
                
        // 參加人數過少，結束襄陽戰，蒙古人退兵
        if (sizeof(p) < 20 && ! TEST)
        {
                status = 0; // 襄陽戰結束標誌

                xywar_message("各位江湖義士，本次襄陽保衞戰報名人數不足20人，既然天意如此，也罷！\n");

                if (tiemuzhen)dj_name = "成吉思汗";
                else dj_name = "大將軍";

                switch(random(5))
                {
                         case 1:
                                 call_out("xywar_message", 4, "蒙古副將：報告" + dj_name + "，我軍部分士兵突然染上瘟疫，目前已經無法戰鬥。");
                                 call_out("xywar_message", 6, dj_name + "：啊？竟有此事，立刻通知全軍立即撤退 ……");
                                 break;
                         case 2:
                                 call_out("xywar_message", 4, "蒙古探子：報告" + dj_name + "，襄陽城內居然毫無動靜，也不見防守的軍士，恐有詐。");
                                 call_out("xywar_message", 6, dj_name + "：恩，有道理，我也正覺得納悶。馬上通知全軍迅速撤兵，然後從長計議！");
                                 break;
                         default:
                                 call_out("xywar_message", 4, "蒙古百夫長：報告" + dj_name + "，我軍運糧車無故自燃，糧草輜重已損失殆盡。");
                                 call_out("xywar_message", 6, dj_name + "哼，壞我大事，來啊，拖出去砍了！立即通知全軍火速撤退，以免宋軍乘機偷襲！");
                                 break;
                }

                call_out("xywar_message", 8, "宋兵：報~~！蒙古人突然下令撤軍，所有來襲軍隊已全部撤回！");

                call_out("xywar_over", 10);
                return;
        }
        
        // 隨機選擇一個
        if (sizeof(p))player_leader = p[random(sizeof(p))];

        if (sizeof(player_leader))ob = find_player(player_leader);
        
        if (objectp(ob))
        {
                // 選擇玩家將領
                xywar_message(HIG "本次襄陽保衞戰由" + HIY + ob->name() + "(" + ob->query("id") + ")" HIG 
                                 "擔任襄陽守軍將領，可以根據戰況調動襄陽守軍(xy xmove 方向)。\n");
        }
        
        xywar_message("宋兵：報~~！蒙古軍將會在五分鐘後圍攻襄陽，請做好相關準備，死守(guard)蒙古軍必經之路。");

        // 10秒鐘後開始每擱一分鐘播報蒙古軍隊情況
        remove_call_out("do_combatd_message");
        call_out("do_combatd_message", 10, 1);

        return;
}

// 分配軍隊數量
int allot_soldier()
{
        int i, k;
        string *key_n_soldier;

        // 軍隊數量
        n_mg_tq = 40 + random(10);
        //n_mg_zb = 40 + random(10);
        n_mg_zb = 60 + random(20);
        //n_mg_gb = 60 + random(20);
        n_mg_gb = 120 + random(40);
        //n_mg_bb = 60 + random(20);
        n_mg_bb = 120 + random(40);
        n_xy_sb = 80 + random(20);

            // 1/5出現鐵木真
        if (random(5) == 1)tiemuzhen = 1;

        // 出現鐵木真兵力增加20%
        if (tiemuzhen)
        {
                n_mg_tq = n_mg_tq + n_mg_tq / 5;
                n_mg_zb = n_mg_zb + n_mg_zb / 5;
                n_mg_gb = n_mg_gb + n_mg_gb / 5;
                n_mg_bb = n_mg_bb + n_mg_bb / 5;
        }

        // 隨機選擇一個門士兵較多
        key_n_soldier = keys(n_soldier);
        i = random(sizeof(key_n_soldier));        
        
        // 該方向上多MORE_SOLDIER名士兵
        more_soldier_poision = key_n_soldier[i];
        
            // ({ 鐵騎、哲別、弓兵、 步兵  })
            // 平均分配到四門
        for (k = 0; k < sizeof(key_n_soldier); k ++ )
        {
                n_soldier[key_n_soldier[k]] = ({ n_mg_tq / 4,
                                                 n_mg_zb / 4,
                                                 n_mg_gb / 4,
                                                 n_mg_bb / 4,
                                               });
        }

            // ({ 鐵騎、哲別、弓兵、 步兵  })
            // 隨機一個門士兵較多
        n_soldier[more_soldier_poision] = ({ n_mg_tq / 4 + MORE_SOLDIER,
                                             n_mg_zb / 4 + MORE_SOLDIER,
                                             n_mg_gb / 4 + MORE_SOLDIER,
                                             n_mg_bb / 4 + MORE_SOLDIER,
                                       });
                                      
        // 記錄最初蒙古軍總數
        n_mg_sb2 = total_menggu_soldier("total");
        n_xy_sb2 = total_menggu_soldier("xiangyang");
        
        return 1;
}

// 初始化軍隊
int init_soldier()
{
        /**
        1、初始化郭靖
        2、設置襄陽戰等待標誌
        3、產生蒙古軍隊物件並移動到各自的位置
        4、產生襄陽士兵並分配到四個門
        **/        
        object ob, mg_dj;// 蒙古大將
        string *key_doors;
        string re_route; // 方向反向
        //int n_mg_tq, n_mg_zb, n_mg_bb, n_mg_gb, n_xy_sb;
        int i, n;

        // 設置等待攻擊標誌
        status = WAIT_START;
        
        xy_guojing = new(XYNPC + "guo");
        if (tiemuzhen)mg_dj = new(XYNPC + "tiemuzhen");
        else mg_dj = new(XYNPC + "mgdajiang");

        // 根據事先分配的數量進行各種兵種分配

        // 8個千夫長
        for (i = 0; i < 8 ; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");
                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                
                // 分配到四大門

                // 東門
                if (i < 2)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南門
                if (i >= 2 && i < 4)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西門
                if (i >= 4 && i < 6)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北門
                if (i >= 6)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        // 12個百夫長
        for (i = 0; i < 12 ; i ++)
        {
                ob = new(XYNPC + "mgbaifuzhang");
                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                // 分配到四大門

                // 東門
                if (i < 3)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南門
                if (i >= 3 && i < 6)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西門
                if (i >= 6 && i < 9)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北門
                if (i >= 9)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }
        // 4個副將
        for (i = 0; i < 4; i ++)
        {
                ob = new(XYNPC + "mgfujiang");
                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                // 分配到四大門

                // 東門
                if (i == 0)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南門
                if (i == 1)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西門
                if (i == 2)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北門
                if (i == 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_tq / 4;

        // n_mg_tq個鐵騎兵
        for (i = 0; i < n_mg_tq ; i ++)
        {
                ob = new(XYNPC + "mgqibing");
                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                // 分配到四大門

                // 東門
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北門
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_zb / 4;

        // n_mg_zb個哲別
        for (i = 0; i < n_mg_zb ; i ++)
        {
                ob = new(XYNPC + "mgzhebie");
                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                // 分配到四大門

                // 東門
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北門
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_gb / 4;

        // n_mg_gb個弓兵
        for (i = 0; i < n_mg_gb ; i ++)
        {
                ob = new(XYNPC + "mggongbing");
                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                // 分配到四大門

                // 東門
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北門
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_bb / 4;

        // n_mg_bb個步兵
        for (i = 0; i < n_mg_bb ; i ++)
        {
                ob = new(XYNPC + "mgbubing");
                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                // 分配到四大門

                // 東門
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北門
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }
        
        // 在more_soldier_poision門多增加MORE_SOLDIER名士兵        
        re_route = re_poision(more_soldier_poision);

        for (i = 0; i < MORE_SOLDIER ; i ++)
        {
                ob = new(XYNPC + "mgbubing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);                
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);

                ob = new(XYNPC + "mggongbing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                ob = new(XYNPC + "mgqibing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                
                ob = new(XYNPC + "mgzhebie");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);                
        }

        // 記錄，有時候會出現沒有襄陽士兵
        if (n_xy_sb <= 1)log_file("xiangyang_xysb", "ok at " + ctime(time()) + "\n");
        
        n = n_xy_sb / 4;

        // n_xy_sb個襄陽士兵
        for (i = 0; i < n_xy_sb ; i ++)
        {
                ob = new(XYNPC + "xyshibing");

                // 分配到四大門
                // 東門
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors2["east"]);
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors2["south"]);
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors2["west"]);
                }
                // 北門
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors2["north"]);
                }
        }

        key_doors = keys(doors);

        // 郭靖移動到中央廣場
        xy_guojing->move("/d/xiangyang/guangchang");


        // 移動NPC到軍營前清理軍營其他PLAYER
        clear_junying();
        
        // 蒙古大將移動到軍營
        if (tiemuzhen)
        {
                mg_dj = new(XYNPC + "tiemuzhen");
                mg_dj->move("/d/xiangyang/junying3");
                // 設置本次襄陽保衞戰的序列號
                mg_dj->set("ran_num", RAN_NUM);                
        }
        else
        {
                mg_dj = new(XYNPC + "mgdajiang");
                mg_dj->move("/d/xiangyang/junying3");
                // 設置本次襄陽保衞戰的序列號
                mg_dj->set("ran_num", RAN_NUM);                
        }

        // 兩名千夫長保護大將
        for (i = 0; i < 2; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");
                ob->move(environment(mg_dj));
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                if (tiemuzhen)                
                        ob->force_me("guard tie muzhen");                
                else
                        ob->force_me("guard menggu dajiang");
        }
        
        // 如果有鐵木真則增加 
        // 8名千夫長，4名副將，20名鐵騎、20名哲別保護
        if (tiemuzhen)
        {
                for (i = 0; i < 8; i ++ )
                {
                        ob = new(XYNPC + "mgqianfuzhang");
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 設置本次襄陽保衞戰的序列號
                        ob->set("ran_num", RAN_NUM);                        
                }
                                
                for (i = 0; i < 4; i ++ )
                {
                        ob = new(XYNPC + "mgfujiang");
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 設置本次襄陽保衞戰的序列號
                        ob->set("ran_num", RAN_NUM);                        
                }
                
                // 要設置不計算士兵數量標誌
                for (i = 0; i < 20; i ++ )
                {
                        ob = new(XYNPC + "mgqibing");
                        ob->set("no_total", 1);
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 設置本次襄陽保衞戰的序列號
                        ob->set("ran_num", RAN_NUM);                        
                }

                for (i = 0; i < 20; i ++ )
                {
                        ob = new(XYNPC + "mgzhebie");
                        ob->set("no_total", 1);
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 設置本次襄陽保衞戰的序列號
                        ob->set("ran_num", RAN_NUM);                        
                }
        }

        // 移動10名步，10名弓手兵到軍營外/d/xiangyang/junying1
        // 守護方向north
        for (i = 0; i < 10; i ++)
        {
                ob = new(XYNPC + "mgbubing");
                ob->set("no_total", 1);
                ob->move("/d/xiangyang/junying1");
                ob->force_me("guard north");
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                ob = new(XYNPC + "mggongbing");
                ob->set("no_total", 1);
                ob->move("/d/xiangyang/junying1");
                ob->force_me("guard north");
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);                
        }

        // 移動6名千夫長，40名哲別，40名鐵騎守護軍營/d/xiangyang/junying2
        for (i = 0; i < 6; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");
                ob->move("/d/xiangyang/junying2");
                ob->force_me("guard north");
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);                
        }
        for (i = 0; i < 40; i ++)
        {
                ob = new(XYNPC + "mgzhebie");
                ob->set("no_total", 1);                
                ob->move("/d/xiangyang/junying2");
                ob->force_me("guard north");
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);
                                
                ob = new(XYNPC + "mgqibing");
                ob->set("no_total", 1);
                ob->move("/d/xiangyang/junying2");
                ob->force_me("guard north");
                // 設置本次襄陽保衞戰的序列號
                ob->set("ran_num", RAN_NUM);                
        }

        call_out("xywar_message", 2, "蒙古軍隊已經抵達襄陽城外安營紮寨，現在全軍正侯命待發！");

        call_out("xywar_message", 15, "宋兵探子：此次蒙古軍隊人數大約為： " HIY +
                                      sprintf("%d", total_menggu_soldier("total")) + HIC " 人。");

        // 郭靖通知玩家進行報名
        call_out("xywar_message", 5, HIY "郭靖：各路江湖豪傑，武林同道，現今蒙古人即將圍攻襄陽，情況危機，"
                                         "如願保衞襄陽出一份力，請\n            速到" HIM "襄陽中央廣場" HIY "進行報名吧！" NOR);

        // 設置可報名標誌
        sign_up_status = 1;

            // 5分鐘後停止報名，並檢查報名人數是否達到要求
        remove_call_out("check_sign_up");
        if (TEST)call_out("check_sign_up", 10);
        else call_out("check_sign_up", 300);

        return;
}
// 襄陽援軍達到後的動作
void add_xy_soldier_action()
{
        call_out("xywar_message", 1, HIY "蒙古探子：報！襄陽援兵已經部署完畢，分散於四城門抵抗我軍。" NOR);
        
        if (random(2) == 1)        
                call_out("xywar_message", 3, HIY "蒙古將領：哼！看來他們是在做最後的垂死掙扎，傳令加強進攻，儘快拿下城池。" NOR);
        else
                call_out("xywar_message", 3, HIY "蒙古將領：傳令全軍將士加強攻勢，萬萬不可輕敵，這次務必要順利拿下襄陽城" NOR);
}

// 增加襄陽士兵
void add_xy_soldier()
{
        object ob;
        string re_route; // 方向反向
        int i, n, k;
        string *key_n_soldier;

        if (now_status() != WARRING && now_status() != WAIT_START && ! TEST)return;
        
        n_xy_sb = ADD_XY_SOLDIER;
        n = ADD_XY_SOLDIER / 4;
        
        // n_xy_sb個襄陽士兵
        for (i = 0; i < n_xy_sb ; i ++)
        {
                ob = new(XYNPC + "xyshibing");

                // 分配到四大門
                // 東門
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors3["east"]);
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors3["south"]);
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors3["west"]);
                }
                // 北門
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors3["north"]);
                }
        }        


        // 修改襄陽軍數量記錄表
        n_xy_sb = n_xy_sb + ADD_XY_SOLDIER;

        xywar_message(HIY "襄陽援兵已抵達襄陽城，並平均分散在四門抵禦蒙古人。");
        
        call_out("add_xy_soldier_action", 2); 
        
        return;
}

// 外部調用：增加襄陽士兵，起前端調用，增加延遲效果作用
void add_xy_soldier_ext(object me)
{        
        // 檢查是否可調用
            if (now_status() != WARRING && now_status() != WAIT_START)
            {
                    write("戰鬥還沒有開始呢。\n");
                    return;
            }            
        
        // 調用後增加調用標誌
        add_xyb_flag = 1;
        
        call_out("xywar_message", 2, HIR + me->name() + "使用兵符，增派襄陽守軍。" NOR);
        call_out("xywar_message", 4, HIR + "襄陽援軍正在分配和調動，援軍抵達後將平均分散在四門抵抗蒙古軍。" NOR);
        call_out("xywar_message", 6, HIR + "襄陽援軍即將抵達襄陽城，請提前做好相關戰術調動。" NOR);
        call_out("add_xy_soldier", 12);
}

// 蒙古人派兵增援
// 需要在設置方位的時候檢查 yb_attack_where 變量，如果不為"none"則需要單獨設置
// 目的是將援軍火力在某一方向上集中，便於攻城
void add_soldier()
{
        object ob;
        string re_route; // 方向反向
        int i, n, k;
        string *key_n_soldier;

        // 根據事先分配的數量進行各種兵種分配
        
        // 8個千夫長
        for (i = 0; i < 8 ; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");
                // 分配到四大門

                // 東門
                if (i < 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南門
                if (i >= 2 && i < 4)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西門
                if (i >= 4 && i < 6)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北門
                if (i >= 6)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        // 12個百夫長
        for (i = 0; i < 12 ; i ++)
        {
                ob = new(XYNPC + "mgbaifuzhang");
                // 分配到四大門

                // 東門
                if (i < 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南門
                if (i >= 3 && i < 6)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西門
                if (i >= 6 && i < 9)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北門
                if (i >= 9)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }
        // 4個副將
        for (i = 0; i < 4; i ++)
        {
                ob = new(XYNPC + "mgfujiang");
                // 分配到四大門

                // 東門
                if (i == 0)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南門
                if (i == 1)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西門
                if (i == 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北門
                if (i == 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_tq / 4;

        // n_mg_tq個鐵騎兵
        for (i = 0; i < n_mg_tq ; i ++)
        {
                ob = new(XYNPC + "mgqibing");

                // 分配到四大門

                // 東門
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北門
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_zb / 4;

        // n_mg_zb個哲別
        for (i = 0; i < n_mg_zb ; i ++)
        {
                ob = new(XYNPC + "mgzhebie");

                // 分配到四大門

                // 東門
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北門
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_gb / 4;

        // n_mg_gb個弓兵
        for (i = 0; i < n_mg_gb ; i ++)
        {
                ob = new(XYNPC + "mggongbing");

                // 分配到四大門

                // 東門
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北門
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_bb / 4;

        // n_mg_bb個步兵
        for (i = 0; i < n_mg_bb ; i ++)
        {
                ob = new(XYNPC + "mgbubing");

                // 分配到四大門

                // 東門
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南門
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西門
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北門
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {                
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        };
                }
        }
        
        // 在more_soldier_poision門多增加MORE_SOLDIER名士兵        
        re_route = re_poision(more_soldier_poision);

        for (i = 0; i < MORE_SOLDIER ; i ++)
        {
                ob = new(XYNPC + "mgbubing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);

                ob = new(XYNPC + "mggongbing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                
                ob = new(XYNPC + "mgqibing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);

                ob = new(XYNPC + "mgzhebie");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
        }

        // 修改蒙古軍數量記錄表
        key_n_soldier = keys(n_soldier);

        for (k = 0; k < sizeof(key_n_soldier); k ++ )
        {
                n_soldier[key_n_soldier[k]] = ({ n_soldier[key_n_soldier[k]][0] + n_mg_tq / 4,
                                                 n_soldier[key_n_soldier[k]][1] + n_mg_zb / 4,
                                                 n_soldier[key_n_soldier[k]][2] + n_mg_gb / 4,
                                                 n_soldier[key_n_soldier[k]][3] + n_mg_bb / 4,
                                               });
        }

            // ({ 鐵騎、哲別、弓兵、 步兵  })
            // 隨機一個門士兵較多
        n_soldier[more_soldier_poision] = ({ 
                                             n_soldier[more_soldier_poision][0] + MORE_SOLDIER,
                                             n_soldier[more_soldier_poision][1] + MORE_SOLDIER,
                                             n_soldier[more_soldier_poision][2] + MORE_SOLDIER,
                                             n_soldier[more_soldier_poision][3] + MORE_SOLDIER,
                                          });

        xywar_message(HIR "蒙古人增援部隊已抵達襄陽，並準備開始攻城。");

        // 散佈虛假消息
        if (yb_attack_where != "none")
        {
                string string_ran_doors = random_doors_name();
                
                xywar_message(HIY "蒙古大將：蒙古援軍聽令，所有分隊朝着" + HIR + string_ran_doors +
                              HIY "方向進攻，不得有誤。" NOR);
                xywar_message(NOR + YEL "頃刻間，離" + string_ran_doors + NOR + YEL "不遠處，塵土飛揚，"
                              "似乎聚集了大量軍隊。" NOR);
        }

        return;
}

// 江湖人士支援
void support_npc()
{
        object ob1, ob2, ob3, ob4;
        string guard_door,guard_door_name;
        string *sp;
        string pos;
        
        if (random(10) > 3 && ! TEST)return;
        
        switch(random(2))
        {
                // 楊過和小龍女
                case 0:
                        call_out("xywar_message", 2, HIW "楊過：郭伯伯，現今襄陽有難，誅殺蒙古韃子怎能不算過兒一份！" NOR);
                        call_out("xywar_message", 5, HIW "小龍女：過兒，你到哪兒我就跟你到哪兒 ……" NOR);
                        call_out("xywar_message", 8, HIY "郭靖大笑：好好好！男兒以保家衞國為己任，有過兒你和龍姑娘在，我就放心了！" NOR);
                        // 隨機選擇一個門守護
                        sp = keys(doors2);
                        pos = sp[random(sizeof(sp))];
                        guard_door = doors2[pos];
                        guard_door_name = doors2_name[pos];
                        call_out("xywar_message", 12, HIW "楊過：我和龍兒也是路過此地，聽説蒙古人將要圍攻襄陽城，所以便來看看。" NOR);
                        call_out("xywar_message", 15, HIW "楊過：我和龍兒決定了要助郭伯伯一臂之力，保衞襄陽城。" NOR);
                        call_out("xywar_message", 18, HIW "小龍女望了郭靖一眼點了點頭。" NOR);
                        call_out("xywar_message", 20, HIY "郭靖激動地説到：好，過兒。那你們就守護" + HIR + guard_door_name + HIY "吧！" NOR);
                        call_out("xywar_message", 22, HIW "言畢，楊過和小龍女直奔" + guard_door_name + "。" NOR);
                        
                        ob1 = new(YANGGUO);
                        ob2 = new(LONGNV);

                        ob1->move(guard_door);
                        ob1->force_me("guard " + re_poision(pos));
                        ob2->move(guard_door);
                        ob2->force_me("guard " + ob1->query("id")); // 小龍女只保護楊過
                        ob1->set("mate", ob2);
                        ob2->set("mate", ob1);
                        
                        xy_msg1 = "楊過和小龍女前來支援，守護" + HIR + guard_door_name;
                        break;

                // 東邪等
                case 1:
                        call_out("xywar_message", 2, HIW "黃藥師：哼！蒙古韃子竟然如此囂張，我黃老邪就偏要跟你們會會！" NOR);
                        call_out("xywar_message", 6, HIY "歐陽鋒：哈哈哈！既然黃老邪有這個雅興，那我西毒歐陽鋒怎能不湊湊熱鬧，哈哈哈！" NOR);
                        call_out("xywar_message", 10, HIM "一燈大師雙手合十道：可憐我天下蒼生又將置身火海，生靈塗炭，老衲豈能坐視不理！" NOR);
                        call_out("xywar_message", 14, HIG "洪七公：哈哈，這麼熱鬧？我老叫花子可不能錯過……" NOR);
                        call_out("xywar_message", 18, HIC "郭靖一臉興奮：好好好！襄陽有救了！" NOR);
                        call_out("xywar_message", 20, HIR "聽説東邪、西毒、南帝、北丐四大宗師加入到襄陽保衞戰當中，共同抗擊蒙古人。" NOR);
                        
                        ob1 = new(DONGXIE);
                        ob2 = new(XIDU);
                        ob3 = new(NANDI);
                        ob4 = new(BEIGAI);
                        ob1->move(doors2["east"]);
                        ob1->force_me("guard " + "west");
                        ob2->move(doors2["west"]);
                        ob2->force_me("guard " + "east");
                        ob3->move(doors2["south"]);
                        ob3->force_me("guard " + "north");
                        ob4->move(doors2["north"]);
                        ob4->force_me("guard " + "south");        

                        xy_msg1 = "東邪、西毒、南帝、北丐四大高手前來增援，分別守護四門。";        

                        break;
                        
                default:
                        return;
        }
}

void start_story(int i)
{
        string *story = ({
                "宋朝末年，朝廷昏庸腐敗，蒙古人大舉伐宋，天下生靈塗炭，民不聊生 ……",
                "襄陽城乃宋朝戰略要地，連年來為奪取襄陽，蒙古人起用重兵圍攻 ……",
                "但是，郭靖黃蓉夫婦長年來帶領襄陽兵士，死守城池，頑強抵抗，令蒙古人久攻不下。",
                "蒙古軍營 ……",
                "成吉思汗：襄陽不取，難以成就我蒙古大業，看來需要加派兵力強攻襄陽城！",
                "成吉思汗：傳我號令，加派兵力，準備強攻襄陽，此次一定要將襄陽城拿下。",
                HIR "提示：蒙古成吉思汗派出重兵進攻襄陽！" NOR,
                "襄陽城內。"
                "宋兵：報！，據前方探子回報，蒙古人已派兵直逼襄陽！！！",
                "郭靖：哎，蒙古人久攻襄陽不下，這次一定又加重兵力，欲強取我襄陽城。",
                "郭靖頓了頓對宋兵吩咐道：傳令襄陽所有軍士加強戒備，等待號令！",
                "宋兵應了一聲轉身出去。",
                "郭靖長歎道：這次蒙古人大舉進攻襄陽，不知道又要有多少無辜的人犧牲，哎...",
                "郭靖頓了頓對坐在一旁的黃蓉説道：這次蒙古人來勢洶洶，對襄陽志在必得，以目前襄陽城的兵力恐怕堅守不了多久，\n"
                "            不知蓉兒你有什麼好辦法可以幫助渡過這一次危難，保住襄陽城！",
                "黃蓉站起在房中走了一圈對郭靖説道：以目前的形勢看，敵強我弱，如果光靠襄陽城目前這點兵力恐怕 ……",
                "黃蓉頓了頓又道：不如以靖哥哥你的大名，招募天下英雄豪傑來此共同作戰，或可保住襄陽城。",
                "郭靖猛然間手一拍桌子將正在思索的黃蓉嚇了一大跳：好，就這麼決定了，這次無論如何都要守住襄陽城。",
                "黃蓉：@@",
                "此時，一位宋兵急匆匆地跑了進來道：郭將軍，據探子回報，蒙古軍已逼近襄陽，大約五分鐘後可抵達城外！",
                "郭靖正色道：傳令襄陽全體軍士，振作精神，隨時準備和蒙古人開戰。",
                "宋軍應了一聲，轉身跑出去。",
                "郭靖和黃蓉低聲交談了幾句後也跟着出去，直奔軍營 …… 大戰一觸即發！",
                HIR "提示：蒙古軍隊將於五分鐘後抵達襄陽城外，請正在任務的玩家停止任務，以免無辜受害！！！" NOR,
        });
        
        
        
        // 五分鐘後
        // 二分鐘後
        // 隨機判斷是否江湖人士參與
        if (i >= sizeof(story))
        {
                remove_call_out("init_soldier");
                if (TEST)call_out("init_soldier", 5);
                else call_out("init_soldier", 300); // 初始化必要數據
                
                // 江湖人士資援襄陽
                remove_call_out("support_npc");
                if (TEST)call_out("support_npc", 2);
                else call_out("support_npc", 120);
                
                return;
        }

        xywar_message(story[i]);
        i += 1;

        remove_call_out("start_story");
        call_out("start_story", 4, i);
        return;
}

// 開始襄陽戰
void start_xywar()
{
        /*
        1、分配軍隊數量，緊根着開始故事情節敍述
        2、1、完成五分鐘後初始化-->init_soldier()
        3、正式啟動戰鬥
        */

        start_status = 1;    // 設置情節開始以免系統重複調用
        start_time = time();  // 設置開始時間

        RAN_NUM = 100 + random(900); // 產生本次襄陽保衞戰序列號，共三位數
        
        allot_soldier(); // 分配軍隊數量

        // 開始敍述故事
        start_story(0);

}

// 返回本次玩家將領
// 如果其退出戰鬥則返回 “無“
string leader_player()
{        
        if (! if_sign_up(player_leader))return "無";
        
        return player_leader;
}

// 玩家可控制襄陽守軍
// 1、查詢目前守軍守衞地點
// 2、設置守軍集合兵力守衞地點
// 如果襄陽士兵死完則無法再顯示
// 蒙古軍派遣援軍後1分鐘內無法查詢

// 查詢守軍及蒙古軍情況
void show_soldier(object me)
{
        int total, xytotal, w, e, s, n;
        string msg;
        
        total = total_menggu_soldier("total");
        xytotal = total_menggu_soldier("xiangyang");
        w = total_menggu_soldier("west");
        e = total_menggu_soldier("east");
        s = total_menggu_soldier("south");
        n = total_menggu_soldier("north");
                
        msg =  HIR "\n根據探子的消息，帶來以下襄陽戰報：\n" NOR;
        msg += HIC "--------------------------------------------------------------------\n" NOR;
        if (time() - last_move_xysolder < 60)
        {
                msg += HIG "蒙古軍剛增派了大量援軍，目前準確人數正在刺探當中 ……\n" NOR;
        }
        else
        {
                msg += HIG "蒙古軍總數：" HIR + sprintf("%d", total) + HIG "人，其中：" 
                       "青龍門" HIR + sprintf("%d", e) + HIG "人，朱雀門" HIR + sprintf("%d", s) + HIG "人，"
                       "白虎門" HIR + sprintf("%d", w) + HIG "人，玄武門" HIR + sprintf("%d", n) + HIG "人。\n" NOR;
        }

        msg += HIW "襄陽守軍總人數: " HIR + sprintf("%d", xytotal) + HIW "人，主要集中在" HIR + 
               xy_soldier_poision("name") + "(" + xy_soldier_poision("poision") + HIW ")。\n" NOR;    
        msg += HIC "--------------------------------------------------------------------\n" NOR;        

        tell_object(me, msg);
        
        return;
}


// 調動襄陽守軍
// 權限在/cmds/usr/xy.c 裏做判斷
void move_xysoldier(object me, string p)
{
        int xytotal;
        string msg, dj_name;
        
        if (now_status() != WARRING && now_status() != WAIT_START)
        {
                write("襄陽保衞戰還沒有開始，你無法調動襄陽守軍。\n");
                return;
        }
        
        // 上次調動時間間隔至少為MOVE_WAIT秒
        if (time() - last_move_xysolder < MOVE_WAIT)
        {
                write("距離上次調動襄陽守軍時間不足60秒，士兵疲憊，無法連續調動。\n");
                return;
        }
        
        xytotal = total_menggu_soldier("xiangyang");
        
        if (xytotal < 5)
        {
                write("目前襄陽守軍數量太少，無法進行調動。\n");
                return;
        }
        
        if (p != "west" && p != "east" && p != "north" && p != "south")
        {
                write("你要將襄陽守軍往哪個方向調動？(west|north|east|south)\n");
                return;
        }
        
        // 設置襄陽守軍新的防守方向
        xysb_poision = p;
        
        // 設置調動時間
        last_move_xysolder = time();
        
        write("你已經下令調動襄陽守軍，襄陽守軍正趕往" + HIY + xy_soldier_poision("name") + NOR "地點抵禦蒙古人。\n" NOR);
        
        xywar_message(HIG + me->name() + "正在調動襄陽守軍，襄陽守軍已經趕往" + HIY + xy_soldier_poision("name") + HIG "地點抵禦蒙古人。\n" NOR);
        
        if (tiemuzhen)dj_name = "成吉思汗";
        else dj_name = "蒙古大將";
        
        switch(random(5))
        {
                case 0:
                        msg = "哼，此次襄陽城至在必得，這只是宋軍在做垂死的抵抗。";
                        break;
                case 1:
                        msg = "哈哈哈，雕蟲小技，不過是以卵擊石，螳臂當車而已。";
                        break;                        
                case 2:
                        msg = "咦？次此宋軍將領是何許人也？竟然懂得如此用兵，看來中原人才輩出，我等切不可輕敵。";
                        break;
                
                default:
                        msg = "哼，我蒙古勇士以一敵十，爾等老弱殘兵豈能與我蒙古人的爭鋒。";
                        break;                
        }
        
        msg = HIM + dj_name + "：" + msg + NOR;

        xywar_message(msg);
        
        return;
}


// 調用蒙古軍戰術
// 增加援軍
void combat_add_soldier()
{
            
            // 最多增加ADD_MGB_TIMES次
            if (add_mgb_times >= ADD_MGB_TIMES)
            {
                    write("增援次數已達極限。\n");
                    return;
            }

            if (now_status() != WARRING && now_status() != WAIT_START)
            {
                    write("戰鬥還沒有開始呢。\n");
                    return;
            }

            last_add_mgb_time = time();
            add_mgb_times += 1;
            
            write(HIW "你下令派出蒙古軍增援。\n" NOR);

            // 開始準備調動            
            xywar_message(HIR "蒙古人點燃了狼煙，通知蒙古軍增援。" NOR);

            // 延遲派兵
            remove_call_out("delay_add_soldier");
            call_out("delay_add_soldier", 30 + random(10));

            call_out("xywar_message", 3, HIR "蒙古援軍已經收到訊息，準備開始調動。");
            call_out("xywar_message", 8, HIR "蒙古增援部隊已開始起程，很快將達到襄陽。");
            call_out("xywar_message", 15, HIR "蒙古援軍正連夜趕路，即將抵達襄陽城。");
}

// 蒙古延遲派兵
void delay_add_soldier()
{
        if (now_status() != WARRING && ! TEST)return;

        // 派兵增援
        add_soldier();
}

// 戰術：虛假退兵
void combat_xjtuibing()
{
        
}

// 戰術：聲東擊西
void combat_sdjixi()
{
        
}

// 集中兵力攻擊某門
// 參數pos 為方向，指相對於襄陽廣場的方向 west,east,north,south
void combat_attack_all(string pos)
{
        // 50%機率虛假説明攻擊方向
        if (random(2) == 1)
        {
        }
        
        
        
}