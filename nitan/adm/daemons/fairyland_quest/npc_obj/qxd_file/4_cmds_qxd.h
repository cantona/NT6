// hj 內基本指令

int do_who_in_hj()
{
    object rooms;
    mapping info;

    rooms = find_object( HJ_DIR+ "room_door_hj" );
    if( !rooms ) rooms = load_object( HJ_DIR + "room_door_hj" );
    if( !rooms ) return errs("發生意外錯誤，無法查詢。\n");
    write( rooms->who_in_hj()[ "info" ] );
    return 1;
}

int do_hjtop()
{
    object out_room;

    out_room = find_object( HJ_OUT_ROOM );
    if( !out_room )
        return errs("現在無法查看記錄。\n");
    write(HIW"
       『幻境﹒遙遠傳說之起緣﹒幽靈顯現』
"+out_room->get_TOP_pic()+"\n"NOR);
    return 1;
}

// 有BUG 55555555 已改正，並且優化了一下下。  naihe 2:36 03-10-24
// 接納玩家 pah (xsmarter) 的建議，加入了放棄技能的指令。
// 改了列表方式，雖然比之前的煩瑣，但能夠根據我的需要來排序。
int do_gsks( string arg )
{
    object me = this_player();
    int i, amount, temp;
    string *key;
    string msg, clcl, cl, pic, lv_pic, t1, t2;
    mapping all_skills, all_damages;

    string *list;


    if( !me_ok(me) ) return 0;

    all_skills=query_temp("hj_game_skills", me);
    all_damages=query_temp("hj_game_damages", me);

    if( !all_skills || !mapp(all_skills) || sizeof(all_skills) < 1 ||
        !all_damages || !mapp(all_damages) || sizeof(all_damages) < 1 )
        return errs("你並未學得任何 幻境 內的技能。\n");

    if( !arg ) arg = ".";

    if( sscanf(arg, "-d %s", msg) )
    {
        if( undefinedp( all_skills[msg] ) || undefinedp( all_damages[msg] ) )
            return errs("你並不懂得這項幻境內的技能。\n");

        arg = all_skills[msg];
        delete_temp("hj_game_skills/"+msg, me);
        delete_temp("hj_game_damages/"+msg, me);
        delete("huanjing2003/last_skills_name/"+msg, me);
        delete("huanjing2003/last_skills_lv/"+msg, me);
        me->save();
        message_vision( "$N逆運技能，把自己所懂得的「"+arg+"」散去了。\n",me);
        return 1;
    }

    // 下面開始以固定排序，列出玩家所懂得的技能。
    list = ({ "heal", "hfzj", "hyzj", "llzj", "ydzj", "dhzj", "fhzj", "gszj", });


    clcl = NOR + WHT;
    pic = "◆";
    msg = clcl +
          "□───────┬─┬─────┬─────┬─────────□\n" +
          "│    技   能   │LV│ 運用(yun)│ 絕技(pfm)│    效     果     │\n" +
          "├───────┼─┼─────┼─────┼─────────┤\n";


    for( i=0;i<sizeof(list);i++ )
    {
        if( undefinedp( all_skills[list[i]] ) || undefinedp( all_damages[list[i]] ) )
            continue;

        // 上色、特殊技提示及絕招提示
        cl = "";
        t1 = "   ----   ";
        t2 = "   ----   ";
        switch( list[i] )
        {
            case "heal" : cl = CYN; t1 = "克制(kz)"; break;
            case "hfzj" : cl = HIW; t1 = "翔空(xk)"; t2 = "狂風(kf)"; break;
            case "hyzj" : cl = HIM; t1 = "聰敏(cm)"; t2 = "暴雨(by)"; break;
            case "llzj" : cl = HIC; t1 = "力量(ll)"; t2 = "驚雷(jl)"; break;
            case "ydzj" : cl = HIG; t1 = "光芒(gm)"; t2 = "迅電(xd)"; break;
            case "dhzj" : cl = HIB; t1 = "守護(sh)"; t2 = "奪魂(dh)"; break;
            case "fhzj" : cl = HIR; t1 = "熱情(rq)"; t2 = "火燄(hy)"; break;
            case "gszj" : cl = HIY; t1 = "尋石(xs)"; t2 = "巨石(js)"; break;
        }

        // 加效果標記，讓人一眼可以看出是否能yun, pfm 以及技能高低
        if( all_damages[list[i]] > 99 )
            all_damages[list[i]] = 99;
        // 這一句實際上和 me->set_temp() 同樣效果。莫非 mapping 也是類似“指針”的？
        // 例如： mapping test = objecttt->query("lalala");
        //        objecttt->delete("lalala");
        // 那麼這個時候， lalala 的值，也成為“0”了！反之亦然。
        temp = all_damages[list[i]];

        if( t1 != "   ----   " )
        {
            if( temp >= YUN_LvNeed ) t1 = "●" + t1;
            else t1 = "○" + t1;
        }
        if( t2 != "   ----   " )
        {
            if( temp >= PFM_LvNeed ) t2 = "●" + t2;
            else t2 = "○" + t2;
        }
        lv_pic = "";
        while( temp>9 )
        {
            lv_pic += pic;
            temp -= 10;
        }
        if( strlen(lv_pic) > 18 ) lv_pic = lv_pic[0..17];

        msg += sprintf( clcl+"│%s%s(%s)"+clcl+"│%2d"+clcl+"│%-10s"+clcl+"│%-10s"+clcl+"│"+cl+"%-18s"+clcl+"│\n"+clcl,
            cl, all_skills[list[i]],list[i], 
            all_damages[list[i]],t1, t2, lv_pic );
        // 技能數量 +1
        amount ++;
    }

    // 為了今後若有擴展時，也可以顯示新技能
    // 這一段未完善，需要看加的是什麼技能再考慮更改。
    key = keys( all_damages );
    for( i=0; i<sizeof( key ); i++ )
    {
        // 已在前面處理過了，或者技能設置有誤，跳過
        if( member_array(key[i],list) != -1 || undefinedp( all_skills[ key[i] ] ) )
            continue;
        // 不加入顏色設置
        msg += sprintf( clcl+"│%s(%s)"+clcl+"│%2d"+clcl+"│%-10s"+clcl+"│%-10s"+clcl+"│"+cl+"%-18s"+clcl+"│\n"+clcl,
            all_skills[key[i]], key[i], 
            all_damages[key[i]], "   ----   ","   ----   ","");
            amount ++;
    }
    // 沒有通過檢測的技能
    if( !amount )
        return errs("你並未學得任何 幻境 內的技能。\n");
    msg += clcl+ "□───────┴─┴─────┴─────┴─────────□\n"NOR;
    write( "  以下是你學得的幻境內技能(共"+chinese_number(amount)+"項)：\n" + msg + "  如需要放棄某項技能，請使用指令：<gsks -d 技能名>  例如：gsks -d heal\n  請注意，輸入指令將直接放棄該技能，並無法恢復！\n");
    return 1;
}

int do_ghp()
{
    object me=this_player();
    string color, temp, temp2, temp3;
    int hp,hp_max, iii;

    if( !me_ok(me) ) return 0;

    hp=query_temp("hj_hp", me);
    hp_max=query_temp("hj_hp_max", me);

    color = HIB;
    if( hp > (hp_max * 2/10) ) color = HIR;
    if( hp > (hp_max * 4/10) ) color = HIM;
    if( hp > (hp_max * 6/10) ) color = HIY;
    if( hp > (hp_max * 8/10) ) color = HIG;
    if( hp > hp_max ) color = HIC;

    if( !temp = query("find_name") )
        temp = "神秘國度";
    switch( temp )
    {
        case "風之國度": temp = HIW+temp+NOR;break;
        case "雨之國度": temp = HIM+temp+NOR;break;
        case "雷之國度": temp = HIC+temp+NOR;break;
        case "電之國度": temp = HIG+temp+NOR;break;
    }
    temp2 = "";
    if( query_temp("hj_special/xk", me))temp2+=HIW"「翔空」"NOR;
    if( query_temp("hj_special/cm", me))temp2+=HIM"「聰敏」"NOR;
    if( query_temp("hj_special/ll", me))temp2+=HIC"「力量」"NOR;
    if( query_temp("hj_special/gm", me))temp2+=HIG"「光芒」"NOR;
    if( query_temp("hj_special/kz", me))temp2+=CYN"「克制」"NOR;
    if( query_temp("hj_special/sh", me))temp2+=HIB"「守護」"NOR;
    if( query_temp("hj_special/rq", me))temp2+=HIR"「熱情」"NOR;
    if( query_temp("hj_special/xs", me))temp2+=HIY"「尋石」"NOR;

    if( temp2 == "" ) temp2 = " ---";

    temp3 = "";
    iii=query_temp("hj_game_mepower", me);
    while( iii >4 )
    {
        temp3 += "◆";
        iii -= 5;
    }
    if( strlen( temp3 ) > 20 ) temp3 = temp3[0..19] + ">>>>";

    write( sprintf("【 %s ∥ LV "HIY"%d"NOR" ∥ 氣息：%s%d"NOR"/"HIG"%d"NOR" ∥ 得分："HIY"%d"NOR" ∥ 基本力量："HIY"%s"NOR" ∥ 累計殺死NPC "HIM"%d"NOR" 個 】\n【 技能運用中：%s 】\n"NOR,
        temp,query("huanjing2003/lv", me),color,
        hp,hp_max,query_temp("hj_score", me),temp3,query("huanjing2003/kill_npc", me),temp2));
    return 1;
}

// heal 方式更新，可以實現自動恢復。
int do_gheal(string arg)
{
    object target,me=this_player();

    if( !me_ok(me) ) return 0;

    if( !query_temp("hj_game_skills/heal", me) || !query_temp("hj_game_damages/heal", me) )
        return errs("你並不懂得恢復技能。\n");

    if( !arg || arg == query("id", me))target=me;
    else target=present( arg,environment( me ) );
    if( !target ) return errs("你要幫誰恢復氣息？\n");
    if( !target->is_character() ) return errs("這不是活物。\n");
    if( !living(target) ) return errs("還是先等這人醒來再說吧。\n");
    if( !query_temp("hj_hp", target) || !query_temp("hj_hp_max", target) )
        return errs("這人沒有絲毫氣息，還是免了吧。\n");

    // 本指令亦可幫NPC恢復氣息（將有迷題型NPC需要玩家去幫助） :)
    // 已不可幫助NPC恢復氣息。
    if( query_temp("hj_need_waiting", me) == "fighting" || query_temp("hj_fighting", me) )
            return errs("你還在戰鬥中，要療傷得先停下來(halt / ht)。\n");

    if( query_temp("hj_healing", me) )
        return errs("你已在運用恢復之技。\n");

    if( me->is_busy() )
        return errs("你還忙著呢。\n");

    if(target == me )
    {
        if( query_temp("hj_hp", me)>(query_temp("hj_hp_max", me)*9/10) )
            return errs("你還健康得很，不必調和氣息。\n");
        message_vision(CYN"$N"NOR+CYN"定下心來，靜靜地調和自己的氣息。\n"NOR,me);
    }
    else
    {
        if( present( "hj temp leave obj", target )      // 已經暫時離開遊戲了，不能幫他恢復hp
           || query("hj_game/npc", target )
           || query_temp("huanjing", target) != "start"
        )
            return errs("你不能幫助這個人恢復氣息。\n");

        if( query_temp("hj_hp", target)>(query_temp("hj_hp_max", target)*9/10) )
            return errs("這人還健康得很，不必調和氣息。\n");
        if( query_temp("hj_hp", me)<100 )
            return errs("你自顧不暇，還為別人療傷？\n");
        message_vision(CYN"$N"NOR+CYN"把手掌貼在$n"NOR+CYN"的背上，運起「恢復之技」來。\n"NOR, me, target );
    }

    set_temp("hj_healing", target, me);
    set_temp("hj_need_waiting", "healing", me);

    remove_call_out("healing");
    call_out("healing", 1, me );
    return 1;
}

void healing( object me)
{
    object env_me,env_target, target;
    int heal_lv, heal_hp;

    if( !me || !me_ok(me) )
        return;
    if( !query_temp("hj_need_waiting", me )
       || query_temp("hj_need_waiting", me) != "healing"
    )
        return;
    target=query_temp("hj_healing", me);
    if( !target
       || !query_temp("huanjing", target )
       || query_temp("huanjing", target) != "start"
       || !query_temp("hj_hp", target )
       || query_temp("hj_hp", target)<1
       || !query_temp("hj_hp_max", target )
      || present( "hj temp leave obj", target )
    )
         return hj_halt( CYN"$N"NOR+CYN"內勁一撤，停止了運用恢復之技。\n"NOR );
    env_target = environment( target );
    env_me = environment( me );
    if( !env_target || env_target != env_me || !query("room_mark", env_target )
      || query("room_mark", env_target) == 1 )
        return hj_halt( CYN"$N"NOR+CYN"內勁一撤，停止了運用恢復之技。\n"NOR );
    // 基本判斷通過。
    if( query_temp("hj_hp", target)>(query_temp("hj_hp_max", target)*9/10) )
    {
        if( me == target )
            return hj_halt( CYN"$N"NOR+CYN"調息已順，長長地舒了一口氣。\n"NOR);
        return hj_halt( CYN"$N"NOR+CYN"見得$n"NOR+CYN"已經調息順暢，撤回了掌來。\n"NOR);
    }

    if( me->is_busy() )
    {
        remove_call_out("healing");
        call_out("healing", 1, me );
        return;
    }
    heal_lv=query_temp("hj_game_damages/heal", me);
    heal_hp = (heal_lv / 2 + random(heal_lv / 2 ));  // lv 100 = 50 + random(50)
    // 雨之國度主動技能效果  使用恢復之技能時效力增強
    if( query_temp("hj_game_find", me) == "yu" )
        heal_hp += (heal_hp / 3) + random(heal_hp/5);
    if(target == me)
    {

        // 飛火之技唯一體現(1)，使用 heal 時降低忙時
        if( query_temp("hj_special/rq", me) )
            me->start_busy(1)+random(2);
        else me->start_busy(2+random(2));

        addn_temp("hj_hp", heal_hp, me);
        if( query_temp("hj_hp", me)>query_temp("hj_hp_max", me) )
            set_temp("hj_hp",query_temp("hj_hp_max",  me), me);
        message_vision(CYN"$N"NOR+CYN"定心調和氣息，只覺得傷勢恢復了些。\n"NOR,me);
        tell_object( me, sprintf("當前： %d / %d \n",
            query_temp("hj_hp", me),query_temp("hj_hp_max", me)));

        /* 取消
        // 運用這個技能，將可能損失一點力量
        if( !random(query_temp("hj_game_mepower", me)*3 )
           && query_temp("hj_game_mepower", me)>20 )
        {
            addn_temp("hj_game_mepower", -1, me);
            tell_object(me,HIY"你只覺得元氣恢復了許多，但力氣卻似乎小了。\n"NOR);
        }
        */
        // 但也可能獲得等級提升
        if( !random(query_temp("hj_game_damages/heal", me)*2) )
        {
            addn_temp("hj_game_damages/heal", 1, me);
            if( query_temp("hj_game_damages/heal", me)>99 )
                set_temp("hj_game_damages/heal", 99, me);
            else tell_object(me,HIY"你對「恢復之技」的領會又進了一層！\n"NOR);
        }
        remove_call_out("healing");
        call_out("healing", 1, me );
        return;
    }

    if( query_temp("hj_hp", me)<100 )
        return hj_halt( CYN"$N"NOR+CYN"正在幫助$n"NOR+CYN"療傷，卻發現自己氣息不暢，只得罷手。\n"NOR);


    // 飛火之技唯一體現(2)，使用 heal 時降低忙時
    if( query_temp("hj_special/rq", me) )
        me->start_busy( 1+random(3) );
    else
        me->start_busy(3+random(3));
    // 取消此設置
    // 若是為非NPC人物（即玩家）療傷，對方會有忙時。
    //    if( !target->query("hj_game/npc") )
    //        target->start_busy(2+random(2));
    addn_temp("hj_hp", heal_hp, target);

    if( query_temp("hj_hp", target)>query_temp("hj_hp_max", target) )
        set_temp("hj_hp",query_temp("hj_hp_max",  target), target);

    message_vision(CYN"$N"NOR+CYN"全力施行為$n"NOR+CYN"療傷，只見得$n"NOR+CYN"的臉色好轉了許多。\n"NOR, me, target);
    // 幫助他人(無論是否NPC)，將獲得一小點的加分，但需要消耗自身的氣息。
    // 已更改，需要消耗自己氣息（小量），但不會有得分。
    addn_temp("hj_hp", -random(heal_lv/3), me);
    message_vision(CYN"$N"NOR+CYN"聚精會神，轉眼間臉上已現出疲憊之色！\n"NOR,me);
    remove_call_out("healing");
    call_out("healing", 1, me );
    return;
}

int do_hjquit(string arg)
{
    object qxd,me = this_player();

    if( !me_ok(me) ) return errs("你不得使用本指令。\n");

    if ( !arg || (arg!= "fail" && arg!="ok") )
        return errs(HIG"\n             <hjquit> 指令使用提示：

< hjquit fail >     放棄所有的成績，立刻退出 幻境 遊戲。
                      "HIR"使用此指令將減少你的1點貢獻度，請慎用。"NOR"
< hjquit ok >       以正常方式退出（類似使用 回歸之鏡），
                      但你必須有 500 分以上的當前得分，並且
                      需要一定的 已進行遊戲 時間。
\n"NOR);

    if ( arg == "fail" )
    {
        if( query("shenzhou/pts", me)<1 )
            return errs("你連1點貢獻度都沒有，不得使用本指令。\n");
        write("你輸入了強制退出指令，視作失敗的情況退出 幻境 1 遊戲。"HIR"本指令將扣除你一點貢獻度！\n"NOR);
        addn("shenzhou/pts", -1, me);
        set_temp("hj_hp", -1, me);
        me->start_busy(5);
        return 1;
    }

    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙著呢。\n");

    qxd = present( "qixing deng",me);
    if( !qxd || query("my_master", qxd) != me )
        return errs("你身上沒有七星燈？……或者你不是它的主人？……\n");

    if( !query("can_quit_hj", qxd) )
        return errs("你才剛進來遊戲沒多久，確實要退出請使用 <hjquit fail> 指令作放棄退出。\n"HIR"請注意，使用 fail 類型指令退出將會扣減你的貢獻度1點，請慎用！\n"NOR);

    if( !query_temp("hj_score", me) || query_temp("hj_score", me)<500 )
        return errs("你當前的遊戲得分不夠 500 分，確實要退出請使用 <hjquit fail> 指令作放棄退出。\n"HIR"請注意，使用 fail 類型指令退出將會扣減你的貢獻度1點，請慎用！\n"NOR);

    if( query("wait_over", qxd) == "yes" )
        return errs("你的遊戲時間即將結束，請稍為等待即可。\n");

    message_vision(CYN"$N"NOR+CYN"高聲叫道：“現實映現！”\n"NOR,me);
    write(HIR"使用本指令，將扣除你的 500 點遊戲得分！\n"NOR);
    addn_temp("hj_score", -499, me);
    me->start_busy(3);

    set("use_huigui", "yes", qxd);

    message_vision(WHT"只見一陣白霧不知從何處飄來，癒來癒濃……\n"NOR,me);
    return 1;
}

int do_hjtime()
{
    object me = this_player();
    int enter_time=query_temp("hj_enter_time", me);;

    write(sprintf( "你進入遊戲的時間是 %s ，現在的時間是 %s ，\n遊戲時間%s 。\n",
        !enter_time ? "未知" : ctime_format( enter_time ),  ctime_format(),
        !enter_time ? "未知" : sprintf( "共 %d 小時 %d 分 %d 秒", 
            ( time() - enter_time ) / 3600,
            ( ( time() - enter_time ) % 3600 ) / 60,
            ( ( time() - enter_time ) % 3600 ) % 60 ) ) );

    return 1;
}

int do_halt()
{
    object me = this_player(),target;
    string temp;

    if( !me_ok(me) )
        return errs( "什麼？\n");
    if( (!query_temp("hj_healing", me) && !query_temp("hj_fighting", me)) || 
        !query_temp("hj_need_waiting", me) )
    {
        delete_temp("hj_need_waiting", me);
        return errs( "你現在並不在戰鬥或療傷中。\n");
    }
    temp=query_temp("hj_need_waiting", me);
    if( temp == "healing" )
    {
        target=query_temp("hj_healing", me);
        if( target == me )
        {
            hj_halt(CYN"$N"NOR+CYN"急吸一口大氣，停止了調整氣息。\n"NOR);
            return 1;
        }
        hj_halt(CYN"$N"NOR+CYN"掌力一收，停下了對$n"NOR+CYN"的療傷。\n"NOR);
        return 1;
    }
    hj_halt(CYN"$N"NOR+CYN"虛晃一招，躍出戰圈不打了。\n"NOR);
    return 1;
}

// 若主人（玩家）不在，本物件會被清除，所以不用考慮
// 延時中發生的意外。
void delete_special_sks( object me, string sks, string sks_name )
{
    // 話這麼說，基本安全總要做的
    if( !me || !me_ok(me) )
        return;
    // 如果用 wiztools 停止了運用，這裡再停一次，豈非搞笑？所以要看看它是否還在用。
    if( !query_temp("hj_special/"+sks, me) )
        return;
    delete_temp("hj_special/"+sks, me);
    message_vision( HIY"\n只見圍著$N"HIY"的一圈微光隱退，「"+sks_name+"」技能的效力消失了。\n\n"NOR, me);
}

int do_gyun( string arg )
{
    // 這個指令的擴展不好，不管了，就這樣罷。
    // 實在需要擴充時，再改為好擴充的方式。
    object me = this_player();
    string *sp_sks = ({ "xk", "cm", "ll", "gm", "kz", "sh", "rq", "xs" }), find_name;
    int HpNeed = 50, hpneed, del_time;
    // HpNeed 可能浮動增加 20%
    mapping sks_sks = ([
        "xk": ({ "翔空", "風之國度", "hfzj", "呼風之技" }), 
        "cm": ({ "聰敏", "雨之國度", "hyzj", "喚雨之技" }),
        "ll": ({ "力量", "雷之國度", "llzj", "落雷之技" }),
        "gm": ({ "光芒", "電之國度", "ydzj", "引電之技" }),
        "kz": ({ "克制",       "--", "heal", "恢復之技" }),
        "sh": ({ "守護",       "--", "dhzj", "奪魂之技" }),
        "rq": ({ "熱情",       "--", "fhzj", "飛火之技" }),
        "xs": ({ "尋石",       "--", "gszj", "滾石之技" }),
    ]);


    if( !me_ok(me) )
    {
        write("什麼？\n");
        return 1;
    }

    if( !arg || member_array( arg, sp_sks ) == -1 )
    {
        write( sprintf("
      你的特殊技能運用情況：
"WHT"=====================================
"HIW"    翔空(xk)   >>>>>>   %s
"HIM"    聰敏(cm)   >>>>>>   %s
"HIC"    力量(ll)   >>>>>>   %s
"HIG"    光芒(gm)   >>>>>>   %s
"NOR+CYN"    克制(kz)   >>>>>>   %s
"HIB"    守護(sh)   >>>>>>   %s
"HIR"    熱情(rq)   >>>>>>   %s
"HIY"    尋石(xs)   >>>>>>   %s
"NOR+WHT"=====================================\n"NOR, 
    query_temp("hj_special/xk", me)?"運用中":"--",
    query_temp("hj_special/cm", me)?"運用中":"--",
    query_temp("hj_special/ll", me)?"運用中":"--",
    query_temp("hj_special/gm", me)?"運用中":"--",
    query_temp("hj_special/kz", me)?"運用中":"--",
    query_temp("hj_special/sh", me)?"運用中":"--",
    query_temp("hj_special/rq", me)?"運用中":"--",
    query_temp("hj_special/xs", me)?"運用中":"--"));
        return 1;
    }

    // 忙時限制有調整，這是為了可以在戰鬥中或療傷中運用技能
    if( me->query_busy() > 5 )
    {
        write("你現在實在是太忙了(忙時5秒以上)，無法靜心運用特殊技能。\n");
        return 1;
    }
    // 不得重復運用。
    if( query_temp("hj_special/"+arg, me) )
    {
        write("你已在運用這個技能。\n");
        return 1;
    }
    // 需要大量氣息
    hpneed = HpNeed + random(HpNeed/5);
    if( query_temp("hj_hp", me)<(hpneed+50) )
    {
        write("你的氣息太弱，無法運用特殊技能。\n");
        return 1;
    }
    if( query_temp("hj_game_damages/"+sks_sks[arg][2], me)<YUN_LvNeed )
    {
        write(sprintf("你的「%s」等級不夠，無法運用「%s」技能。\n",
            sks_sks[arg][3], sks_sks[arg][0] ) );
        return 1;
    }
    // 效力
    del_time=query_temp("hj_game_damages/"+sks_sks[arg][2], me)*4/5;
    // 若是F,Y,L,D四種特殊技，非本國子民效力減半
    if( sks_sks[arg][1] != "--" && query("find_name") != sks_sks[arg][1] )
        del_time /= 2;

    set_temp("hj_special/"+arg, del_time, me);
    // 這個 set 的值無實用意義，可使用任意非零值。
    addn_temp("hj_hp", -hpneed, me);
    //    me->start_busy( me->query_busy() + 1 );
    // 取消技能運用的忙時。因其本身需要大量氣息，故不必限制忙時。
    // 各特殊技運用時的描述
    switch( sks_sks[arg][0] )
    {
        // #########################################################
        case "翔空":
            message_vision(HIW"\n只見$N"HIW"張開雙手，仰天閉目口誦咒文，霎時間平地起風，$N"HIW"竟至浮身半空！\n"
                "這正是風之「翔空」秘籍！\n\n"NOR, me);
            break;
        // #########################################################
        case "聰敏":
            message_vision(HIM"\n只見$N"NOR+HIM"兩手互握，低頭閉目默念咒文，頓時似有無限靈感紛湧而至！\n"
                "這正是雨之「聰敏」秘籍！\n\n"NOR, me);
            break;
        // #########################################################
        case "力量":
            message_vision(HIC"\n只見$N"HIC"雙目圓睜單拳向天，口中大喝一聲，頓時全身筋骨□啪作響，氣勢驚人！\n"
                "這正是雷之「力量」秘籍！\n\n"NOR, me);
            break;
        // #########################################################
        case "光芒":
            message_vision(HIG"\n只見$N"HIG"右手攤掌緩緩前伸，剎那間掌心凝聚一團耀眼光芒，瞬間籠罩全身！\n"
                "這正是電之「光芒」秘籍！\n\n"NOR, me);
            break;
        // #########################################################
        case "克制":
            message_vision( CYN"\n只見$N"NOR+CYN"雙掌合十，默默地念了幾句咒文，頓時一陣清風掠起，讓人心境平和，再無煩憂。\n"
                "這正是恢復之技「克制」秘籍！\n\n"NOR, me );
            del_time *= 4;  // 效力持久
            break;
        // #########################################################
        case "守護":
            message_vision( HIB"\n只見$N"HIB"雙手食指並置額心，口念咒文，四處即時和起一陣凄厲之聲，似有靈體護身一般！\n"
                "這正是奪魂之技「守護」秘籍！\n\n"NOR, me );
            break;
        // #########################################################
        case "熱情":
            message_vision( HIR"\n只見$N"HIR"左手握拳置于左腰之旁，右手伸出食、中二指，滿臉笑容，大喊一聲：“耶！”\n"
                "這正是飛火之技「熱情」秘籍！\n\n"NOR,me);
            break;
        // #########################################################
        case "尋石":
            message_vision( HIY"\n只見$N"HIY"雙手緊握放在臉前，閉目喃喃祈禱道：“石頭，石頭，我要石頭……”\n"
                "這正是滾石之技「尋石」秘籍！\n\n"NOR,me);
            break;
        // #########################################################
    }
    call_out( "delete_special_sks", del_time , me, arg, sks_sks[arg][0] );
    write( sprintf( "技能約持續 %d 秒幻境時間有效。\n", del_time ) );
    return 1;
}
