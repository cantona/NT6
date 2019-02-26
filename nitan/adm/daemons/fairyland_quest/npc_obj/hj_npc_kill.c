//                標準描述長度示例                                   |
// 幻境內人物  殺戮型 （並且會攜帶玩家必須尋找的寶物）
// by naihe  2002-10-27  於茂名
// naihe 05-9-4 15:43 優化一下，同時增加2個類型
// naihe 05-9-5 11:02 再次優化

#include <ansi.h>

inherit NPC;

#include "hj_settings/room_amount_hj.h"
#include "hj_settings/health_desc.h"
#include "hj_settings/get_hj_dir.h"
#include "hj_settings/hj_msg.h"

#define     NPC_NORMAL_SIZE         6       // 普通NPC的範圍，從 0~ SIZE-1
#define     NPC_ZUREN_INDEX         5       // 族人NPC的索引號
#define     NPC_ZUZHANG_INDEX       6       // 族長NPC的索引號
#define     NPC_YL_WUSHI_INDEX      10      // 幽靈 -- 武士
#define     NPC_YL_CIKE_INDEX       7       // 幽靈 -- 刺客
#define     NPC_YL_SHASHEN_INDEX    8       // 幽靈 -- 殺神
#define     NPC_YL_YINSHI_INDEX     9       // 幽靈 -- 隱士

void checking();
void npc_dead_reward();
void npc_dead_reward_wushi();
void npc_dead_reward_sp( int total_reward );

// 第一個參數指定“族”， 第二個參數指定級別。
varargs void setme( int npc_class, int npc_level )
{
    int std_power, std_busy, std_hpmax;
    mapping *npc_info, *npc_info2, info;
    string id, *class_list;
    int i;
    // npc 標準信息 -----------------------------------------------------
    npc_info2 = ({
        ([ "name":"小頭領",
            "id":({ "tou ling", "ling", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // 越大越不愛主動攻擊
        ]),
        ([ "name":"力士",
            "id":({ "li shi", "shi", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // 越大越不愛主動攻擊
        ]),
        ([ "name":"壯漢",
            "id":({ "zhuang han", "han", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // 越大越不愛主動攻擊
        ]),
        ([ "name":"兇徒",
            "id":({ "xiong tu", "tu", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // 越大越不愛主動攻擊
        ]),
        ([ "name":"法師",
            "id":({ "fa shi", "shi", }),
            "auto_kill": 1,
            "hit_suck": 1,  // 攻擊會吸取 hp
            "peaceful": (5+random(15)), // 越大越不愛主動攻擊
        ]),
        ([ "name":"族人",
            "id":({ "zu ren", "ren", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // 越大越不愛主動攻擊
        ]),
        ([ "name":HIY"族長",
            "id":({ "zu zhang", "zhang", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // 越大越不愛主動攻擊
        ]),
        ([ "special_name": HIB"幽靈族"HIY"刺客"NOR,
            "special_long" : "這是一個幽靈族的刺客，看起來身手敏捷，矯健過人。\n",
            "id":({ "youling cike", "cike", }),
            "auto_kill": 1,
            "peaceful": 3, // 越大越不愛主動攻擊
            //"hit_busy": 1, // 攻擊會造成忙時
            "dead_reward_score" : 150,    // NPC死亡時會給予獎勵
            "max_busy_limit" : 3,  // 本NPC最大隻能接受的 busy time，超過時會強制恢復自由
            "del_msg" : "$N忽地發出一陣淒厲長嘯，隨後「嘭」地一聲消失不見了。\n",
        ]),

        ([ "special_name": HIB"幽靈族"HIR"殺神"NOR,
            "special_long" : "這是一個幽靈族的殺神，全身散發驚人的殺氣！\n",
            "id":({ "youling shashen", "shashen", }),
            "auto_kill": 1,
            "peaceful": 3, // 越大越不愛主動攻擊
            "hit_busy": 1, // 攻擊會造成忙時
            "dead_reward_score" : 1500,    // NPC死亡時會給予獎勵
            "del_msg" : "$N忽地發出一陣淒厲長嘯，隨後「嘭」地一聲消失不見了。\n",
        ]),
        ([ "special_name":HIB"幽靈族"HIM"隱士"NOR,
            "special_long" : "這是一個幽靈族的隱士，全身散發着一股莫名的壓迫之氣，讓人不敢靠近。\n",
            "id":({ "youling yinshi", "yinshi", }),
            "hit_busy": 1, // 攻擊會造成忙時
            "dead_reward_score" : 800,    // NPC死亡時會給予獎勵
            "del_msg" : "$N忽地發出一陣淒厲長嘯，隨後「嘭」地一聲消失不見了。\n",
        ]),
        ([ "special_name": HIB"幽靈族武士"NOR,
            "special_long" : "這是一個幽靈族的武士，陰森詭異。\n",
            "id":({ "youling wushi", "wushi", "shi", }),
            "hit_busy": 1, // 攻擊會造成忙時
            "del_msg" : "$N忽然發出一陣刺耳的梟叫聲，瞬時間身影朦朧，消失不見了！\n",
        ]),
    });
    // npc 戰鬥相關信息 -----------------------------------------------------
    std_power = 15 + random( 6 );
    std_busy = 3 + random( 6 );
    std_hpmax = 50 + random( 251 );
    npc_info = ({
        ([ "power": std_power * 2,  "busy": std_busy,    "hpmax": 400+random(201) ]),  // 小頭領    0
        ([ "power": std_power *3/2, "busy": std_busy,    "hpmax": std_hpmax       ]),  // 力士      1
        ([ "power": std_power,      "busy": std_busy,    "hpmax": 300+random(201) ]),  // 壯漢      2
        ([ "power": std_power,      "busy": 2+random(3), "hpmax": std_hpmax       ]),  // 兇徒      3
        ([ "power": std_power,      "busy": 2+random(2), "hpmax": 80+random(71)   ]),  // 法師      4
        ([ "power": std_power,      "busy": std_busy,    "hpmax": std_hpmax       ]),  // 族人      5
        ([ "power": std_power * 3,  "busy": 3+random(4), "hpmax": 800+random(701) ]),  // 族長      6
        ([ "power": std_power / 2,  "busy": 1,           "hpmax": 1500+random(501) ]), // 幽靈刺客  7
        ([ "power": std_power * 2,  "busy": 1+random(2), "hpmax": 8000+random(3001) ]),// 幽靈殺神  8
        ([ "power": std_power * 3,  "busy": 2+random(3), "hpmax": 3000+random(1001) ]),// 幽靈隱士  9
        ([ "power": 10+random(21),  "busy": 2+random(2), "hpmax": 400+random(201) ]),  // 幽靈武士  10
    });
    // 更新此處設置時，需要計算正確的值，並更新 help 文件。
    // ---------------------------------------------------------------------------
    class_list = ({
        YEL"蠻野族",
        YEL"猛力族",
        YEL"矮妖族",
        YEL"山怪族",
        YEL"巨人族",
    });
    i = sizeof( npc_info2 );
    if( npc_class == 88 )  // 指定“族”為任務NPC  (僅由 hj_room1.c 裏調用)
    {
        npc_class = -1;
        npc_level = NPC_YL_WUSHI_INDEX;    // 則指定為 幽靈武士
        set("job_npc", 1 );
    }
    else if( npc_class == 99 ) // 指定“族”為隨機
    {
        npc_class = random(5);  // 那麼就隨機
    }
    else if( npc_class < 0 || npc_class > 4 )   // 數據錯誤的話
    {
        npc_class = random(5);  // 那麼也隨機
    }
    // ok. 選擇  lv
    if( npc_class != -1 )  // 不是指定任務NPC的話，才繼續處理
    {
        // 省略參數或有誤時，隨機出現
        if( npc_level < 1 || npc_level > i )
        {
            npc_level = random( NPC_NORMAL_SIZE );    // 隨機獲得一個“正常類型NPC”
            if( !query("take_gem_npc") && random( 300 ) == 88 )
                npc_level = NPC_YL_SHASHEN_INDEX;     // 很小機率出現殺神
            else if( !query("take_gem_npc") && random(200) == 88 )
                npc_level = NPC_YL_YINSHI_INDEX;      // 較小機率出現隱士
            else if( !query("take_gem_npc") && random(100) == 88 )
                npc_level = NPC_YL_CIKE_INDEX;        // 普通機率出現刺客
            else if( random(20) == 8 )
                npc_level = NPC_ZUZHANG_INDEX;        // 較容易出現各族族長
        }
        else
            npc_level --;  // 否則為指定的減1 (傳入1時意思是數組的0號)
    }
    // 防止意外
    if( npc_level < 0 || npc_level > sizeof(npc_info2) )
    {
        npc_level = NPC_ZUREN_INDEX;  // 發現數據有誤時，強制改為族人
        delete( "job_npc" );
    }
    // 設置基本名字、ID及描述。
    info = npc_info2[ npc_level ];
    if( info["special_name"] )
    {
        set_name( info["special_name"], info[ "id" ] );
    }
    else
    {
        set_name( class_list[ npc_class ] + info["name"] + NOR, info[ "id" ] );
    }
    if( info[ "special_long"] )
    {
        set( "long", info[ "special_long"] );
    }
    else
    {
        set( "long", "這是一個"+class_list[ npc_class ]+NOR"的族民，十分好戰，可以説是兇殘成性。\n");
    }
    set("auto_kill", info[ "auto_kill" ] );
    set("peaceful", info[ "peaceful"] );
    set("del_msg", info[ "del_msg" ] );
    set("hit_busy", info[ "hit_busy" ] );
    set("hit_suck", info[ "hit_suck" ] );
    set("dead_reward_score", info[ "dead_reward_score" ] );
    set("max_busy_limit", info[ "max_busy_limit" ] );
    set( "iii", npc_class );
    set( "npc_class", npc_class );
    set( "npc_level", npc_level );

    set("hj_game/npc","kill");
    // 設置戰鬥相關的數值。
    info = npc_info[ npc_level ];
    // 如果是帶寶 npc ，並且又不是族長，那麼設置為小頭領的能力(外表看起來仍是族人、力士之類)。
    if( query("id") != "zu zhang" && query("take_gem_npc") )
        info = npc_info[ 0 ];
    set( "mepower", info[ "power" ] );
    set( "att_busy", info[ "busy" ] );
    set_temp( "hj_hp_max", info[ "hpmax" ] );
    set_temp( "hj_hp",     info[ "hpmax" ] );
    set( "attack_busy", 0 );
    set("msg","只聽得一陣響聲傳來，旁邊走過來一個面目猙獰的傢伙！\n");
    set("gender","男性");
    set("age",30+random(30));
    set("no_refresh",1);
    set("life_remain", query("delete_time_max") );
    // 非持寶者時，族長停留時間延長一倍。殺神、隱士更長。
    id = query("id");
    if( !query("take_gem_npc") )
    {
        if( id == "zu zhang" )
            set("life_remain", query("delete_time_max") * 2 );
        else if( query("dead_reward_score" ) )  // 如果是有獎勵積分的類型，則使之存活時間加長
            set("life_remain", query("delete_time_max") * 8 );  // 為了維持更久
    }
    // 強制刪除 auto kill 標記。
    if( query( "take_gem_npc" ) || id == "youling wushi" || id == "youling yinshi" )
        delete( "auto_kill" );
    remove_call_out("checking");
    remove_call_out("delete_me");
    call_out("checking", 3 );
    if( id == "youling yinshi" || id == "youling shashen" )
        hj_shout( HIM"〖幻境傳聞〗聽説"+query("name")+HIM"在幻境密林中出現了！\n"NOR );
}

void create()
{
    set("delete_time_max",300+random(180) );
    // 每個NPC出場時間最多 8 分鐘(若是玩家寶物目標，則以 fyld_npc.h 裏設置為準。
    setme( 99 );
    setup();
}

// 自毀程序
void delete_me()
{
    object ob = this_object();
    remove_call_out( "delete_me" );
    if( !objectp(ob) )
        return;
    if( !environment(ob) )
    {
        destruct(ob);
        return;
    }
    if( stringp( query("del_msg") ) )
        message_vision( query("del_msg"), ob );
    else
        message_vision( "只聽得一聲怪叫，$N「嘭」地一聲消失不見了。\n", ob);
    // 這兩個特別的 NPC 要通告一下。幽靈刺客不必通告；幽靈武士是 JOB NPC，也不必。
    if( query("id") == "youling yinshi" || query("id") == "youling shashen" )
    {
        if( query("hp") < 1 )
        {
            if( stringp(query("killme_by")) )
            {
                object who;
                who = find_player( query("killme_by") );
                if( objectp(who) && environment(who) == environment(ob) )
                    hj_shout(HIM"〖幻境傳聞〗聽説"+query("name")+HIM"被"+query("name", who)+HIM"殺死了！\n"NOR);
                else
                    hj_shout( HIM"〖幻境傳聞〗聽説"+query("name")+HIM"被殺死了！\n"NOR );
            }
        }
        else
            hj_shout( HIM"〖幻境傳聞〗聽説"+query("name")+HIM"離開了幻境密林。\n"NOR );
    }
    destruct(this_object());
}

// “心跳”檢測
void checking()
{
    object ob,*inv,temp,my_host,qxd;
    string *dirs;
    string id;
    int i, ppp;

    object target;

    if( !environment(this_object()) ) return;

    if( query("take_gem_npc") =="yes" && stringp(query("the_gem_for")) )
    {
        my_host=find_player(query("the_gem_for"));
        if( !my_host || query_temp("huanjing", my_host) != "start" || 
           query_temp("hj_hp", my_host)<1 || 
           query_temp("hj_find_ok", my_host) == "yes" )
        {
            remove_call_out("delete_me");
            call_out("delete_me",1);
            return;
        }
    }
    // 死亡時，進行獎勵。
    if( query_temp("hj_hp") < 1 )
    {
        npc_dead_reward();
        return;
    }
    // 否則時間到了，主動離開。沒有任何獎勵。
    if( query("life_remain") < 1 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1 );
        return;
    }
    ob = this_object();
    // 如果設置忙時限制，並且現在的忙時比限制的要高，那麼強制恢復
    if( (ppp=query("max_busy_limit")) > 0 && ppp < query_busy() )
    {
        start_busy( ppp );
        message_vision( "\n$N忽地使勁一掙，身體似乎恢復了自由！\n\n", ob );
    }
    // 本NPC仍在生，下面開始進入攻擊程序。
    // 攻擊等待時間仍未到，或偶爾得到小几率的隨機數，跳過。
    addn("attack_busy", -1 );
    if( query("attack_busy") < 0 )
        set("attack_busy", 0 );
    if( query("attack_busy") || !random(8) )
    {
        addn("life_remain", -1 );
        remove_call_out("checking");
        call_out("checking",1 );
        return;
    }
    // 好，開始攻擊
    // 如果有 killme_by 標記，即攻擊該人
    id = query("id");
    if( query("killme_by") )
    {
        target = present( query("killme_by"), environment(ob) );
        // 目標不在本地了，進入空閒狀態
        if(!target)
        {
            delete("killme_by");
            delete("start_kill_msg");
            set_leader( 0 );  // 停止跟隨
        }
        // 目標存在本地，打！
        else 
        {
            // 如果其不攜帶神人令以及臨時離開器，立刻實行跟隨，並且開打！
            if( !present("shenren ling",target) && !present( "hj temp leave obj", target ) )
            {
                set_leader( target );
                // 如果是第一輪開打，來個通知
                if( !query("start_kill_msg") )
                {
                    set("start_kill_msg", 1);
                    message_vision( HIR"\n看來$n"HIR"想要殺死$N"HIR"！\n\n"NOR, target, this_object() );
                }
                // 設置攻擊等待時間
                set("attack_busy", query("att_busy") );
                // 調用攻擊函數。
                call_out( "att_target",1, target );
            }
        }
    }
    // 否則，可能進行主動攻擊。
    else if( query("auto_kill") )   // 看此 npc 是否會自動 kill
    {
        inv = all_inventory(environment(ob));
        ppp = query( "peaceful" );
        if( ppp < 2 )
            ppp = 2;
        // 逐個過濾
        for( i=sizeof(inv)-1; i>=0; i-- )
        {
            if( random(ppp) )  // 和平度高的就不理這個東西(不管它是不是能打的東西)
                continue;
            // 對其執行判定，準備開打
            temp = inv[i];
            if( !temp->is_character()
               || query("hj_game/npc", temp )
               || query_temp("hj_hp", temp)<1
               || query_temp("huanjing", temp) != "start"
            )
                continue;
            // 無燈者不打（打了也白打）
            if(!(qxd = present("qixing deng",temp)) )
                continue;
            // 攜帶神人令、或攜帶臨時離開器(臨時離開遊戲)者，不會被攻擊。
            if( present("shenren ling",temp) || present( "hj temp leave obj", temp ) )
                continue;
            // 還有4個以上的燈亮着時，族長不會主動進行攻擊。
            if( id == "zu zhang" && query("last_deng", qxd)>4 )
                continue;
            // 還有6個以上的燈亮着時，小頭領不會主動進行攻擊。
            if( id == "tou ling" && query("last_deng", qxd)>6 )
                continue;
            // 那麼，開始攻擊目標！
            set_leader( temp );
            set("killme_by",query("id", temp));
            message_vision( HIR"\n看來$n"HIR"想要殺死$N"HIR"！\n\n"NOR,
                    temp, this_object() );
            set("start_kill_msg", 1);
            set("attack_busy", query("att_busy") );
            call_out("att_target",1, temp );
            break;
            // 測試用，請小心    tell_object(find_player("naihe"),"抽不中 kill "+temp->query("id")+" .\n");
        }
    }
    i = 0;  // 作為是否 random_move 的標記
    // 幽靈武士、或者帶有特殊獎勵的NPC，不要到處亂走
    if( id == "youling wushi" || query( "dead_reward_score" ) )
    {
        if( !random(50) )
            i = 1;
    }
    else if( !random(5) )
        i = 1;
    if( i && !is_busy() && !query("killme_by") && living(this_object()) && query_temp("hj_hp") > 0 )
    {
        dirs=({ "east","west","south","north","northeast",
            "northwest","southeast","southwest" });
        command( "go "+ dirs[random(sizeof(dirs))] );
    }
    addn("life_remain", -1 );
    remove_call_out("checking");
    call_out("checking",1 );
}

void att_target( object target )
{
    object temp;
    string temp_msg,color_name, id;
    int power = query("mepower") * 4 / 5 + random( query("mepower") / 5 ) + 1;

    if( is_busy() || query_temp("hj_hp") < 1 )
        return;
    if( !target
      || !environment(target)
      || environment(target) != environment( this_object() )
       || query_temp("hj_hp", target)<1 )
    {
        delete("killme_by");
        delete("start_kill_msg");
        set_leader( 0 );  // 停止跟隨
        return;
    }
    switch( random(12) )
    {
    case 0 .. 3 : temp_msg=NOR+CYN"狠狠地揮出一拳，把$N"NOR+CYN"打個正中！";break;
    case 4 .. 7 : temp_msg=NOR+CYN"狠狠地踢出一腳，$N"NOR+CYN"躲閃不及，吃個正着！"; break;

    case 8: temp_msg=NOR+CYN"口中「嗬嗬」怪叫，雙手亂揮，卻也讓$N"NOR+CYN"中了招！";
        power -= ( power /3 ); break;
    case 9:    temp_msg=NOR+CYN"手腳亂揮，完全不成章法，卻也讓$N"NOR+CYN"中了招！";
        power -= ( power /3 ); break;
    case 10:temp_msg=NOR+CYN"使盡了力氣向着$N"NOR+CYN"一撞，把$N"NOR+CYN"撞得飛了開去！";
        power += ( power / 2 ); break;
    case 11: temp_msg=NOR+CYN"向着$N"NOR+CYN"一抓！$N"NOR+CYN"閃身躲過，只受了點輕傷。";
        power = power / 5 + random( power / 5 );
        if( power < 1 ) power = 1;
        break;
    }
    // 法師攻擊的描述亦不相同。
    if( (id=query("id")) == "fa shi" )
    {
        power = query("mepower") * 4 / 5 + random( query("mepower") / 5 ) + 1;
        message_vision( sprintf( HIY"\n$n"HIY"對着$N"HIY"指手劃腳地施着法，$N"HIY
            + "竟覺全身氣息傾泄而出！結果造成 "HIR"%d"HIY" 點的傷害。\n"NOR, power ),
            target, this_object()
        );
    }
    else
        message_vision( sprintf( CYN"\n$n%s"NOR+CYN"結果造成 "HIR"%d"NOR+CYN" 點的傷害。\n"NOR,
            temp_msg, power), target, this_object()
        );
    addn_temp("hj_hp", -power, target);
    // 幽靈族會讓對方增加忙時！！！
    if( query( "hit_busy" ) )
    {
        // 奪魂之技特殊技能體現之一，有效抵抗來自NPC的奪魂類攻擊的忙時效果
        if( !query_temp("hj_special/sh", target) && target->query_busy()<3 && !random(5) )
        {
            target->start_busy( target->query_busy() + 5 );
            message_vision( HIB"$N"HIB"只覺得一陣麻木之感如電般傳遍全身，頓時動彈不得！\n"NOR, target );
        }
    }
    // 各族的法師會吸取對方的 hp.
    if( query( "hit_suck" ) )
    {
        if( !random(2) && query_temp("hj_hp") < (query_temp("hj_hp_max") *9 / 10 ) )
        {
            message_vision( "只見$n大吸了一口從$N身上所泄漏的真氣！$n的氣息恢復了許多。\n", target, this_object() );
            addn_temp("hj_hp", power * 2 + random( power * 2 ) );
        }
    }
    // 取消怪物攻擊時減少分數的設置
    //    target->addn_temp("hj_score",-random(power/3) );
    //    if( target->query_temp("hj_score") < 1 )
    //    target->set_temp("hj_score", 1);
    color_name=get_health_desc(query_temp("hj_hp", target),query_temp("hj_hp_max", target));
    message_vision(NOR"（ $N"+color_name+""NOR" ）\n"NOR,target);
}

void hj_get_attack( object ob )
{
    if( !objectp(ob) || !query("dead_reward_score") )
        return;
    addn("hj_att/"+query("id", ob),1);
}

// =================================================================
// ========================== NPC 死亡獎勵 =========================
// =================================================================
void npc_dead_reward()
{
    string id = query("id");
    object temp, me, ob = this_object();

    // 本物件無 env 或 hp 還有(錯誤的調用), 無任何獎勵。
    if( !environment(ob) || query_temp("hj_hp") > 0 )
    {
        destruct( ob );
        return;
    }
    // 給一點點小的概率，讓NPC可能額外的攜帶寶物。
    if( random(200) == 88 )
        set("take_gem_npc", "yes" );
    // 如果是持寶NPC，絕對掉下寶物。
    if( query("take_gem_npc") =="yes" )
    {
        temp = new(__DIR__"hj_obj_gem");
        temp -> setme( query("npc_class") );    // 如果 class 超出允許範圍，則會隨機設置寶物
    }
    // 否則如果是族長，掉下本族的權杖。加入隨機數，否則JOB變得相當的容易了。
    else if( id == "zu zhang" && random(3) )
    {
        temp = new( __DIR__"hj_obj_gem_qz" );
        temp -> setme( query("npc_class") );    // 如果 class 超出允許範圍，則會隨機設置權杖
    }
    // 否則如果不是幽靈武士、並且不是有特殊獎勵的，就有機會掉下技能石或果品或購物寶石。
    else if( !random(3) && id != "youling wushi" && !query("dead_reward_score") )
    {
        if( random(3) )
            temp = new( __DIR__"hj_obj_other" );
        else if( random(2) )
            temp = new( __DIR__"hj_obj_quest" );
        if( temp )
            temp->setme(99);
    }
    if( temp )
    {
        message_vision("$N身上突然掉下一"+query("unit", temp)+"$n！\n",ob,temp);
        temp->move(environment(ob));
    }
    // 進行特殊的獎勵。幽靈武士是任務NPC，特別獎勵
    if( id == "youling wushi" )
        npc_dead_reward_wushi();
    // 否則，如果有“獎勵積分”的設置，則使用預定的方式獎勵積分。
    else if( query("dead_reward_score") )
        npc_dead_reward_sp( query("dead_reward_score") );
    // 給殺死本NPC的玩家加個記錄
    if( stringp( query( "killme_by" ) ) )
    {
        me = find_player( query("killme_by") );
        if( objectp( me ) )
            addn("huanjing2003/kill_npc", 1, me);
    }
    remove_call_out("delete_me");
    call_out("delete_me",1 );
}
// =================================================================    


// 幽靈武士死亡後給予獎勵。
// (1) query("job_master_obj")  object 型，JOB是屬於此人的
// (2) query("job_award_score") int 型，獎勵的得分
// (3) query("job_award_skills") int 型，獎勵的技能
// query("killme_by")  最後一擊
void npc_dead_reward_wushi()
{
    object me, ob = this_object();
    mapping sks;
    string *sks_list;
    string sks_id;

    if( query("id") != "youling wushi" )
        return;
    me = query("job_master_obj");
    if( !objectp(me)
       || query("killme_by") != query("id", me )
       || query_temp("huanjing", me) != "start"
       || query_temp("hj_hp", me)<1
      || !environment(me)
      || environment(me) != environment(ob)
    )
        return;

    // 所有條件OK，開始獎勵玩家
    message_vision(CYN"$N"NOR+CYN"消滅了被自己放出來的幽靈族武士，心中大慰。\n"NOR, me);
    // 先獎勵得分
    addn_temp("hj_score", query("job_award_score"), me);
    tell_object( me, HIR"遊戲提示：你的得分增加了 "+ query("job_award_score")+ " 點！\n"NOR);
    // 再獎勵技能，如果有的話
    if( query("job_award_skills") )
    {
        sks=query_temp("hj_game_skills", me);
        if( sizeof( sks ) )
        {
            sks_list = keys( sks );
            // 獲取了隨機的技能 ID
            sks_id = sks_list[ random(sizeof(sks_list)) ];
            // 還得數據無誤才行
            if( query_temp("hj_game_damages/"+sks_id, me) )
            {
                addn_temp("hj_game_damages/"+sks_id, query("job_award_skills"), me);
                tell_object( me, sprintf( HIR"遊戲提示：你的「%s」提升了 %d 級！\n"NOR,
                    query_temp("hj_game_skills/"+sks_id, me),
                    query("job_award_skills"))
                );
                if( query_temp("hj_game_damages/"+sks_id, me)>99 )
                {
                    set_temp("hj_game_damages/"+sks_id, 99, me);
                    tell_object( me, HIR"該技能已經達到上限了。\n"NOR );
                }
            }
        }
    }
    // 如果有力量獎勵的話
    if( query("job_award_power") > 0 )
    {
        addn_temp("hj_game_mepower", query("job_award_power"), me);
        tell_object( me, sprintf( HIR"遊戲提示：你的力量增強了 %d 點！\n"NOR,
            query("job_award_power"))
        );
    }
    // End.
}
// =================================================================


// 特殊的獎勵。主要是給 youling shashen 或 youling yinshi 或 youling cike 使用。
void npc_dead_reward_sp( int total_reward )
{
    mixed ls;
    string id, *key;
    object usr, ob = this_object();
    int total_hit, percent, reward;

    if( total_reward < 100 )
        total_reward = 100;
    if( total_reward > 10000 )
        total_reward = 10000;
    if ( !query("dead_reward_score") )
        return;
    if( !mapp( (ls=query("hj_att")) ) || !sizeof(ls) )
        return;
    key = keys( ls );
    foreach( id in key )
    {
        total_hit += ls[ id ];
    }
    if( total_hit < 1 )
        return;
    foreach( id in key )
    {
        usr = find_player( id );
        if( !objectp(usr)
           || query_temp("huanjing", usr) != "start"
           || query_temp("hj_hp", usr)<1
          || !environment(usr)
           || !query("room_mark", environment(usr) )
        )
            continue;
        tell_object( usr, HIG"\n你" + (ls[id] >= total_hit ? "獨" : "合眾人之")
            + "力殺死了"+query("name")+HIG"，感到自身修為大有長進。\n"NOR );
        percent = ls[id] * 100 / total_hit;
        reward = total_reward / 100 * percent;
        // 不在同一地方時，得分減半。
        if( environment(usr) != environment(ob) )
            reward /= 2;
        if( reward < 1 )
            reward = 1;
        tell_object( usr, HIR"遊戲提示：你的得分增加了 "+reward+" 點！\n"NOR);
        addn_temp("hj_score", reward, usr);
        if( query("killme_by") == query("id", usr) )
        {
            tell_object( usr, HIG"殺死"+query("name")+HIG"的最後一擊是你造成的！你得到了更多的獎勵。\n"NOR );
            reward = total_reward / 10;
            tell_object( usr, HIR"遊戲提示：你的得分增加了 "+reward+" 點！\n"NOR);
            addn_temp("hj_score", reward, usr);
        }
    }
    // End.
}
// =================================================================
// =================================================================
// =================================================================
