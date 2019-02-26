// 由於文件太大，本文件被分開。本文件僅由 room_gameover_hj.c 調用。
// 領取獎品（兑換幻境遊戲的獎勵）。
// naihe 22:56 03-10-23


// #########################################################
// #########################################################
// #########################################################
//
// 數據類獎品規則説明：(award_data)
//            "score?"  ，需要多少點成績可以兑換
//            "me?"     ，能夠換多少
//            "dt-n?"   ，數據名稱
//            "c-name"  ，中文描述，2-4個字，否則不對齊（將會很難看）
//            "all->0?" ，是否僅能兑現一次
//
// 以 gxd 為例，得分必須有100點以上才可以兑換，並且將以 100:1 的兑換率計算得出
//              可以得到多少點 gxd. 它的 "all->0?" 是 "yes"，那麼不夠兑換的零頭
//              將會全部被清除。計算完之後，玩家被 set("shenzhou/pts", 點數)。
//
// 注意，例如 "gxd", "pot" 等位置的ID，僅前8個字符有效。
// 如 貢獻度、經驗值 等位置的中文名，僅前8個字符有效（即4個漢字）。
//
// 物件類獎品規則説明：（本類獎品已不開放，相關函數已刪除！）
//             規則同上，只是多了一個 "fl-set"。
//             它表示在移交這個物件之前，要先對物件進行一些什麼樣的 set.
//             例如 hsw, 則會設置： hsw->set("huanjing2003_award", 1);
//             不需要任何設置時，可不要 "fl-set" 或把 "fl-set" 的值留空。
//
// 特殊獎品規則説明：
// #define 的2個數值都是特殊獎品所需要的得分值，分別是：
//
//      KEEP_SKILLS_SCORE, 一次保留技能
//      KEEP_POWER_SCORE,  一次保留力量
//
// #########################################################
// #########################################################
// #########################################################


// ★★★★★★★★★★★★★★★★★★★★★★★★★
// ★★★★★★★★★★★★★★★★★★★★★★★★★
// ★★★★★★★★★★★★★★★★★★★★★★★★★


#define        KEEP_SKILLS_SCORE        500
#define        KEEP_POWER_SCORE         500

#define        award_data        ([ "gxd": ([ "score?":30,"me?":1,"dt-n?":"shenzhou/pts", "c-name":"貢獻度","all->0?":"yes" ]),"exp": ([ "score?":1,  "me?":900,"dt-n?":"huanjing2003/exp","c-name":"幻境經驗","all->0?":"yes" ]),"pot": ([ "score?":1,  "me?":300,"dt-n?":"huanjing2003/pot","c-name":"幻境潛能","all->0?":"yes" ]), ])

#define        award_obj    ([ ])

// ★★★★★★★★★★★★★★★★★★★★★★★★★
// ★★★★★★★★★★★★★★★★★★★★★★★★★
// ★★★★★★★★★★★★★★★★★★★★★★★★★



string get_prize_name( string n, string id )
{
    if( !n ) n = "神祕獎項";
    if( !id ) id = "??????";
    if( strlen( n ) > 8 ) n = n[0..7];
    if( strlen( id ) > 8 ) id = id[0..7];

    return sprintf( "%s(%s)", n, id );
}


int prize(string arg)
{
    object me = this_player(), temp_obj;
    int amount, temp_int, my_score, i;
    string msg, *key, temp_str;
    mapping award_all, temp_map;

    if( GetAward != "允許" )
        return notify_fail("領取獎品的程序已被巫師關閉，請稍等或詢問在線巫師。\n");

    if( query("is_checking") == query("id", me) )
        return notify_fail("現在正在計算你的得分，請稍等再領獎。\n");

    if( query_temp("huanjing", me) )
        return notify_fail("請先以 <YEAH> 指令計算得分，方可領獎。\n");


    my_score=query_temp("hj_score", me);

    // 測試情況時的特別設置。
    if( IS_TEST )
    {
        if( !TEST_AWARD_GXD )
            return notify_fail("現在是測試期間，並且沒有任何獎勵。請直接離開即可。\n");

        if( !arg || ( arg != "gxd" && arg != "leiji" ) )
            return notify_fail("現在是測試期間，僅有小量獎勵，以資鼓勵。你的得分是 "+my_score+" 點。\n"
                "換取貢獻度：<YEAH!!! gxd>  --> 將你所有得分換成貢獻度，每 500 點得分可得 "+TEST_AWARD_GXD+" 點。\n"
                "換取累積技能：<YEAH!!! leiji> --> 將你所有得分換成使用累積技能的機會。每 1000 點換得一次。\n");

        if( arg == "gxd" )
        {
            delete_temp("hj_score", me);
            amount = my_score / 500 * TEST_AWARD_GXD;
            message_vision("$N的得分為 "+my_score+" 點，領取了 "+amount+" 點貢獻度。\n",me);
            addn("shenzhou/pts", amount, me);
            return 1;
        }

        delete_temp("hj_score", me);
        amount = my_score / 1000;
        message_vision("$N的得分為 "+my_score+" 點，領取了 "+amount+" 次使用累積技能的機會。\n",me);
        addn("huanjing2003/last_skills_times", amount, me);
        if( query("huanjing2003/last_skills_times", me)>9 )
        {
            message_vision( "$N的累積技能使用次數已滿，最多隻能使用 9 次。\n",me);
            set("huanjing2003/last_skills_times", 9, me);
        }
        return 1;
        // test 狀態不做領獎 LOG。
    }
    // 好，正常狀態下的領獎程序。
    // 無論有分沒分，可以看獎品表。
    if( me->is_busy() ) return notify_fail("你還忙着呢，等有空再領獎吧。\n");
    me->start_busy( 1 );

    if( !arg )
    {

        msg = HIC"=====================================================================
        『幻境·遙遠傳説之起緣·幽靈顯現』    基本獎項列表\n\n"NOR;

        award_all = award_data + award_obj;
        key = keys( award_all );
        if( key && sizeof( key ) > 0 )
        {
            for( i=0;i<sizeof(key);i++ )
            {
                temp_map = award_all[ key[i] ];
                // 處理一下長度，漂亮些
                temp_str = get_prize_name( temp_map["c-name"], key[i] );
                msg += sprintf( "%s %-18s ---- %|4d 得分可換 %|4d \"%s\"。\n",
                    temp_map[ "all->0?" ] == "yes" ? "●" : "○",
                    get_prize_name( temp_map["c-name"], key[i] ),
                    temp_map[ "score?" ], temp_map[ "me?" ],
                    temp_map[ "c-name"] );
            }
        }

        msg += sprintf("
\"●\"標記表示：領取該獎時，將你的得分按兑換率計算後，可得到相應
              數額的獎品，而剩下的“零頭”得分將會被清除。
\"○\"標記表示：領取該獎時，扣除獎品需要的得分後，剩下的得分仍有效。

"HIW"請以 %s "HIW"指令領獎，你還有 %d 點的得分。
"HIY"特別獎項列表，請以 %s "HIY"指令查詢。
"HIC"=====================================================================\n"NOR,
            HIR"<YEAH!!! ID>"NOR, my_score,
            HIR"<YEAH!!! sp>"NOR,
            );

        me->start_more( msg );
        return 1;
    }

    if( arg == "sp" )
    {
        msg = sprintf( HIC"=====================================================================
        『幻境·遙遠傳説之起緣·幽靈顯現』    特別獎項列表"NOR"

    在你每一次退出幻境遊戲後，一旦計算得分，你的最後一次的所有技能和
力量都會被記錄。而每一次你進入幻境遊戲時，這些記錄都會被削減。其中：

    所有技能記錄削減為五分之四，無最高限制，1 級以下遺忘該技能，
                                    無任何技能時，恢復默認設置；
    力量    記錄削減為四分之三，最高 30 點，5 點或以下時恢復默認設置。

    你可以在這裏以得分兑換，而獲得使用這些累積值的機會。當你還擁有某
項的機會時，在你進入遊戲後，該項累積值將直接應用到遊戲中而不採取默認
的設置。但是，如果你還有某項機會次數，卻沒有了該項的累積記錄或該項數
值太低，你的使用機會的次數不會被扣減，而使用默認設置。

○ 技能保留(skills)  -----  以 %|4d 點得分換取 1 次機會，最多 9 次。
○ 力量保留(power)   -----  以 %|4d 點得分換取 1 次機會，最多 9 次。

"HIW"請以 %s "HIW"指令領獎，你還有 %d 點的得分。
"HIY"你的技能/力量記錄，以 <YEAH!!! last> 查詢。
"HIC"=====================================================================\n"NOR,
            KEEP_SKILLS_SCORE, KEEP_POWER_SCORE,
            HIR"<YEAH!!! ID>"NOR, my_score );

        write( msg );
        return 1;
    }
    // 查詢已被記錄了的各項值。(未削減)
    if( arg == "last" )
    {
        msg = sprintf(  "===============================================\n"
                "你的力量記錄為 %d 點，還有 %d 次使用的機會。\n",
                    query("huanjing2003/last_power", me),
                    query("huanjing2003/last_power_times", me));

        temp_map=query("huanjing2003/last_skills_lv", me);
        if( !temp_map || !sizeof(temp_map) )
            msg += "你沒有技能記錄。\n";
        else
        {
            msg+="你的技能記錄如下(還有"+query("huanjing2003/last_skills_times", me)+"次使用的機會)：\n";
            key = keys( temp_map );
            for( i=0;i<sizeof( key ); i++ )
            {
                msg += sprintf( "%s\t%s\t\t%d\n",
                    key[i],
                    !query("huanjing2003/last_skills_name", me)[key[i]]?
                        "無效技能" :
                    query("huanjing2003/last_skills_name", me)[key[i]],
                    temp_map[key[i]] );
            }
        }

        msg += "===============================================\n" +
            "這些數值將會在你下一次進入幻境的時候，被系統自動削減。\n"+
            "而如果你還有某項的使用機會，將可以繼續使用(被削減後的)對應的項目。\n";

        me->start_more( msg );
        return 1;
    }

    if( my_score < 1 )
        return notify_fail("你沒有任何得分，無法領獎。\n");

    switch( arg )
    {
        case "skills": temp_int = KEEP_SKILLS_SCORE; temp_str = "累積技能"; break;
        case "power": temp_int = KEEP_POWER_SCORE; temp_str = "累積力量"; break;
    }

    if( arg == "skills" || arg == "power" )
    {
        if( my_score < temp_int )
            return notify_fail("你的得分不足 "+temp_int+" 點，無法換取“"+temp_str+"”的獎勵。\n");

        if( query("huanjing2003/last_"+arg+"_times", me) >= 9 )
            return notify_fail("你已有 9 次或以上使用“"+temp_str+"”的機會了。\n");

        // OK，可以換
        addn("huanjing2003/last_"+arg+"_times", 1, me);
        set_temp("hj_score", my_score-temp_int, me);

        message_vision( "$N以 "+temp_int+" 點得分換下了一次“"+temp_str+"”的機會。\n", me);
        hj_log_file( sprintf("\n%s(%s)領獎--\"%s\"1次(需%d分)。(%s)\n",
            query("name", me),getuid(me),temp_str,temp_int,ctime_format()));
        return 1;
    }
    // 下面是普通獎品系列。
    // 判斷數據類獎品。
    if( !undefinedp( award_data[arg] ) )
    {
        temp_map = award_data[arg];
        // "gxd": ([ "score?":100,"me?":1,"dt-n?":"shenzhou/pts", "c-name":"貢獻度","all->0?":"yes" ]),
        if( my_score < temp_map[ "score?" ] )
            return notify_fail("你的得分不足以領取這個獎項。\n");
        temp_str = temp_map[ "c-name" ];
        // 一次領獎
        if( temp_map[ "all->0?" ] == "yes" )
        {
            // 計算可領獎次數
            temp_int = my_score / temp_map[ "score?" ];
            // 計算得獎總數
            temp_int *= temp_map[ "me?" ];
            // LOG
            message_vision( sprintf("$N把所有的得分用來換取了 %d 點%s。\n",
                temp_int, temp_str), me );
            hj_log_file( sprintf("\n%s(%s)領獎--\"%s\"%d點(一次性%d分)。(%s)\n",
                query("name", me),getuid(me),temp_str,temp_int,
                query_temp("hj_score", me),ctime_format()));
            // 設置
            addn(temp_map["dt-n?"], temp_int, me);
            delete_temp("hj_score", me);
            return 1;
        }
        // 非一次領獎
        // 計算次數
        temp_int = temp_map[ "me?" ];
        // 這裏的 my_score 用意已改，作為領獎需要的得分值。
        my_score = temp_map[ "score?" ];
        message_vision( sprintf( "$N以 %d 點得分換取了 %d 點%s。\n",
            my_score, temp_int, temp_str), me);
        hj_log_file( sprintf("\n%s(%s)領獎--\"%s\"%d點(需%d分)。(%s)\n",
            query("name", me),getuid(me),temp_str,temp_int,
            my_score, ctime_format() ) );
        addn(temp_map["dt-n?"], temp_int, me);
        addn_temp("hj_score", -my_score, me);
        return 1;
    }
    write("沒有這個獎品。請輸入 <YEAH!!!> 查詢普通獎項，或 <YEAH!!! sp> 查詢特別獎項。\n");
    return 1;
}
