// inherit: mroom.c

// 怪物練級房間
// n_time    怪物刷新時間
// n_npc     怪物刷新數量
// n_max_npc 房間容納最多怪物數量，即一次最多刷新多少個怪物
// s_npc     怪物種類，文件路徑
// n_av_refresh 平均刷新速率
// 一個房間只能定義一種怪物

#include <ansi.h>

inherit ROOM;

// 計算刷新速率的間隔時間
// 每過一段時間通過一定算法計算刷新速率
#define COUNT_REFRESH_TIME         45

void start_heart_beat()
{
        // 默認為心跳1
        set_heart_beat(1);
}

void setup()
{
        mapping product;
        string mine;
        int count;

        set("no_clean_up", 1);
                set("no_roar", 1);
                //set("no_flyto", 1); // 不能騎馬或MISS到這裏，已經在horse.c做限制

                // 設置房間怪物屬性
                if (! query("n_time"))set("n_time", 60);                                // 默認怪物45秒刷新一次
                if (! query("n_npc"))set("n_npc", 1);                                   // 默認怪物每次刷新一個
                if (! query("n_max_npc"))set("n_max_npc", 1);                           //默認為1，房間容納最多怪物數量，即一次最多刷新多少個怪物
                if (! query("s_npc"))set("s_npc", "/clone/quarry/zhu");                 // 默認怪物為野獸—豬

                set("n_die", 0);                    // 單位時間內怪物死亡數量
                if (query("last_refresh_time"))     // 上次刷新時間
                        set("last_refresh_time", query("last_refresh_time"));


                if (query("last_count_refresh_time"))     // 上次計算刷新速率的時間
                        set("last_count_refresh_time", query("last_count_refresh_time"));
                
                ::setup();

        start_heart_beat();
}

void init()
{
                if (random(2))this_player()->start_busy(1);                     
}

// 每次心跳執行的操作
// 刷新時間到後刷新怪物，並計算下次刷新時間及怪物數量

void heart_beat()
{
                object ob_npc;
                object env;
                object *inv, *obs;
                int n_left_npc; // 當前怪物數量和最大容納怪物數的差
                int n_npc; // 設置怪物的數量
                int i;  // 計數變量
                int refresh_total; // 時間間隔內總共刷新的怪物數量
                int new_n_time;  // 設置新的刷新時間
                int new_n_npc; // 設置怪物刷新數量

                //object me;

                                
                env = this_object();

                if( new_n_time <= 0)new_n_time=query("n_time", env);
                if( new_n_npc <= 0)new_n_time=query("n_npc", env);
                
                // 如果為蓬萊島，則判斷蓬萊島是否開放
                if( query("penglai", env) && !GIFT_D->is_open_pld())return ;

                inv = all_inventory(env);

                obs = filter_array(inv, (: base_name($1) == query("s_npc") :)); // 過濾掉非本房間怪物的其他文件

                // 時間到達則刷新怪物
                n_left_npc = query("n_max_npc") - sizeof(obs);
                if (n_left_npc > 0 && time() - query("last_refresh_time") >= query("n_time"))
                {
                        n_npc = n_left_npc >= query("n_npc") ? query("n_npc") : n_left_npc;

                        for (i = 0; i < n_npc; i ++ )
                        {
                                ob_npc = new(query("s_npc"));
                                if (! objectp(ob_npc))
                                {
                                        log_file("mroom", "無法找到npc文件 " + query("s_npc") + "\n");
                                        return;
                                }
                        
                                ob_npc->move(env);
                        }

                        set("last_refresh_time", time());
                }

                // 計算刷新速率的算法
                // 每間隔COUNT_REFRESH_TIME秒計算一次，然後根據計算結果重新設置
                // 怪物刷新時間和數量
                if (time() - query("last_count_refresh_time") >= COUNT_REFRESH_TIME)
                {
                        // 算法描述
                        // 通過統計單位時間內怪物死亡數量
                        // 判定刷新速度，只計算怪物減少或不變的數量，不計算增加的數量

                        // 時間間隔內總共刷新的怪物數量
                        refresh_total = COUNT_REFRESH_TIME / query("n_time") * query("n_npc");

                        if (refresh_total < 1)refresh_total = 1;
                        
                        // 設置刷新時間按照比例計算
                        new_n_time = query("n_time") * query("n_die") / refresh_total;
                        
                        // 滿刷，即刷出多少怪都全部殺死增加刷新
                        if (new_n_time >= query("n_time"))
                        {
                                new_n_time = new_n_time - new_n_time / 3;
                                new_n_npc = query("n_npc") + 1;
                        }
                        // 殺死怪物超過刷出的一半增加刷新
                        else if (new_n_time >= query("n_time") / 2)
                        {
                                new_n_time = new_n_time - new_n_time / 5;
                                new_n_npc = query("n_npc") + 1;
                        }
                        else // 未超過一半刷新速度則降低刷新速度
                        {
                                new_n_time = new_n_time + new_n_time / 2;
                                new_n_npc = query("n_npc") / 2;
                        }
                        
                        // 溢出判斷
                        if (new_n_time > query("n_time"))new_n_time = query("n_time");
                        if (new_n_time <= 0)new_n_time = query("n_time"); // n_die == 0                                         
                        if (new_n_time < 15)new_n_time = 15;
                        if (new_n_npc < 1)new_n_npc = 1;                                
                        if (new_n_npc > query("n_max_npc"))new_n_npc = query("n_max_npc");
                        set("n_time", new_n_time);
                        set("n_npc", new_n_npc);

                        // 計數清0
                        set("n_die", 0);

                        // 記錄本次計算的時間
                        set("last_count_refresh_time", time()); 

                }

}

// 怪物死亡時通知該房間累計怪物死亡熟練，以便計算刷新速率
void npc_die(object ob)
{
        addn("n_die", 1);
}
