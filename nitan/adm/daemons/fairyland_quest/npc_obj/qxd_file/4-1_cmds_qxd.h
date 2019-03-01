// 支持幻境內基本指令
// 上一個文件寫不下了，寫到這裡來
// 本指令參考 cmd i 而寫
// 實話說，仔細地看了 i 指令，發現 hj 裡實在大有可精簡之處，sigh
// naihe 6:39 03-11-5
string get_msg( object *list, int type )
{
    mixed class123;
    object *temp;
    int n, i=0;
    string msg = "  ";

    if( !list || sizeof(list) < 1 ) return "";

    // 先進行處理，將同一名稱物件分成各小組
    class123 = unique_array( list, (: sprintf( "%s%s%s",
            base_name($1),$1->name(),query("id", $1)):));

    // 開始組織其信息
    foreach( temp in class123 )
    {
        // 以此方法保持每橫排可列出 2 或 3 個名字，節約屏幕啊
        i++;
        if( i>3 && type ) { i=1;msg += "\n  "; }
        if( i>2 && !type ) { i=1;msg += "\n  "; }
        // 類型為 0 時，2個一橫排，否則 3個一橫排

        n = sizeof(temp);
        msg += sprintf( "(%2s)%s  ", n<10 ? "0"+n : ""+n, temp[0]->short() );
    }

    return msg;
}


int do_gi()
{
    object *inv, me = this_player(), *temp, *hjinv, *list;
    int n;
    string msg, cl;

    // 隨時允許查詢
//    if( !me_ok(me) ) return 0;

    inv = all_inventory(me);
    if( !inv || sizeof(inv) < 1 )
        return errs("你身上沒有攜帶任何東西。\n");

    // 得到一個 object 組，該組內只包含 有query("hj_game/obj")信息的任何物件
    hjinv=filter_array(inv,(:query("hj_game/obj", $1):));

    // 若無該組，可直接返回
    if( !hjinv || !sizeof(hjinv) )
        return errs( "你共攜帶"+chinese_number(sizeof(inv))
                +"件其他物品，並沒有任何幻境內物品。\n");
    // 設置頭信息
    msg = sprintf(HIC"
你共攜帶 %d 件各式物品，負重是 %d%% 。
其中有 %d 件其他物品，%d 件幻境內物品：
=======================================================================\n"NOR,
        sizeof(inv),
        me->query_encumbrance() * 100 / me->query_max_encumbrance(), 
        sizeof(inv)-sizeof(hjinv), sizeof(hjinv) );

    cl = HIY;

// 開始進行詳細的分類統計。

    // 劍器類
    list=filter_array(hjinv,(:query("hj_game/obj", $1) == "sword":));
    // 如果有劍器類，組織其信息並將這些從總列表中剔除
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"攻擊劍器類(共 %d 件)：\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // 魔法水晶類
    list=filter_array(hjinv,(:query("hj_game/obj", $1) == "magic":));
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"魔法水晶類(共 %d 件)：\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // 技能石類
    list=filter_array(hjinv,(:query("hj_game/obj", $1) == "quest":));
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"技能石類(共 %d 件)：\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // 輔助類
    list=filter_array(hjinv,(:query("hj_game/obj", $1) == "tools":));
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"輔助道具類(共 %d 件)：\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // 果品或寶石類
    list=filter_array(hjinv,(:query("hj_game/obj", $1) == "other":));
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"果品或寶石類(共 %d 件)：\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // 權杖、各族寶物類
    list=filter_array(hjinv,(:query("hj_game/obj", $1) == "the_gem"
                   || query("hj_game/obj", $1) == "the_gem_qz":));
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"各族寶物類(共 %d 件)：\n"NOR"%s\n",
                n, get_msg( list, 0 ) );
        hjinv -= list;
    }

    // 如果還有剩余，即為特殊類
    if( n = sizeof( hjinv )  )
        msg += sprintf( cl+"特殊類(共 %d 件)：\n"NOR"%s\n",
                n, get_msg( hjinv, 0 ) );

    msg += HIC"=======================================================================\n"NOR;
    write( msg );
    return 1;
}

// 臨時離開遊戲
int do_hjleave(string arg)
{
    object me = this_player();
    if( !me_ok(me) )
        return errs( "什麼？\n");
    if( !arg || arg != "yes" )
        return errs( 
            "當你在幻境遊戲中需要暫時離開時，請使用這個指令。\n"
            "這個指令可以讓你的遊戲角色受到保護，不會受到來自任何方面的攻擊。\n"
            "不過，關于你的一些遊戲內容會繼續，例如遊戲總時間到達後你會結束遊戲；等等。\n"
            "每局遊戲裡只能使用三次這個指令。使用時，你必須在空閒狀態下。\n"
            "\n          如果你確實想暫時離開，請輸入： hjleave yes\n\n"
        );
    if( query_temp("hjleave_usetimes", me) >= 3 )
        return errs( "本局遊戲你已經用過這個功能 3 次了。\n");
    if( me->is_busy()
       || query_temp("hj_healing", me )
       || query_temp("hj_fighting", me )
       || query_temp("hj_need_waiting", me )
    )
        return errs( "你還忙著呢！你必須在空閒時才能使用這個指令。\n");
    if( query("room_mark", environment(me)) == 1 )
        return errs( "你不能在 1 號地點使用這個指令。\n" );
    addn_temp("hjleave_usetimes", 1, me);
    new( __DIR__"hj_temp_leave") -> move(me);
    return 1;
}