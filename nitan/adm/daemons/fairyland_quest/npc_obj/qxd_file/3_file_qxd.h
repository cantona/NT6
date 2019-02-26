void create()
{
    set_name(long_color+"七星燈"NOR, ({"qixing deng","deng"}));
    set_weight(10);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", longs + get_deng_pic(DENG_AMOUNT) );
        set("unit", "個");
        set("value", 0);
    }

    set("no_drop","這東西是隻屬於你一個人的。\n");
    set("no_give","這東西是隻屬於你一個人的。\n");
    set("no_steal","這東西是隻屬於別人一個人的。\n");
    set("no_get","這東西不是你的，無法拾取。\n");
    set("lost_time",1);  // 本輪已過的時間(秒)
    set("last_deng",DENG_AMOUNT);  // 還剩幾個燈
    set("no_updated_dest", 1 ); // 不讓 updated 隨機丟失

    set("hj_game/obj","qx_deng");

    setup();
}

void init()
{
    if(start_checking == 0)
    {
        start_checking = 1;
        remove_call_out("checking");
        call_out("checking",1);
    }
    add_action("do_ghp", ({ "ghp", "hh", }) );
    add_action("do_gi", ({ "gi", "ii", }) );
    add_action("do_gk", ({ "gkill", "kk", }) );
    add_action("do_gsks", ({ "gsks", "gskills", "ss", }) );
    add_action("do_gheal", ({ "gheal", "hl", }) );
    add_action("do_halt", ({ "ghalt", "ht", }) );
    add_action("do_gbei", ({ "gbei", "bb" }) );
    add_action("do_gpfm", ({ "gpfm", "pp",}) );
    add_action("do_gyun", ({ "gyun", "yy",}) );
    add_action("do_who_in_hj", ({ "gwho", "ww", }) );
    add_action("do_wizhg", "wizhg");
    add_action("do_hjtop", "hjtop", );
    add_action("do_hjtime", "hjtime");
    add_action("do_hjquit", "hjquit");    // 強制退出 huanjing 遊戲的指令。
    add_action("do_hjleave", "hjleave", );   // 臨時離開遊戲 
}

int do_wizhg()
{
    object me = this_player();
    if( !wizardp(me) ) return 0;
    if( !me_ok(me) ) return 0;
    set("use_huigui","yes");
    message_vision( CYN"$N"NOR+CYN"大聲叫道：“我是巫師，讓我回家！！！”\n"NOR+WHT"只見一陣白霧不知從何處飄來，愈來愈濃……\n"NOR,me);
    return 1;
}

void checking()
{
    object ob,me,*all_mine,debuger;
    int temp,hp,i;

    time=query("lost_time", this_object());
    deng=query("last_deng", this_object());

//    write("checking.\n");

    ob=this_object();
    me=query("my_master");

    if( !me || !query_temp("huanjing", me) )
    {
        call_out("delete_me",1);
        return;
    }

    if( query_temp("huanjing", me) == "fail" || query_temp("huanjing", me) == "over" )
        return;

    if( query_temp("huanjing", me) == "feng"
          || query_temp("huanjing", me) == "yu"
          || query_temp("huanjing", me) == "lei"
          || query_temp("huanjing", me) == "dian" )
    {
        if ( singing == "no" )
        {
            singing = "yes";
            switch(query_temp("huanjing", me) )
            {
                case "feng":songs=context1;break;
                case "yu":songs=context2;break;
                case "lei":songs=context3;break;
                case "dian":songs=context4;break;
            }
            remove_call_out("sing_song");
            call_out("sing_song",1,0,me);
        }
        return;
    }

    hp=query_temp("hj_hp", me);
    if( !hp || hp < 1 )
    {
        all_mine = all_inventory(me);
        if(all_mine || sizeof(all_mine) > 0)
        {
            int mark, mark2;
            object room, env;
            if( (env=environment(me)) )
                mark=query("room_mark", env);
            for(i=sizeof(all_mine)-1; i>=0; i-- )
            {
                if( query("hj_game/obj", all_mine[i] )
                   && query("id", all_mine[i]) != "qixing deng"
                )
                {
                    if( random(5) )
                    {
                        if( mark > 0 && mark <= HJ_ROOM_AMOUNT && !random(3) )
                            mark2 = mark;
                        else
                            mark2 = 1+random( HJ_ROOM_AMOUNT );
                        if( !(room = find_object( HJ_DIR +"hj_room"+mark2 )) )
                            if( !(room = load_object( HJ_DIR +"hj_room"+mark2 )) )
                                room = env;
                        all_mine[i]->move(room);
                        if( room == env )
                            message_vision(sprintf("一%s%s似是從$N身上跳出來般，跌在了地上。\n",
                                query("unit", all_mine[i]),query("name", all_mine[i])),me);
                        else
                        {
                            message_vision(sprintf("一%s%s似是從$N身上跳出來般，往遠處天空飛射而去！\n",
                                query("unit", all_mine[i]),query("name", all_mine[i])),me);
                            tell_room( room, sprintf("一%s%s突然從天上落了下來。\n",
                                query("unit", all_mine[i]),query("name", all_mine[i])));
                        }
                    }
                    else
                    {
                        destruct(all_mine[i]);
                    }
                }
            }
        }
        message_vision(HIR"$N"HIR"忽然兩眼發直，不能動彈了！\n"NOR,me);
        me->start_busy(3);
        set_temp("huanjing", "fail", me);
        remove_call_out("game_over");
        call_out("game_over",1);
        debuger = find_player("lonely");
        if( debuger && query("env/hj_wizmsg", debuger) )
            tell_object( debuger, sprintf( HIR"幻境遊戲通知：%s"HIR"(%s"HIR")失敗狀態離開了遊戲。 ( <unset hj_wizmsg> 不再發送本類信息)\n"NOR,
        query("name", me),query("id", me)));
        CHANNEL_D->channel_broadcast("rumor", sprintf("幻境: 聽説%s[%s]探險失敗，離開了幻境。",query("name", me),query("id", me)));
        return;
    }

    time++;

    if( wait_over == "yes" && time > DENG_TIME / 5 )
    {
        me->start_busy(3);
        set_temp("huanjing", "over", me);
        remove_call_out("game_over");
        call_out("game_over",1);

        debuger = find_player("lonely");
        if( debuger && query("env/hj_wizmsg", debuger) )
            tell_object( debuger, sprintf( HIR"幻境遊戲通知：%s"HIR"(%s"HIR")成功狀態離開了遊戲。 ( <unset hj_wizmsg> 不再發送本類信息)\n"NOR,
        query("name", me),query("id", me)));
        CHANNEL_D->channel_broadcast("rumor", sprintf("幻境: 聽説%s[%s]探險成功，離開了幻境。",query("name", me),query("id", me)));
        return;
    }

    if( wait_over !="yes" && time > DENG_TIME )  // 時間到，結束遊戲（ 不算 fail ）
    {
        if( EXTEND_DENG > 0 )
        {
            EXTEND_DENG--;
            if( EXTEND_DENG < 2 ) set("can_quit_hj", 1);
        }
        else
        {
            deng--;
            time=1;
            if(deng < 1)  // 燈全滅後，還有一點點時間。
            {
                wait_over = "yes";
                set("wait_over","yes");
            }

            if( deng > 0 )
                message_vision("$N只聽得似有一聲微響，只見"+query("name", ob)+"裏的一個亮點熄滅了。\n",me);
            else message_vision("$N只聽得似有一聲微響，只見"+query("name", ob)+"裏的最後一個亮點也熄滅了。\n",me);


            tell_object( me, get_deng_pic( deng ) );

            if(deng == 4) long_color=""HIB"";
            if(deng == 2) long_color=""BLU"";
            longs="這是一個四四方方的小盒子，盒蓋透明，你能見到內裏有"+long_color+chinese_number(deng)+"個小點"NOR"在散發着微弱的光芒。\n";
            set_name(long_color+"七星燈"NOR, ({"qixing deng","deng"}));
            if( deng > 0 ) set("long",longs + get_deng_pic(deng) );
            else set("long",BLU"這是一個四四方方的小盒子，盒蓋透明，裏面已經一絲亮光也見不到了。\n"NOR  + get_deng_pic(deng) );
        }
    }

    // 隨機讓別的玩家看到自己大概的狀態(虛擬遊戲裏也有PK哦)
    // 玩家若暫時離開遊戲，則不報告
    if( !present( "hj temp leave obj", me ) )
    {
        if( query_temp("hj_hp", me)<(query_temp("hj_hp_max", me)*2/10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    RED+query("name", me)+""RED"一副頭重腳輕的樣子，看來就要支持不住了。\n"NOR,({me}));
        }
        else if( query_temp("hj_hp", me)<(query_temp("hj_hp_max", me)*4/10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    HIR+query("name", me)+""HIR"受傷甚為嚴重，堪堪就要倒下似的。\n"NOR,({me}));
        }
        else if( query_temp("hj_hp", me)<(query_temp("hj_hp_max", me)*6/10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    HIY+query("name", me)+""HIY"似乎受了傷，看起來狀況不大好。\n"NOR,({me}));
        }
    }
    // 這裏為了迴歸之鏡的。
    if( query("use_huigui", this_object()) )
    {
        wait_over = "yes";
        time = DENG_TIME ;
    }
    // 得分 500+ 時，隨機掉分。這是為了讓玩家更緊湊地抓緊時間。
    // 恢復之技特殊技能“剋制”的唯一體現，不掉分
    if( query_temp("hj_score", me)>500 && !random(3) && !query_temp("hj_special/kz", me) )
    {
        // 玩家臨時離開時，減分的速度較慢
        if( !present( "hj temp leave obj", me ) || !random(3) )
            addn_temp("hj_score", -1, me);
    }
    set("lost_time",time);
    set("last_deng",deng);
    // 更新後的走路忙時系統，配合房間裏的增加busy語句，這裏就減少。
    addn_temp("hj_move_busy", -300, me);
    if( query_temp("hj_move_busy", me)<1 )
        set_temp("hj_move_busy", 1, me);

    remove_call_out("checking");
    call_out("checking",1);
}

void game_over()
{
    object me=query("my_master");
    int enter_time;
    if( !me || !query_temp("huanjing", me) )
    {
        call_out("delete_me",1);
        return;
    }
    message_vision(HIR"$N"HIR"突然一副靈魂出竅的樣子，緊接着消失不見了。\n"NOR,me);
    me->move( HJ_OUT_ROOM );
    message_vision(HIR"$N"HIR"身影逐漸顯現，似是回到現實裏來了。\n"NOR,me);
    enter_time=query_temp("hj_enter_time", me);
    write(sprintf( "你進入遊戲的時間是 %s ，結束的時間是 %s ，\n遊戲時間%s 。\n",
        !enter_time ? "未知" : ctime_format( enter_time ),  ctime_format(),
        !enter_time ? "未知" : sprintf( "共 %d 小時 %d 分 %d 秒", 
            ( time() - enter_time ) / 3600,
            ( ( time() - enter_time ) % 3600 ) / 60,
            ( ( time() - enter_time ) % 3600 ) % 60 ) ) );
    set_temp("hj_out_time", time(), me);
}

void sing_song(int i, object me)
{
    if( !me || !query_temp("huanjing", me) )
    {
        call_out("delete_me",1);
        return;
    }

    singing="yes";

    if (i<sizeof(songs))
    {
        if(i==0) message_vision(CYN"$N忽地似乎感到一陣歌聲又在耳邊響起，不禁凝神細聽起來。\n"NOR,me);
        else write(MAG"   "+songs[ i ] + "\n"NOR);
        i ++;
        remove_call_out("sing_song");
        call_out("sing_song",1,i, me);
    }
    else
    {
        set_temp("huanjing", "start", me);
        message_vision(CYN"你聽得聲音漸弱，終於靜止下來了。\n"NOR,this_object());
        write("\n在燈滅之後，就是你歸來之時……若你氣息(ghp)已無，就將失敗而歸……\n");
        write(HIW"在幻境裏，你只能使用特別的指令來進行攻擊。詳細請用 <help huanjing> 指令查詢。\n"NOR);
        remove_call_out("enter_hj");
        call_out("enter_hj",1);
    }
}

void enter_hj()
{
    object me,rooms,srl,debuger;

    string random_rooms, *key;
    int i, temp_int;
    mapping temp_map1, temp_map2;

    me = query("my_master");
    if( !me || query_temp("huanjing", me) != "start" )
    {
        call_out("delete_me",1);
        return;
    }

    random_rooms= HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
    message_vision(HIR"$N"HIR"踏步走出，忽然間感到一陣強烈的震盪！……\n"NOR,me);
    rooms = load_object(random_rooms);

    // 若玩家身上有遊戲內的標記，清除。
    delete_temp("hj_move_busy", me);
    delete_temp("hj_find_ok", me);
    delete_temp("hj_need_waiting", me);
    delete_temp("hj_game_skills", me);
    delete_temp("hj_game_damages", me);
    delete_temp("hj_find_gem", me);
    delete_temp("hj_quest_answer", me);
    delete_temp("hj_healing", me);
    delete_temp("hj_fighting", me);
    delete_temp("hj_special", me);
    delete_temp("hj_youling_job", me);
    delete_temp("hj_out_time", me);
    delete_temp("this_time_mark", me);

    // 清除完畢才能進入遊戲。
    // ###################################################
    // ###############  設置玩家各類信息  ################
    // ###################################################
    // 新加入的“等級”設置
    // 每1 lv，都能夠得到 0.5 power, 1 all skills, 20 hp_max 的進入加成。
    // lv 最低0級，最高9級。9級時，額外 +1。升級規則請參看 hj_room1.c .
    // lv 與本文件的“使用累積次數”部分有聯繫，請參看下文。
    if( !query("huanjing2003/lv", me) )
        set("huanjing2003/lv", 0, me);
    if( query("huanjing2003/lv", me)>9 )
        set("huanjing2003/lv", 9, me);
    // lv 加成
    if( query("huanjing2003/lv", me) == 9 )
        set("huanjing2003/lv_add", 10, me);
    else
        set("huanjing2003/lv_add",query("huanjing2003/lv",  me), me);
    // 進入時間
    set_temp("hj_enter_time", time(), me);
    // 得分，這個是遊戲結束後重要獎勵依據之一，在遊戲裏由各種途徑增加
    set_temp("hj_score", 1, me);
    // 這是玩家在戰鬥是將使用的方式的判斷！由本目錄 6_combat_qxd.h 內調用。
    set_temp("hj_bei", ".", me);
    // 取個隨機數做標記，該標記將判斷：某個組合好的寶物是否是該玩家在這一次
    // 遊戲裏得到的。如果不是，得分要打個折扣。
    // 這是在測試活動時，出現了這樣的情況：幾個玩家配合，其中一個拿到組合寶物
    // 之後直接 huigui 甚至是 hjquit fail，由於以前的設置是不讓組合寶物 checking()，
    // 所以玩家可以把寶物攢起來，到一定程度後一次過帶出去，以求高記錄和高效率。
    // 這個問題不改也行，不過對於統計數字來説，有點嚇人。還是改改吧。 :)
    set_temp("this_time_mark", 1+random(9999), me);
    // 力量、氣息以及技能，將在後面設置。
    // 基本設置完畢，為了描述更為顯眼，先將玩家 move room，
    // 再進行特別的判斷，並且顯示特別信息。那樣一來，這些
    // 特別的信息就不會被 room 的 long 沖掉。
    me->move(rooms);
    tell_object(me,"\n");
    // 接下來是特別的處理。玩家在退出遊戲時，進行了登記的話，無論
    // 成功與否，都會更新 "last_skills" 以及 "last_power" 。
    // 玩家可以選擇獎品項目“技能保留”、“力量保留”來繼續使用這些設置。
    // 技能保留限制：原等級 4/5，最高80級（即防BUG限制）！最低 LV 0，即遺忘該技能。
    // 力量保留限制：原力量 3/4，並且最高 30，最低 5。
    // 現在，先把上一次的記錄降低。玩家如果在遊戲中非法退出，或者
    // 不登記成績就退出，即得不到提升，只能越降越低，直至被取消。
    // 降低 last_power .
    if( query("huanjing2003/last_power", me) )
    {
        set("huanjing2003/last_power",query("huanjing2003/last_power",  me)*3/4, me);
        if( query("huanjing2003/last_power", me)>30 )
            set("huanjing2003/last_power", 30, me);
    // 如果太低，清除它。這裏與 lv 無關。
        if( query("huanjing2003/last_power", me)<6 )
            delete("huanjing2003/last_power", me);
    }
    // 降低 last_skills .
    if( query("huanjing2003/last_skills_name", me )
       && mapp(query("huanjing2003/last_skills_name", me) )
       && sizeof(query("huanjing2003/last_skills_name", me)) >= 1
       && query("huanjing2003/last_skills_lv", me )
       && mapp(query("huanjing2003/last_skills_lv", me) )
       && sizeof(query("huanjing2003/last_skills_name", me)) >= 1 )
    {
        temp_map1=query("huanjing2003/last_skills_lv", me);
        temp_map2 = ([]);

        key = keys( temp_map1 );
        // 檢測是否有該名字的 skills. 如果有，該 skills 通過，可以加入處理列表中。
        for( i=0; i<sizeof(key); i++ )
        {
            if( !undefinedp(query("huanjing2003/last_skills_name", me)[key[i]]) )
            {
                temp_int = temp_map1[key[i]] *4/5;
                if( temp_int > 80 ) temp_int = 80;
                if( temp_int ) temp_map2 += ([ key[i] : temp_int ]);
                else delete("huanjing2003/last_skills_name/"+key[i], me);
            }
        }

        // 設置降低後的技能列表。
        set("huanjing2003/last_skills_lv", temp_map2, me);
    }
    // 如前邊的眾多條件有任一不符，清理掉它們，避免未知的非法情況。
    else
    {
        delete("huanjing2003/last_skills_name", me);
        delete("huanjing2003/last_skills_lv", me);
    }
    // ok! 下面進行次數判斷，如果玩家有有效使用次數，則可以
    // 使用這些上一次的技能及力量。
    // 否則設置基本數值。
    if( query("huanjing2003/last_power_times", me) )
    {
        if( !query("huanjing2003/last_power", me) )
        {
            tell_object(me,sprintf("你還可以使用%d次累積力量，但是現在你的累積力量比你能得到的基本力量還低，並未生效。\n",query("huanjing2003/last_power_times", me)));
            set_temp("hj_game_mepower", 5, me);
        }
        else
        {
            addn("huanjing2003/last_power_times", -1, me);
            tell_object(me, sprintf("你使用了累積力量的獎勵，該獎勵還剩餘 %d 次。\n",
                query("huanjing2003/last_power_times", me)));
            set_temp("hj_game_mepower",query("huanjing2003/last_power",  me), me);
        }
    }
    else
        set_temp("hj_game_mepower", 5, me);
    // 是否有技能保留次數
    if( query("huanjing2003/last_skills_times", me) )
    {
        if( !query("huanjing2003/last_skills_lv", me) )
        {
            tell_object(me,sprintf("你還可以使用%d次累積技能，但是現在你沒有任何累積技能，並未生效。\n",query("huanjing2003/last_skills_times", me)));
            set_temp("hj_game_skills/heal", "恢復之技", me);
            set_temp("hj_game_damages/heal", 3+random(8), me);
        // 默認設置為只懂得 heal.
        }
        else
        {
            addn("huanjing2003/last_skills_times", -1, me);
            tell_object(me,sprintf("你使用了累積技能的獎勵，該獎勵還剩餘 %d 次。\n",
                query("huanjing2003/last_skills_times", me)));
            set_temp("hj_game_damages",query("huanjing2003/last_skills_lv",  me), me);
            set_temp("hj_game_skills",query("huanjing2003/last_skills_name",  me), me);
        }
    }
    // 否則設置默認技能。
    else
    {
        set_temp("hj_game_skills/heal", "恢復之技", me);
        set_temp("hj_game_damages/heal", 3+random(8), me);
    }
    if( 1 )
    {
        mapping find_name = ([
            "feng" : HIW"風之國度"NOR,
            "yu"   : HIM"雨之國度"NOR,
            "lei"  : HIC"雷之國度"NOR,
            "dian" : HIG"電之國度"NOR,
        ]);
        set_temp("apply/short",({sprintf("%s%s(%s)"NOR,
            find_name[ query_temp( "hj_game_find", me) ],
            query("name", me), capitalize(query("id",me)) ), }), me
        );
        set_temp("hj_apply_short", 1, me);
    }
    // 設置最大氣息（原來的可以累積最大氣息的設置已取消）
    set_temp("hj_hp_max", MAX_HP, me);
    // 下面進行 lv 加成設置。
    temp_int=query("huanjing2003/lv_add", me);
    // 在 lv 9 時，力量可自動保持為 20 點
    addn_temp("hj_game_mepower", temp_int/2, me);
    addn_temp("hj_hp_max", temp_int*20, me);
    // 在 lv 9 時，氣息為 700
    key=keys(query_temp("hj_game_damages", me));
    for( i=0;i<sizeof(key);i++ )
        addn_temp("hj_game_damages/"+key[i], temp_int, me);
    // 在 lv 9 時，技能可自動保持為 50 級

    // 全部設置完畢，還有額外的其他獎勵。
    // 破了記錄或者是幸運玩家，有一定的 max_hp 獎勵。
    if( query("huanjing2003/gift", me) )
    {
        tell_object(me,HIW"你曾是幻境遊戲的"+query("huanjing2003/gift", me)+"者！\n你將得到增多300點遊戲內最大氣息、力量增強10點的獎勵！\n"NOR);
        delete("huanjing2003/gift", me);
        addn_temp("hj_hp_max", 300, me);
        addn_temp("hj_game_mepower", 10, me);
    }
    // 雷之國度主動技能效果  氣息增強。這個增強在最後才增強。
    if( query_temp("hj_game_find", me) == "lei" )
        addn_temp("hj_hp_max", (query_temp("hj_hp_max", me)/10), me);
    if( query_temp("hj_hp_max", me)>1500 )
        set_temp("hj_hp_max", 1500, me);
    set_temp("hjleave_usetimes", 0, me);//hjleave指令可以讓玩家臨時離開時保護角色的安全
    // 所有設置完畢。設置 hp，接下來可以進入遊戲了。
    set_temp("hj_hp",query_temp("hj_hp_max",  me), me);
    // 得到一些必須的道具
    // 進入遊戲時，有一個 120秒 的神人令。
    srl=new(__DIR__"shenren_ling");
    srl->waiting_delete( 120 );
    srl->move(me);
    tell_object(me,"你得到一"+query("unit", srl)+query("name", srl)+"！\n");

    // 進入遊戲時，有一個 脱離水晶。( 這裏使用了同樣的變量名 )
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(2);
    srl->move(me);
    tell_object(me,"你得到一"+query("unit", srl)+query("name", srl)+"！\n");

    // 有一個定向水晶
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(0);
    srl->move(me);
    tell_object(me,"你得到一"+query("unit", srl)+query("name", srl)+"！\n");

/*  此為關鍵物品，不再發放。
// 進入遊戲時，有一個 迴歸之鏡。
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(3);
    srl->move(me);
    tell_object(me,"你得到一個"+query("name", srl)+"！\n");
*/

    // 接受玩家 tianya 的提議，不再強制取消玩家的收聽權。
    //    tell_object(me,HIB"你忽地覺得一片寂靜，剛才的聲音絲毫都聽不見了。\n"NOR);
    //    if(!wizardp(me)) me->delete("channels");

    debuger = find_player("lonely");
    if( debuger && query("env/hj_wizmsg", debuger) )
        tell_object( debuger, sprintf( HIR"幻境遊戲通知：%s"HIR"(%s"HIR")進入幻境遊戲。 ( <unset hj_wizmsg> 不再發送本類信息)\n"NOR,
            query("name", me),query("id", me)));

    CHANNEL_D->channel_broadcast("rumor", sprintf("幻境: 聽説%s[%s]進入了幻境，開始探險。",query("name", me),query("id", me)));
    remove_call_out("checking");
    call_out("checking",1);
    remove_call_out("random_dispersion");
    call_out("random_dispersion",1);
    remove_call_out("robot_check");
    call_out("robot_check", 180 + random(420) );

    me->save();
    return;
}

void delete_me()
{
    message_vision("$N忽地消失不見了。\n",this_object());
    destruct(this_object());
}

void real_random_dispersion()
{
    string random_rooms,msg;
    object obj,obj_me1,obj_me2,obj_me3,npc_ashman,rooms,me;
    int i;

    me=query("my_master");
    if( !me || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1 )
        return;
    msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
    // 如果玩家是離開狀態，那就不額外發放東西。
    if( !present( "hj temp leave obj", me ) )
    {
        // 發放 1-3 個隨機物品(包括各類NPC)至隨機房間。
        i = 1 + random(3);
        while( i-- )
        {
            random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
            rooms = find_object(random_rooms);
            if(!rooms) rooms = load_object(random_rooms);
            obj=new( obj_list_all[random(sizeof(obj_list_all))] );
            obj->move(rooms);
            if( query("msg", obj))msg=query("msg", obj);
            else msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
            tell_room(random_rooms,msg);
        }
        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms)
            rooms = load_object(random_rooms);
        // 隨機發放清道夫，即小矮人。
        // 小矮人停留時間更短了。
        i=1+random(2);
        while( i-- )
        {
            if( random(2) )
            {
                npc_ashman = new( __DIR__"hj_npc_ashman");
                npc_ashman->move(rooms);
                if( query("msg", npc_ashman))msg=query("msg", npc_ashman);
                else msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
                tell_room(random_rooms,msg);
            }
        }
        if( !random(5) )  // 為了情節緊湊，將會發放更多的殺戮型NPC進入遊戲
        {
            npc_ashman=new(__DIR__"hj_npc_kill");
            npc_ashman->move(rooms);
            if( query("msg", npc_ashman))msg=query("msg", npc_ashman);
            else msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
            tell_room(random_rooms,msg);
        }
    }
    // 發放與本人選擇有關的物品至隨機房間。
    if( about_me_obj == 0 )
    {
        about_me_obj=1;
        switch(query("find_name", this_object()) )
        {
            case "風之國度":
                obj_me1=new( obj_list_feng[0] );
                obj_me2=new( obj_list_feng[0] );
                obj_me3=new( obj_list_feng[1] );
                break;
            case "雨之國度":
                obj_me1=new( obj_list_yu[0] );
                obj_me2=new( obj_list_yu[0] );
                obj_me3=new( obj_list_yu[1] );
                break;
            case "雷之國度":
                obj_me1=new( obj_list_lei[0] );
                obj_me2=new( obj_list_lei[0] );
                obj_me3=new( obj_list_lei[1] );
                break;
            case "電之國度":
                obj_me1=new( obj_list_dian[0] );
                obj_me2=new( obj_list_dian[0] );
                obj_me3=new( obj_list_dian[1] );
                break;
        }

        // 這幾句的次序不能亂
        set("host_id",query("id",  me), obj_me1);
        obj_me1->setme(1);
        set("host_id",query("id",  me), obj_me2);
        obj_me2->setme(2);
        set("host_id",query("id",  me), obj_me3);//此為NPC，拿着最重要的物品部分

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me1->move(rooms);
        if( query("msg", obj_me1))msg=query("msg", obj_me1);
        else msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
        tell_room(random_rooms,msg);

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me2->move(rooms);
        if( query("msg", obj_me2))msg=query("msg", obj_me2);
        else msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
        tell_room(random_rooms,msg);

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me3->move(rooms);
        if( query("msg", obj_me3))msg=query("msg", obj_me3);
        else msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
        tell_room(random_rooms,msg);
    }
}
// 不斷地往遊戲中添加物件
void random_dispersion()
{
    remove_call_out("random_dispersion");
    real_random_dispersion();
    call_out("random_dispersion", 60 + random(60) );
}
    
void real_robot_check()
{
    object checker, me;

    me=query("my_master");
    if( !me || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1
       || !environment(me) || !query("room_mark", environment(me) )
       || !query_temp("this_time_mark", me )
      || present( "hj temp leave obj", me )   // 臨時離開遊戲，不發放 robot
    )
        return;
    checker = new( __DIR__"hj_robot_checker" );
    set("checking_player", me, checker);
    set("this_time_mark",query_temp("this_time_mark",  me), checker);
    checker ->move( environment(me) );
    checker ->start_check();
}
// robot 檢測程序，由另一個文件配合。
void robot_check()
{
    remove_call_out("robot_check");
    real_robot_check();
    call_out("robot_check", 600 + random(600) );
}
