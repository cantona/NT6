//Created by RoomEditer on 02-1-3.
//by bravo
// naihe 05-12-3 0:22 完全重寫(只是沿原來的文件名及地理位置而已)，添加賭大小功能，使之成為真正賭場。
// naihe 05-12-3 17:01 調整豹子賠率，增加數據存取功能及更詳細的分析 log.
// 由于 sz /d/ 下文件沒有 save_object() 權，故更改此文件為 /clone/room/changan_dufang.c
// naihe 05-12-6 8:41 加上彩金功能。
// naihe 05-12-14 16:42 最終完善。
// naihe 05-12-18 10:15 降低手續費用由百分率改為千分率，可選擇余地更多。

#include <ansi.h>
inherit ROOM;
inherit F_SAVE;
#include <ctime_format_func.h>    // 某些MUD裡沒有這個函數：ctime_format()，把它寫成：return ctime(time()); 即可。
//#include <set_del_color_func.h> // 某些MUD裡沒有這兩個 s_efun:  setcolor(), delcolor().

#define     DUFANG_VERSION                  "V1.2 (2005.12.18)"

// ----------------- defines -----------------------
#define     DUFANG_LOG_FILE                 "duchang/changan_dufang"     // log dir 下。
#define     LOG_ON          1               // 開啟時則進行 log_file() 操作。主要是記錄 mewiz 操作記錄。
#define     DUFANG_SAVE_FILE    DATA_DIR +  "duchang/changan_dufang"
#define     SAVE_ON         1               // 開啟時則進行 save_object() 操作。
                                            // 本文件數據記錄位置
#define     SYSTEM_WIZ_ID   "$lonely$"       // 允許使用 <mewiz reward 數字> 指令給系統加入獎金。
#define     SYSTEM_EAT_P    3               // 系統吃錢設置是否開啟。這是一個千分率。
                                            // 非零時，每局都要“吃掉”一定的押注額，不計入返還記錄中。
#define     WAIT_TIME       20              // 押注後等待開局的時間(等待多人押注)
#define     GOGO_WAIT_TIME  3               // 準備開局後要等待幾秒才能用 gogo 加速開獎。
#define     DEF_PERCENT     95              // 正常時的默認賠率，這是贏的部分。如 bet 100 即純賺 100*DEF_PERCENT/100
#define     BAOZI_PERCENT   3000            // 豹子的固定賠率。規則同上。
#define     ADD_PERCENT     2               // 當大、小、單、雙連續開出時，連續開出的項其賠率會上漲。這是幅度。
#define     LOST_PERCENT    2               // 同上，隔得越久未開的項其賠率會下跌，這是幅度。
#define     MAX_DF_PLAYER   10              // 最多 10 位玩家同時投注。 定義為 0 時不限制。

//    #######  彩金方面的設置 #######
#define     JACKPOT_ON      1               // 是否開啟彩金獎勵。 0 不開啟。
#define     JACKPOT_RANDOM  5               // 如果 !random(這個數) 並符合條件(贏入足夠的錢)的話就會開啟彩金
#define     JACKPOT_LIMIT   20000           // 彩金限制，系統要贏入多少金才會開啟彩金。不過，也可能以較低概率開啟彩金。
#define     JACKPOT_MAX     2000            // 彩金最多
#define     JACKPOT_MIN     200             // 彩金最少
//    ###############################

#define     BIG_STR         HIG"大"NOR      // 可以在這裡改一下顏色。只是描述而已。
#define     SMALL_STR       HIC"小"NOR
#define     SINGLE_STR      HIY"單"NOR
#define     DOUBLE_STR      HIM"雙"NOR
#define     BAOZI_STR       HIR"豹子"NOR

// ---------------- game vars (save) ----------------
int times_flag = 1;
int BetOn = 1;                              // 允許押注
mapping game_info = ([
    "comp_da"       : 0,
    "comp_xiao"     : 0,
    "comp_dan"      : 0,
    "comp_shuang"   : 0,
    "percent_da"    : DEF_PERCENT,
    "percent_xiao"  : DEF_PERCENT,
    "percent_dan"   : DEF_PERCENT,
    "percent_shuang": DEF_PERCENT,
    "percent_baozi" : BAOZI_PERCENT,        // 可以押豹子，固定賠率。
    "last_msg_dx"   : "",
    "last_msg_ds"   : "",
]);
mapping log_info = ([
    "total_bet" : 0,
    "total_pay" : 0,
    "total_bet_g" : 0,
    "total_pay_g" : 0,
    "system_reward_g": 0,   // 系統額外獎勵的，由 mewiz 指令及特定巫師設置。
    "system_eat"  : 0,      // 系統吃掉的……
    "system_eat_g": 0,
]);
// ---------------- game vars (no save) --------------
nosave int GameStat = 0;
nosave int valid_gogo_time;
nosave int this_bet = 0;
nosave int jackpot = 0;
nosave int jp_num = 0;
nosave int jp_bingo = 0;
nosave int t1;
nosave int t2;
nosave int t3;
nosave int total;
nosave mapping type_str = ([
    "da"        :       BIG_STR,
    "xiao"      :       SMALL_STR,
    "dan"       :       SINGLE_STR,
    "shuang"    :       DOUBLE_STR,
    "baozi"     :       BAOZI_STR,
]);
nosave mapping type_opp = ([
    "da"        :       "xiao",
    "xiao"      :       "da",
    "dan"       :       "shuang",
    "shuang"    :       "dan",
    "baozi"     :       "baozi",
]);
nosave mapping bet_info = ([ ]);
nosave mapping bet_info_jp = ([ ]);
nosave string *df_player = ({ });
// -------------- function list -----------------------
        int     query_system_win    ();
        string  system_info_msg     ();
        string  look_bugao          ();
        string  query_now_long      ();
        string  query_now_long2     ();

        string  check_beted_str     ( string id );
protected int     do_chk              ( string arg );
protected int     do_bet              ( string arg );
protected int     do_mewiz            ( string arg );
protected int     do_gogo             ();
protected void    finish_bingo_check  ();
protected void    new_game            ();
protected void    game_start          ( int stat );
protected string  check_percent_str   ();
// ----------------------------------------------------


// ####################################################
// #################  以下開始正式部分 ################
// ####################################################
// 保持房間不被系統 clean_up()
void reset()
{
    ::reset();
    set("no_clean_up", 1 );
}

// 存儲文件位置
string query_save_file()
{
    if( !SAVE_ON )
        return 0;
    return DUFANG_SAVE_FILE;
}

// 獲得 id 的押注表的字串
string check_beted_str( string id )
{
    string msg;
    msg = "";
    if( bet_info[ id + "-baozi" ] )
        msg += "本局押  "+BAOZI_STR+"：" + bet_info[ id + "-baozi" ] + "\n";
    if( bet_info[ id + "-da" ] )
        msg += "本局押  "+BIG_STR+"：" + bet_info[ id + "-da" ] + "\n";
    if( bet_info[ id + "-xiao" ] )
        msg += "本局押  "+SMALL_STR+"：" + bet_info[ id + "-xiao" ] + "\n";
    if( bet_info[ id + "-dan" ] )
        msg += "本局押  "+SINGLE_STR+"：" + bet_info[ id + "-dan" ] + "\n";
    if( bet_info[ id + "-shuang" ] )
        msg += "本局押  "+DOUBLE_STR+"：" + bet_info[ id + "-shuang" ] + "\n";
    if( msg != "" )
        msg = "以下是本局 "+id+" 的押注：\n" + msg;
    return msg;
}

// 支付獎金等。
protected void finish_bingo_check()
{
    object *inv, ob;
    string id;
    int bet, bingo;

    inv = all_inventory( this_object() );
    if( !sizeof( inv ) )
        return;
    if( jp_bingo && jackpot > 0 )
    {
        tell_room( this_object(), BLINK+HIM"中了幸運獎金！！！本局幸運獎金每位最高派彩 "+jackpot+" (coin)，有押注押中的玩家都能獲得紅利！\n"NOR);
    }
    foreach( ob in inv )
    {
        if( !userp(ob) || !living(ob) )
            continue;
        id = ob->query("id");
        if( (bet=bet_info[ id + "-" + game_info["opened1"]]) > 0 )     // 押大小中了(或豹子中了)。
        {
            bet *= 100;     // 轉成 coin
            // 防止溢出，低賠率時直接計算，高賠率時先除後乘。
            if( game_info["percent_"+game_info["opened1"]] <= 500 )
                bingo = bet + (bet * game_info[ "percent_" + game_info[ "opened1"] ] / 100);    // 計算應得獎金
            else
                bingo = bet + (bet / 100 * game_info[ "percent_" + game_info[ "opened1"] ]);
            ob->add( "balance", bingo );        // 支付
            log_info[ "total_pay" ] += bingo;   // 記錄
            message_vision( "$N押下 "+(bet/100)+" 兩白銀買 "+type_str[game_info["opened1"]]+" ，獲得獎金"
                +MONEY_D->money_str( bingo-bet )+"(錢莊自動轉帳，本金同時返還)。\n", ob );      // 報告
            if( undefinedp( bet_info_jp[id] ) )
                bet_info_jp[ id ] = bet/100;    // 轉回 silver
            else
                bet_info_jp[ id ] += bet/100;    // 轉回 silver
        }
        if( (bet=bet_info[ id + "-" + game_info["opened2"]]) > 0 )     // 押單雙中了。
        {
            bet *= 100;     // 轉成 coin
            // 防止溢出，低賠率時直接計算，高賠率時先除後乘。
            if( game_info["percent_"+game_info["opened2"]] < 300 )
                bingo = bet + (bet * game_info[ "percent_" + game_info[ "opened2"] ] / 100);    // 計算應得獎金
            else
                bingo = bet + (bet / 100 * game_info[ "percent_" + game_info[ "opened2"] ]);
            ob->add( "balance", bingo );        // 支付
            log_info[ "total_pay" ] += bingo;   // 記錄
            message_vision( "$N押下 "+(bet/100)+" 兩白銀買 "+type_str[game_info["opened2"]]+" ，獲得獎金"
                +MONEY_D->money_str( bingo-bet )+"(錢莊自動轉帳，本金同時返還)。\n", ob );      // 報告
            if( undefinedp( bet_info_jp[id] ) )
                bet_info_jp[ id ] = bet/100;    // 轉回 silver
            else
                bet_info_jp[ id ] += bet/100;    // 轉回 silver
        }
    }
    // 統計彩金問題
    if( jp_bingo && jackpot > 0 )
    {
        if( !sizeof( bet_info_jp ) )
        {
            tell_room( this_object(), HIM"不過很可惜，本局遊戲無人押中，彩金無人獲得！\n"NOR );
        }
        else
        {
            string *key, t;
            int percent;
            key = keys( bet_info_jp );
            foreach( t in key )
            {
                if( !(ob = find_player(t)) || environment(ob) != this_object() )
                    continue;
                bet = bet_info_jp[ t ];             // 該玩家總 bet 中數量
                if( bet > 5000 )                   // 總量 5000 以上可以得到全額獎金
                    percent = 100;
                else
                    percent = bet * 100 / 5000;
                if( percent < 1 )
                    percent = 1;                    // 得出百分比
                bingo = jackpot / 100 * percent;    // 最終獎金(coin)
                message_vision( HIY"          $N"HIY"獲得了 "+HIR+percent+"%"HIY" 的彩金："
                    +MONEY_D->money_str( bingo )+"！\n"NOR, ob);
                ob->add( "balance", bingo );        // 支付
                log_info[ "total_pay" ] += bingo;   // 記錄
            }
        }
    }
    // 將 log 記錄換成 gold 單位以防止溢出的問題。
    if( log_info["total_bet"] >= 10000 )
    {
        log_info["total_bet_g"] += log_info["total_bet"] / 10000;
        log_info["total_bet"] %= 10000;
    }
    if( log_info["total_pay"] >= 10000 )
    {
        log_info["total_pay_g"] += log_info["total_pay"] / 10000;
        log_info["total_pay"] %= 10000;
    }
}

// 獲得系統現在贏錢的數量
int query_system_win()
{
    return log_info["system_reward_g"]
        + (log_info["total_bet_g"] - log_info["total_pay_g"] - log_info["system_eat_g"]);
}

protected void new_game()
{
    times_flag ++;
    GameStat = 0;
    bet_info = ([ ]);
    bet_info_jp = ([ ]);
    df_player = ({ });
    jackpot = 0;
    // 本局總押注額要抽一部分作系統吃掉的。
    if( SYSTEM_EAT_P > 0 )
    {
        int tmp;
        tmp = this_bet / 1000 * SYSTEM_EAT_P;       // 這是一個千分率。
        if( tmp < 1 )
            tmp = 1;
        log_info["system_eat"] += tmp;
        if( log_info["system_eat"] >= 10000 )
        {
            log_info["system_eat_g"] += log_info["system_eat"] / 10000;
            log_info["system_eat"] %= 10000;
        }
    }
    this_bet = 0;
    tell_room( this_object(), query_now_long2() );
    set( "long", query_now_long() );
    save();
}
string random_color()
{
    return ({ HIR, HIM, HIB, HIC, HIG, })[ random(5) ];
}
protected void game_start( int stat )
{
    remove_call_out( "game_start" );
    GameStat = 2;
    if( !stat )
    {
        int win = query_system_win();
        int t = 1;
        tell_room( this_object(), HIW"第 "+times_flag+" 局賭局開寶，買定離手！\n"NOR );
        // 系統贏了一定數量，就會開啟彩金獎勵。或者會以較低概率開啟小獎彩金。
        if( (JACKPOT_ON && !random( JACKPOT_RANDOM ) && win > JACKPOT_LIMIT)
         || (JACKPOT_ON && !random(JACKPOT_RANDOM*10))
        )
        {
            jp_bingo = 0;
            // 彩金額是 win 額的 1/20
            jackpot = 1 + random( win/20 );
            // 最多
            if( jackpot > JACKPOT_MAX )
                jackpot = JACKPOT_MAX - random(JACKPOT_MAX/20);
            // 最少
            if( jackpot < JACKPOT_MIN )
                jackpot = JACKPOT_MIN + random(JACKPOT_MIN/20);
            jackpot *= 10000;       // 換成 coin
            if( win > JACKPOT_LIMIT*3 )
                jp_num = 6 + random( 10 );      // 這個相對容易中一些。
            else
                jp_num = 3 + random(16);
            tell_room( this_object(),
                sprintf( "\n                 %s★%s☆%s★ %s幸%s運  "HIY"%d  %s彩%s金 %s★%s☆%s★\n"
                    +HIW"         本局若開出 "HIR"%d"HIW" 點，則所有買中的玩家都有機會獲得獎金！\n\n"NOR,
                        random_color(), random_color(), random_color(),
                        random_color(), random_color(),
                        jackpot,
                        random_color(), random_color(),
                        random_color(), random_color(), random_color(),
                        jp_num,
                )
            );
            t = 5;
        }
        call_out( "game_start", t, 1 );     // t 秒後繼續
        return;
    }
    if( stat == 1 )
    {
        string msg;
        t1 = 1 + random( 6 );
        t2 = 1 + random( 6 );
        t3 = 1 + random( 6 );
        total = t1 + t2 + t3;
        msg = "第 "+times_flag+" 局賭局開出："
            + chinese_number( t1 ) + "、"
            + chinese_number( t2 ) + "、"
            + chinese_number( t3 ) + "，";
        if( t1 == t2 && t1 == t3 )
        {
            msg += BAOZI_STR+ HIW"，通吃“大小單雙”！";
            game_info[ "opened1" ] = "baozi";       // 設置一個就行
            game_info[ "opened2" ] = "-----";       //
        }
        else
        {
            msg += chinese_number( total )+"點  "
                + (total < 11 ? SMALL_STR : BIG_STR) + HIW "  "
                +"，報  "+(total % 2 ? SINGLE_STR : DOUBLE_STR )+ HIW"  數！";
            if( total < 11 )
                game_info[ "opened1" ] = "xiao";
            else
                game_info[ "opened1" ] = "da";
            if( total % 2 )
                game_info[ "opened2" ] = "dan";
            else
                game_info[ "opened2" ] = "shuang";
        }
        tell_room( this_object(), HIW"\n" + msg + "\n\n"NOR );
        game_info[ "last_opened_msg" ] = msg;   // 把信息記錄下來。
        call_out( "game_start", 1, 2 );         // 1秒後繼續
        return;
    }
    else
    {
        if( total == jp_num )
            jp_bingo = 1;
        finish_bingo_check();      // 支付獎金。

        // 計算新的賠率。如果是豹子，則保持賠率。
        if( game_info[ "opened1" ] != "baozi" )
        {
            // 大小連開(或者連續通殺)
            if( game_info[ "last_opened1" ] == game_info[ "opened1" ] )
            {
                game_info[ "percent_" + game_info[ "opened1" ] ] += ADD_PERCENT;
                game_info[ "percent_" + type_opp[game_info[ "opened1" ]] ] -= LOST_PERCENT;
                game_info[ "comp_" + game_info[ "opened1" ] ] ++;
                game_info[ "comp_" +  type_opp[game_info[ "opened1" ]] ] = 0;
            }
            else        // 否則恢復。
            {
                game_info[ "percent_da" ] = DEF_PERCENT;
                game_info[ "percent_xiao" ] = DEF_PERCENT;
                game_info[ "comp_" + game_info[ "opened1" ] ] = 1;
                game_info[ "comp_" + type_opp[game_info[ "opened1" ]] ] = 0;

            }
            // 單雙連開
            if( game_info[ "last_opened2" ] == game_info[ "opened2" ] )
            {
                game_info[ "percent_" + game_info[ "opened2" ] ] += ADD_PERCENT;
                game_info[ "percent_" + type_opp[game_info[ "opened2" ]] ] -= LOST_PERCENT;
                game_info[ "comp_" + game_info[ "opened2" ] ] ++;
                game_info[ "comp_" + type_opp[game_info[ "opened2" ]] ] = 0;
            }
            else
            {
                game_info[ "percent_dan" ] = DEF_PERCENT;
                game_info[ "percent_shuang" ] = DEF_PERCENT;
                game_info[ "comp_" + game_info[ "opened2" ] ] = 1;
                game_info[ "comp_" + type_opp[game_info[ "opened2" ]] ] = 0;
            }
            game_info[ "last_opened1" ] = game_info[ "opened1" ];
            game_info[ "last_opened2" ] = game_info[ "opened2" ];
            // 記錄上盤的信息。
        }
        // 記錄總共開的次數。
        if( !game_info[ "total_opened_" + game_info[ "opened1" ]]  )
            game_info["total_opened_" + game_info[ "opened1" ]] = 1;
        else
            game_info["total_opened_" + game_info[ "opened1" ]] ++;
        if( !game_info[ "total_opened_" + game_info[ "opened2" ]]  )
            game_info["total_opened_" + game_info[ "opened2" ]] = 1;
        else
            game_info["total_opened_" + game_info[ "opened2" ]] ++;
        if( 1 )     // 搞走勢圖
        {
            string t;
            // dx
            if( game_info["opened1"] == "baozi" )
                t = "* ";
            if( game_info["opened1"] == "da" )
                t = "- ";
            else if( game_info["opened1"] == "xiao" )
                t = "_ ";
            else
                t = "* ";
            if( strlen(game_info["last_msg_dx"]) >= 20 )
                game_info["last_msg_dx"] = game_info["last_msg_dx"][2..19];
            game_info["last_msg_dx"] += t;
            // ds
            if( game_info["opened2"] == "baozi" )
                t = "* ";
            if( game_info["opened2"] == "dan" )
                t = "- ";
            else if( game_info["opened2"] == "shuang" )
                t = "_ ";
            else
                t = "* ";
            if( strlen(game_info["last_msg_ds"]) >= 20 )
                game_info["last_msg_ds"] = game_info["last_msg_ds"][2..19];
            game_info["last_msg_ds"] += t;
        }
        new_game();
    }
}

void create()
{
    restore();
    set("short","賭坊");
    //set("long", (: query_now_long :) );  yh lib 不支持這樣 set long. 為了兼容，統一更改。
    set( "long", query_now_long() );       // 每局遊戲結束後還要額外 set 一次，以改變 long().
    set("exits",([
        "east" : "/d/city/tree2",
    ]));
    set("item_desc", ([
        "bugao" : (: look_bugao :),
    ]));
    if( file_size( __DIR__"cadf_huoji.c" ) > 1 )
    {
        set( "objects", ([
            __DIR__"cadf_huoji" : 1,
        ]));
    }
    set("no_fight", 1 );
    set("no_steal", 1 );
    set("no_sleep_room", 1 );

    set("show_dir", "changan" );
    set("show_map_use", "changan2" );
    setup();
}

string query_now_long2()
{
    string msg = "";
    if( !BetOn )
        msg += HIR"                         【賭坊暫停營業】\n\n"NOR;
    if( game_info[ "last_opened_msg" ] )
        msg += BBLU + HIW"  上局：" + filter_color(game_info[ "last_opened_msg" ]) + "  \n"NOR;
    else
        msg += BBLU + HIW"  上局：                                                            \n"NOR;
    msg += "      "BCYN + HIW" A  目前賠率：    [大]  連開 "+game_info[ "comp_da" ]+" 局  賠率 "+(100+game_info[ "percent_da" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" B  目前賠率：    [小]  連開 "+game_info[ "comp_xiao" ]+" 局  賠率 "+(100+game_info[ "percent_xiao" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" C  目前賠率：    [單]  連開 "+game_info[ "comp_dan" ]+" 局  賠率 "+(100+game_info[ "percent_dan" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" D  目前賠率：    [雙]  連開 "+game_info[ "comp_shuang" ]+" 局  賠率 "+(100+game_info[ "percent_shuang" ])+"%    \n"NOR;
    msg += BBLU+HIW"  大小：[ " + sprintf( "%-20s",game_info["last_msg_dx"]) + "]      單雙：[ "+sprintf( "%-20s",game_info["last_msg_ds"])+"]  \n"NOR;
    msg += check_percent_str();
    return msg + "\n";
}

string query_now_long()
{
    string msg;

    msg ="這裡是王者歸來的一家小賭坊，別看它規模不大，卻常常有許多千金富豪
來這裡徹夜豪賭。對門的牆上帖著一張布告(bugao)。\n\n";
    msg += query_now_long2();
    return msg;
}

string look_bugao()
{
    object me = this_player();
    string msg;
    msg =
"**********************************************************
    賭坊遊戲說明  "HIC+DUFANG_VERSION"  Naihe@神州 MUD"NOR"

    本賭坊直接使用錢莊轉帳付款，設骰子賭局。

    三顆骰子，押注後 "+WAIT_TIME+" 秒開獎，押中即獎。
    可以押“大”、“小”、“單”、“雙”、“豹子”共五項。

    4,6,8,10,12,14,16 為雙，5,7,9,11,13,15,17 為單。
    4-10 為小，11-17 為大。
    三顆骰子都一樣時為“豹子”，通吃大小單雙──但賠出押
    中豹子的注金，賠率為固定的 "+(game_info["percent_baozi"]+100)+"%。

    其它賠率每局另報，投注范圍 1 - 10000 兩"HIW"白銀"NOR"。

    "HIY"押注：   <bet 數量 to da|xiao|dan|shuang|baozi>"NOR"
             你也可以用  a|b|c|d|e  來簡化輸入上面的類型。
    查看：   <chk ID>
    即開：   <gogo>

    加入 "HIW"隨機彩金"NOR" 設置！
    每位玩家一次可能獲得 "+JACKPOT_MIN+" - "+JACKPOT_MAX+" 黃金！
**********************************************************\n";
    if( wizardp(me) )
        msg += "你是巫師，可以使用 <mewiz> 指令進行一些設置。\n";
    return msg;
}
void init()
{
    add_action( "do_bet", "bet" );
    add_action( "do_chk", "chk" );
    add_action( "do_gogo", "gogo" );
    if( wizardp(this_player()) )
        add_action( "do_mewiz", "mewiz" );
}

string system_info_msg()
{
    int t = query_system_win();
    return sprintf(
        "(系統現在 %s )  總收入：%d (額外獎勵：%d)  總支出：%d (手續消耗：%d)  盈余：%s%d"NOR"  ("HIY"黃金"NOR")\n",
        (BetOn ? HIG"開放中"NOR : HIR"關閉中"NOR),
        log_info["total_bet_g"],
        log_info["system_reward_g"],
        log_info["total_pay_g"],
        log_info["system_eat_g"],
        (t > 0 ? HIG : HIR),
        t,
    );
}

// 巫師設置開放 / 停止 遊戲；或設置當前總押注數量(更新後之前的記錄沒了，把它設置回來)。
// naihe 按：增加彩金設置之後，押注數量有相當大的影響，所以不能再隨意更改了。取消了這個功能。
protected int do_mewiz( string arg )
{
    object me = this_player();
    int add, now, all, because;
    string msg, help_msg;

    if( !wizardp(me) )
        return 0;
    help_msg = "指令參數如下：\n"
        +"<mewiz reward 數字 原因>  -- 給賭坊系統加入額外獎勵資金，單位 gold 。\n"
        +"                             也可以輸入負數來撤消它。\n"
        +"<mewiz stat>              -- 開放 / 關閉賭坊\n";
    if( arg == "stat" )
    {
        if( BetOn )
            BetOn = 0;
        else
            BetOn = 1;
        if( LOG_ON )
        {
            log_file( DUFANG_LOG_FILE, sprintf( "[%s] %s(%s)更改開放狀態，現在是：%d  。\n",
                ctime_format(), me->query("name"), getuid(me), BetOn )
            );
        }
        msg = sprintf( HIG"【公告】%s(%s)將長安城%s%s了，現在：%s。\n"NOR,
            me->query("name"), getuid(me), query("short"), (BetOn ? "開放" : "關閉"),
            (BetOn ? "正常營業" : "停止營業")
        );
        shout( msg );
        write( msg + "執行完畢，狀態已自動儲存。\n" );
        set( "long", query_now_long() );       // 每局遊戲結束後還要額外 set 一次，以改變 long().
        save();
        return 1;
    }
    if( stringp(arg) && sscanf( arg, "reward %d %s", add, because ) == 2 )
    {
        if( strsrch( SYSTEM_WIZ_ID, "$" + getuid(me) + "$" ) == -1 )
            return notify_fail("對不起，這個指令只能由指定巫師執行。\n"
                "指定巫師："+ replace_string( SYSTEM_WIZ_ID, "$", " ") + "\n"
            );
        if( add < -10000 || add > 10000 )
            return notify_fail("增加量范圍是 -10000 ~ 10000 之間。\n");
        now = log_info["system_reward_g"];
        all = now + add;
        if( all < 0 )
            return notify_fail("對不起，你不能將獎勵資金減到 0 以下。\n"
                "現在有："+now+"  增加："+add+"  結果："+all+"\n"
            );
        if( LOG_ON )
        {
            log_file( DUFANG_LOG_FILE, sprintf( "[%s] %s(%s)因為(%s)注入額外獎勵資金 %d ，原 %d -> %d 。\n",
                ctime_format(), me->query("name"), getuid(me), because, add, now, all )
            );
        }
        msg = sprintf( HIG"【公告】%s(%s)給長安城%s注入了 %d 兩黃金作額外獎勵資金，原因：%s\n"NOR,
            me->query("name"), getuid(me), query("short"), add, because,
        );
        log_info[ "system_reward_g" ] = all;
        shout( msg );
        write( msg + "執行完畢，狀態已自動儲存。\n" + system_info_msg() );
        save();
        return 1;
    }
    write( system_info_msg() + help_msg );
    return 1;
}

protected string check_percent_str()
{
    return sprintf( "%s：%d (%d%%)  %s：%d (%d%%)  %s：%d (%d%%)  %s：%d (%d%%)  %s：%d (%d.%d%%)\n",
            BIG_STR,    game_info["total_opened_da"],
                times_flag <= 1 ? 0 : game_info["total_opened_da"] * 100 / (times_flag-1),
            SMALL_STR,  game_info["total_opened_xiao"],
                times_flag <= 1 ? 0 : game_info["total_opened_xiao"] * 100 / (times_flag-1),
            SINGLE_STR, game_info["total_opened_dan"],
                times_flag <= 1 ? 0 : game_info["total_opened_dan"] * 100 / (times_flag-1),
            DOUBLE_STR, game_info["total_opened_shuang"],
                times_flag <= 1 ? 0 : game_info["total_opened_shuang"] * 100 / (times_flag-1),
            BAOZI_STR,  game_info["total_opened_baozi"],
                times_flag <= 1 ? 0 : (game_info["total_opened_baozi"] * 1000 / (times_flag-1)) / 10,
                times_flag <= 1 ? 0 : (game_info["total_opened_baozi"] * 1000 / (times_flag-1)) % 10,
    );
}

// 查詢押注信息，玩家操作接口函數
protected int do_chk( string arg )
{
    string id, msg;
    if( !arg )
        id = this_player()->query("id");
    else
        id = arg;
    if( (msg=check_beted_str(id)) == "" )
        return notify_fail( id + " 在本局未有任何押注。\n");
    write( msg );
    return 1;
}

// 押注，玩家操作接口函數
protected int do_bet( string arg )
{
    object me = this_player();
    string id, bet_key, type;
    int bet, beted;

    if( !BetOn )
        return notify_fail("對不起，本賭坊暫時停止營業。\n");
    if( GameStat == 2)
        return notify_fail("現在正在開出本局結果，請稍等下局再押。\n");
    id = me->query("id");
    if( !arg || sscanf( arg, "%d to %s", bet, type) != 2 )
    {
        write( check_beted_str( id ) );
        return notify_fail("押注格式： <bet 數量 to da|xiao|dan|shuang>\n");
    }
    // 可簡化
    switch( type )
    {
        case "a":
        case "A": type = "da";   break;
        case "b":
        case "B": type = "xiao"; break;
        case "c":
        case "C": type = "dan";  break;
        case "d":
        case "D": type = "shuang";break;
        case "e":
        case "E": type = "baozi";break;
    }
    if( member_array( type , keys(type_str) ) == -1 )
        return notify_fail("押注格式： <bet 數量 to da|xiao|dan|shuang>\n");
    if( bet < 1 || bet > 10000 )
        return notify_fail("押注范圍在 1 - 10000 兩白銀之間。\n");
    if( me->query( "balance" ) < bet*100 )
        return notify_fail("你的存款不足 "+bet+" 兩白銀了。\n");
    // naihe add 人數限制 05-12-6 8:46
    if( member_array( id, df_player ) != -1 )
    {
        if( MAX_DF_PLAYER > 0 && sizeof(df_player) >= MAX_DF_PLAYER )
            return notify_fail("對不起，這局遊戲押注的人已經太多了。\n");
        else
            df_player += ({ id });
    }
    bet_key = id + "-" + type;
    if( bet_info[ bet_key ] )
    {
        beted = bet_info[ bet_key ];
        if( beted + bet > 10000 )
            return notify_fail( "這局你已經押了 "+beted+" 兩白銀在 "
                +type_str[ type ]+" 上邊了，合計本次超出了最大押注限制。\n"
            );
        bet_info[ bet_key ] = beted + bet;          // 修改該玩家當局的該項押注
        log_info[ "total_bet" ] += (bet*100);       // 總押注額記錄
        this_bet += (bet*100);                      // 本局總押注額記錄
        me->add( "balance", -(bet*100) );
        message_vision( "$N拿過帳本大筆一揮，追加了 "+bet+" 兩白銀押  "+type_str[ type ]+ "。\n", me );
    }
    else
    {
        bet_info[ bet_key ] = bet;                  // 設置該玩家當局的該項押注
        log_info[ "total_bet" ] += (bet*100);       // 總押注額記錄
        this_bet += (bet*100);                      // 本局總押注額記錄
        me->add( "balance", -(bet*100) );
        message_vision( "$N拿過帳本大筆一揮，把 "+bet+" 兩白銀押上了  "+type_str[ type ]+ "。\n", me );
    }
    write( check_beted_str( id ) );
    if( GameStat == 0 )
    {
        valid_gogo_time = time() + GOGO_WAIT_TIME;       // 過幾秒才可以用 gogo 加速開獎。
        GameStat = 1;
        tell_room( this_object(), HIW"第 "+times_flag+" 局賭局將于 "+WAIT_TIME+" 秒後開始，要買的就快押啦！\n"NOR );
        remove_call_out( "game_start" );
        call_out( "game_start", WAIT_TIME, 0 );
    }
    //me->save();       // 不需要。玩家如果 quit 會 save()
    return 1;
}

// 加速開局，玩家接口函數
protected int do_gogo()
{
    if( GameStat != 1 )
        return notify_fail( "現在的狀態不能開獎。可能是無人押注，或者是已在開獎中。\n");
    if( valid_gogo_time > time() )
        return notify_fail( "等等別人也押點再開吧！\n");
    message_vision( "$N大聲叫道：快點開！立刻開！現在、馬上、給我開！\n", this_player() );
    GameStat = 2;
    remove_call_out( "game_start" );
    call_out( "game_start", 1, 0 );
    return 1;
}
