int do_gpfm( string arg )
{
    object me = this_player();
    if( !me_ok(me) )
        return 0;
    if( !arg )
        return errs("你準備使用什麼絕技？\n");
    if( query_temp("hj_need_waiting", me) == "fighting" || query_temp("hj_fighting", me) )
    {
        set("pfm_ready", arg);
        write("你默默聚勁，準備發出絕技 「"+arg+"」 ！\n");
        return 1;
    }
    write("絕技只能在戰鬥時發出！\n");
    return 1;
}

int do_gbei( string arg )
{
    object me = this_player();
    string now_bei, msg;

    if( !me_ok(me) ) return 0;

    now_bei=query_temp("hj_bei", me);
    if( !now_bei ) now_bei = ".";
    if( now_bei == "." || now_bei == "hand" || now_bei == "none" )
        msg = "徒手攻擊";
    else
    {
        if( strsrch( now_bei , "zj" ) != -1 )
            msg = "使用技能 「"+now_bei+"」";
        else msg = "使用道具 「"+now_bei+"」";
    }

    if( !arg ) return errs( "本指令讓你設置在戰鬥中使用的方式，亦可簡化為 <bb> 。
例如： gbei bs jian , 在戰鬥中將會搜尋你身上以及地上的ID為\"bs jian\"的
       道具，對目標進行道具輔助形式的攻擊。
例如： gbei hfzj , 在戰鬥中將會以技能“呼風之技”，對目標進行技能攻擊。

你可以設置例如： gbei jian , 那麼當你身上有 \"jian\" 這個ID的道具時，
都會繼續使用它們來攻擊。

而當你所設置的方式已經無法實現，將自動使用空手攻擊，但你的設置會被保留。

如果你希望以空手攻擊，請設置： <gbei .>  ，或 <gbei hand> ， 或 <gbei none>。
需要查看自己已經設置的狀態，請輸入 <gbei ?> 指令。

你現在設置的方式是："+ msg + " \n");

    if( arg == "?" )
        return errs("你現在準備好的戰鬥方式是："+ msg + " \n");

    set_temp("hj_bei", arg, me);
    now_bei=query_temp("hj_bei", me);
    if( now_bei == "." || now_bei == "hand" || now_bei == "none" )
        msg = "徒手攻擊";
    else
    {
        if( strsrch( now_bei , "zj" ) != -1 )
            msg = "使用技能 「"+now_bei+"」";
        else msg = "使用道具 「"+now_bei+"」";
    }
    write("你把戰鬥方式準備為： "+ msg +" 。\n");
    return 1;
}

// gk 方式更新，實現自動打鬥，並加入絕技。
int do_gk(string arg)
{
    //    object me,target,tools;
    //    int damages,me_busy,me_power,target_busy;
    //    string tools_name,target_name,do_att="no",color_name,temp,skills_name,skills_name2;

    object me = this_player(), target;
    string target_id;

    if( !me_ok(me) ) return 0;

    if(!arg) return errs("你想要攻擊誰？\n");

    if( query_temp("hj_need_waiting", me) == "healing" || query_temp("hj_healing", me) )
            return errs("你還在療傷呢，要打架得先停下來(halt / ht)。\n");

    target = present( arg, environment(me) );

    if(!target) return errs("這裡沒有這個人。\n");
    if(!target->is_character()) return errs("這不是活物！\n");
    if( !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1 )
        return errs(query("name", target)+"沒有絲毫幻境裡的氣息，不必攻擊了吧。\n");
    if(!living(target)) return errs("這個遊戲裡必須是清醒的對手才能攻擊。\n");
    if(target == me ) return errs("攻擊自己？沒必要吧……\n");

/*  允許任何玩家對殺。
// 自己得分不夠，不許殺玩家
    if( query_temp("hj_score", me)<200 && !query("hj_game/npc", target) )
        return errs("你的遊戲得分那麼低，還是抓緊時間弄分數去吧！\n");

// 不允許殺得分低的玩家
    if( query_temp("hj_score", target)<200 && !query("hj_game/npc", target) )
        return errs(query("name", target)+"的遊戲得分太低，這樣做好象不太好吧？\n");
*/


    if( query("gender", me) == "男性" )
        message_vision(HIR"\n只聽得$N"HIR"大喝道：『納命來！』，朝著$n"HIR"搶上便攻！\n\n"NOR, me, target );
    else if( query("gender", me) == "女性" )
        message_vision(HIR"\n只聽得$N"HIR"一聲矯呼：『受死吧！』，朝著$n"HIR"搶上便攻！\n\n"NOR, me, target );
    else message_vision(HIR"\n只聽得$N"HIR"陰側側地一笑，更不打話，朝著$n"HIR"搶上便攻！\n\n"NOR, me, target );


    set_temp("hj_fighting", target, me);
    set_temp("hj_need_waiting", "fighting", me);

    // 這裡不用 remove_call_out(), 因為該函數內有判斷句，多余的 call_out 不作處理。
    call_out("fighting", 1);
    return 1;
}

// 對目標進行一次攻擊
void do_attack( object me, object target, int damages )
{
    string describe;
    if( !objectp(me) || !objectp(target) || damages < 1 )
        return;
    // 所謂暴擊……
    if( !random(50) )
    {
        message_vision( HIR"忽然一陣"HIY"金光"HIR"閃過，$N"HIR"這一擊的威力加強了數倍！\n"NOR, me );
        damages *= 2+random(2);
    }
    // 打NPC時
        if( query("hj_game/npc", target) )
        {
            // NPC設個標記是你打的
                set("killme_by",query("id",  me), target);
        // 可以得到得分。
        // 電之國度被動技能效果  戰鬥中得分上漲
        if( query_temp("hj_special/gm", me) )
            addn_temp("hj_score", 1+random(damages/8), me);
        else
            addn_temp("hj_score", 1+random(damages/10), me);
    }
    target->hj_get_attack(me);  // 目標執行一個受到攻擊的函數，只有 hj npc 才有這個函數
    addn_temp("hj_hp", -damages, target);//給目標扣血
    // 顯示健康狀態
    describe=get_health_desc(query_temp("hj_hp", target),query_temp("hj_hp_max", target));
    message_vision(NOR"（ $N"+describe+NOR" ）\n"NOR,target);
    // 完畢。
}

void fighting()
{
    object me = query("my_master"), inv_me, inv_target, target, use_tools, srl;
    string figh_type, fight_use, use_skills, color_name, skills_name, describe, temp;
    int damages, me_busy, me_power, target_busy;

    mapping pfm_info;

    if( !me || !me_ok(me) ) return;

    // 玩家已收式(halt)。
    // 這個句子不行，有很小的幾率會造成錯誤。
    //    if( !me->query_temp("hj_fighting") || me->query_temp("hj_need_waiting") != "fighting")
    // 這就可以了 :)
    if( !query_temp("hj_need_waiting", me )
      || query_temp("hj_need_waiting", me) != "fighting" )
        return;

    target=query_temp("hj_fighting", me);
    if( !target || query("room_mark", environment(me)) == 1 )
        return hj_halt( HIW"\n$N"HIW"擺了一個收式，停下手來。\n\n"NOR );

    // 目標是玩家，已死亡或有意外
    if( !query("hj_game/npc", target) && 
        (!query_temp("huanjing", target )
         || query_temp("huanjing", target) != "start"
         || !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1
         || !query_temp("hj_hp_max", target)) )
             return hj_halt( HIW"\n$N"HIW"擺了一個收式，對著$n"HIW"哈哈一笑，停下手來。\n\n"NOR );

    // 目標不是玩家，已死亡
    if( query("hj_game/npc", target) && 
        (!query_temp("hj_hp", target) || query_temp("hj_hp", target)<1) )
             return hj_halt( HIW"\n$N"HIW"擺了一個收式，對著$n"HIW"哈哈一笑，停下手來。\n\n"NOR );

    inv_target = environment( target );
    if( !inv_target || inv_target != environment(me) || !query("room_mark", inv_target) )
        return hj_halt(HIW"\n$N"HIW"見"+query("name", target)+HIW"已不在此處，擺了一個收式，罷下手來。\n\n"NOR);

    // 目標攜帶神人令
    if( (srl=present("shenren ling",target)) )
    {
        message_vision(CYN"$N"NOR+CYN"身上的"+query("name", srl)+NOR+CYN"突然發出一陣光芒！\n"NOR,target);
        return hj_halt( HIB"$N"HIB"忽感一陣莫名的巨大壓力，只得罷下手來。\n"NOR );
    }
    // 目標離開遊戲
    if( present( "hj temp leave obj", target ) )
    {
        return hj_halt( CYN"$n"NOR+CYN"身形忽隱忽現，竟似並無實體一般！$N"NOR+CYN"只得罷下手來。\n"NOR );
    }
    // 好的，下面準備開始攻擊目標。
    // 忙時中，等待下一秒。
    if( me->is_busy() )
    {
        remove_call_out("fighting");
        call_out("fighting", 1);
        return;
    }
    // 可以打了，判斷打的形式
    // 防錯
    if( !query_temp("hj_bei", me) )
        set_temp("hj_bei", "hand", me);

    figh_type = ".";

    // 有絕技請求，先行判斷
    if( query("pfm_ready") )
    {
        // 該函數進行判斷並返回信息。
        pfm_info = can_use_pfm( query("pfm_ready"), me, target );
        // 把絕技請求刪除
        delete( "pfm_ready" );
        // 如果返回0，則不繼續做任何處理。
        if( !mapp(pfm_info) || !sizeof(pfm_info) )
        {
            remove_call_out("fighting");
            call_out("fighting", 1);
            return;
        }
        // 不可用時，將返回提示信息 "err_msg" 給玩家一個提示
        // 必須是 sizeof() 為 7 的數據才是正常的。
        if( sizeof( pfm_info ) != 7 )
        {
            if( !pfm_info || undefinedp( pfm_info[ "err_msg" ] ) )
                tell_object( me, "發生意外，無法使用絕技！\n");
            else tell_object( me, pfm_info[ "err_msg" ] + "！\n");
        }
        // 否則無錯誤，允許使用該 pfm 。
        // 下邊的描述程序中，將完全使用 pfm_info 裡提供的數據。
        else figh_type = "pfm";
    }
    // 開始判斷其他的情況
    // 玩家設定空手
    fight_use=query_temp("hj_bei", me);

    if( figh_type == "." &&
      (!fight_use || fight_use == "." || fight_use == "hand" || fight_use == "none")
    )
        figh_type = "hand";
    // 攻擊類型未確定，繼續進行判斷。判斷是否技能類型。
    // 先查看有無該技能，以及是否氣息過弱
    if( figh_type == "." )
    {
        if( fight_use != "heal"
           && query_temp("hj_game_skills/"+fight_use, me )
           && query_temp("hj_game_damages/"+fight_use, me )
        )
        {
            // 有技能，玩家氣息是否過低
            if( query_temp("hj_hp", me)<100 )
            {
                message_vision( HIY"\n$N"HIY"忽然覺得氣息不順，只好放棄技能攻擊，改用空手作戰。\n\n"NOR, me);
                figh_type = "hand";
                // 強制給他設置徒手戰鬥
                set_temp("hj_bei", "hand", me);
            }
            // 那麼OK，使用技能
            else
            {
                use_skills = fight_use;
                figh_type = "skills";
            }
        }
        // 無該項技能，查找身上的道具
        else
        {
            use_tools = present( fight_use, me );
            // 只能使用身上的，要用就要揀起來。
//            if( !use_tools ) use_tools = present( fight_use, environment( me ) );
            // 無該道具，空手作戰
            if( !use_tools ) figh_type = "hand";
            else
            {
                // 找到了，要看是不是能打架的東西
                // 是道具但是不是能用的，轉空手
                if( !query("hj_game/obj", use_tools )
                  || !query("use_times", use_tools) || !query("power", use_tools )
                  || !query("busy", use_tools )
                  || (query("hj_game/obj", use_tools) != "sword"
                     && query("hj_game/obj", use_tools) != "magic") )
                    figh_type = "hand";
                // 否則定為可用。
                else figh_type = "tools";
            }
        }
    }

    // 防止未知的錯誤，理論上來說不會出現
    if( figh_type != "tools" && figh_type != "skills" && figh_type != "pfm" )
        figh_type = "hand";
    // **********************************
    // 好了，下面根據類型進行攻擊
    // 根據玩家的力量，確定基本攻擊力
    if( !query_temp("hj_game_mepower", me) )
        set_temp("hj_game_mepower", 5, me);
    me_power=query_temp("hj_game_mepower", me);

    // 雷之國度被動技能效果  戰鬥中提升基本力量
    if( query_temp("hj_special/ll", me) )
        me_power = (me_power*2) + random(me_power);
    // 徒手攻擊
    if( figh_type == "hand" )
    {
        // 確定攻擊力、忙時等
        damages = (me_power * 3 / 4 + random(me_power / 4) );
        me_busy = 2;
        // 攻擊描述
        temp = ({
            "揮出一拳",
            "踢出一腳",
            "劈出一掌",
            "側身一撞",
            "飛身一踢",
        })[ random(5) ];
        // 不使用 message_vision() 的方式
        tell_room(environment(me),CYN"\n"+query("name", me)+NOR+CYN"奮力向"+query("name", target)+NOR+CYN+temp+"！\n"NOR,({me,target}));
        tell_object(target,CYN"\n"+query("name", me)+NOR+CYN"奮力向你"+temp+"，造成了"HIR""+damages+""NOR+CYN"點的傷害！\n"NOR);
        tell_object(me,CYN"\n你奮力向"+query("name", target)+NOR+CYN+temp+"，造成了"HIG""+damages+""NOR+CYN"點的傷害！\n");
        if( !random(query_temp("hj_game_mepower", me)*2) )
        {
            write(HIY"你只覺得打拳腳功夫多了，力量似乎又大了些。\n"NOR);
            addn_temp("hj_game_mepower", 1, me);
        }
    }
    // 用道具攻擊
    if( figh_type == "tools" )
    {
        // 看看是什麼類型的道具先
        // 劍類
        if( query("hj_game/obj", use_tools) == "sword" )
        {
            // 先確定攻擊力、忙時等
            damages = ( me_power *3 / 4 + random( me_power / 4 ) ) +
                  (query("power", use_tools)*3/4)+
                  random(query("power", use_tools)/4);

            if( query("busy", use_tools) == 888)me_busy=0;
            else me_busy=query("busy", use_tools);
            addn("use_times", -1, use_tools);
            // 判斷 use_tools 使用次數完畢而要 delete 的句子放在後邊，
            // 否則此時 delete 了它，後面還要調用，就有BUG BUG。
            // 好，攻擊描述
            temp = ({ "攻", "削", "刺", "劈", "挑" })[ random(5) ];
            tell_room(environment(me),CYN"\n"+query("name", me)+NOR+CYN"握起"+query("name", use_tools)+NOR+CYN"向"+query("name", target)+NOR+CYN+temp+"去！\n"NOR,({me,target}));
            tell_object(target,CYN"\n"+query("name", me)+NOR+CYN"握起"+query("name", use_tools)+NOR+CYN"向你"+temp+"來，造成了"HIR+damages+NOR+CYN"點的傷害！\n"NOR);
            tell_object(me,CYN"\n你握起"+query("name", use_tools)+NOR+CYN"向"+query("name", target)+NOR+CYN+temp+"去，造成了"HIG+damages+NOR+CYN"點的傷害！\n");
        }
        // 否則是魔法水晶類
        else
        {
            // 確定攻擊力等
            damages = ( me_power * 3 / 4 + random( me_power / 4 ) ) +
                  (query("power", use_tools)*3/4)+
                  random(query("power", use_tools)/4);
            if( query("type", use_tools) == query("find_name") )
                damages *= 2+random(2);
            if( query("busy", use_tools) == 888)me_busy=0;
            else me_busy=query("busy", use_tools);
            addn("use_times", -1, use_tools);
            switch(query("type", use_tools) )
            {
                case "風之國度": color_name=HIW;break;
                case "雨之國度": color_name=HIM;break;
                case "雷之國度": color_name=HIC;break;
                case "電之國度": color_name=HIG;break;
                default:color_name = WHT;
            }
            message_vision(color_name+"\n$N"NOR+color_name+"舉起$n"NOR+color_name+"大聲呼喚道：“魔法速現！”\n"NOR,me, use_tools);
            tell_room(environment(me),color_name+"只見"+query("att_msg", use_tools)+"向"+query("name", target)+NOR+color_name+"攻去，造成了"HIG+damages+NOR+color_name+"點的傷害！\n"NOR,target);
            tell_object(target,color_name+"只見"+query("att_msg", use_tools)+"向你攻來，造成了"HIR+damages+NOR+color_name+"點的傷害！\n"NOR);
        }
    }

    // 技能攻擊
    if( figh_type == "skills" )
    {
        // 確定攻擊力及忙時等
        // 這是一個特殊的地方，使用技能時最多只能有力量的 1/2
        damages = me_power / 4 + random( me_power / 4 ) +  
            (query_temp("hj_game_damages/"+use_skills, me)*3/4)+
              random(query_temp("hj_game_damages/"+use_skills, me)/4);

        skills_name=query_temp("hj_game_skills/"+use_skills, me);
        me_busy = 2+random(2);

        switch( query("find_name") )
        {
            case "風之國度":
                if(skills_name == "呼風之技")
                damages += damages / 2 ;   // 1.5 倍
                break;
            case "雨之國度":
                if(skills_name == "喚雨之技")
                damages += damages / 2;
                break;
            case "雷之國度":
                if(skills_name == "落雷之技")
                damages += damages / 2;
                break;
            case "電之國度":
                if(skills_name == "引電之技")
                damages += damages / 2;
                break;
        }
        if(skills_name == "飛火之技" || skills_name == "滾石之技")
            damages = 1+(damages/3)+random(damages*2);

        switch( skills_name )
        {
            case "呼風之技" : color_name = HIW; break;
            case "喚雨之技" : color_name = HIM; break;
            case "落雷之技" : color_name = HIC; break;
            case "引電之技" : color_name = HIG; break;
            default: color_name = WHT; break;
        }
        tell_room(environment(me),color_name+"\n"+query("name", me)+NOR+color_name+"運起「"+skills_name+"」向"+query("name", target)+NOR+color_name+"攻去！\n"NOR,({me,target}));
        tell_object(target,color_name+"\n"+query("name", me)+NOR+color_name+"運起「"+skills_name+"」向你攻來，造成了"HIR+damages+NOR+color_name+"點的傷害！\n"NOR);
        tell_object(me,color_name+"\n你運起「"+skills_name+"」向"+query("name", target)+NOR+color_name+"攻去，造成了"HIG+damages+NOR+color_name+"點的傷害！\n"NOR);

        addn_temp("hj_hp", -(3+random(3)), me);
        // 使用技能，每次將隨機降低自身HP數點。
        // 有機會得到技能提升，難度更大了
        if( !random(query_temp("hj_game_damages/"+use_skills, me)*2) )
        {
            addn_temp("hj_game_damages/"+use_skills, 1, me);
            if( query_temp("hj_game_damages/"+use_skills, me)>99 )
                set_temp("hj_game_damages/"+use_skills, 99, me);
            else tell_object(me,HIY"你對「"+skills_name+"」的領會又進了一層！\n"NOR);
        }
    }
    // 絕技攻擊
    if( figh_type == "pfm" )
    {
        // 絕技攻擊時，攻擊力等完全由絕技函數判定，這裡只是加上力量的基本攻擊。
        // 絕技攻擊的基本攻擊力與使用技能時一樣，最多只能有力量的 1/2
        damages = me_power / 4 + random( me_power / 4 ) + pfm_info[ "damages" ];
        me_busy = pfm_info[ "me_busy" ];
        addn_temp("hj_hp", -pfm_info["lost_hp"], me);
        // 描述
        temp = replace_string( pfm_info[ "msg_all" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_room(environment(me), temp, ({ me, target }) );

        temp = replace_string( pfm_info[ "msg_me" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_object( me,temp );

        temp = replace_string( pfm_info[ "msg_target" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_object( target, temp );
    }
    // 好了，所有的描述什麼的都搞定了
    // 調用 標準攻擊函數進行攻擊。
    // ################################################
    do_attack( me, target, damages );
    // ################################################
    // 風之國度被動技能效果，戰鬥中busy降至最低。
    if( query_temp("hj_special/xk", me) && me_busy )
        me->start_busy(1);
    // 否則正常計算。
    else
        me->start_busy(me_busy);
    // 特別的技能或道具，令對方有忙時
    if( figh_type == "skills" && skills_name =="奪魂之技" )
    {
        addn_temp("hj_hp", -(3+random(3)), me);
        // 若是使用奪魂之技，將額外需要更多的氣息。
        // 奪魂之技特殊技能體現之二(1)，有效抵抗來自玩家的奪魂類攻擊的忙時效果
        if( !query_temp("hj_special/sh", target) && !random(10 )
            && target->query_busy() < 6 )
        {
            // 99 lv 奪魂技可造成 20 秒忙時
            target_busy=query_temp("hj_game_damages/dhzj", me)/5;
            if(target_busy < 2) target_busy = 2;
            target->start_busy( target_busy + target->query_busy() );
            tell_room( environment(me), sprintf( HIR"%s"HIR"突然兩眼發直，整個人呆住了似的。\n"NOR, target->name(1)), ({me,target}));
            tell_object( target, HIR"你突然兩眼發直，整個人呆住了似的。 (造成忙時 "+target_busy+" 秒)\n"NOR );
            tell_object( me, HIR+target->name(1)+HIR+"突然兩眼發直，整個人呆住了似的。 (造成忙時 "+target_busy+" 秒)\n"NOR );
        }
    }
    // 奪魂之技特殊技能體現之二(2)，有效抵抗來自玩家的奪魂類攻擊的忙時效果
    if( !query_temp("hj_special/sh", target) && !random(5 )
        && figh_type == "tools" && target->query_busy() < 6
         && (query("id", use_tools) == "dh sj" || query("id", use_tools) == "dh jian") )
    {
        target_busy = 10+random(11);
        target->start_busy( target_busy + target->query_busy() );
        tell_room( environment(me), sprintf( HIR"%s"HIR"突然兩眼發直，整個人呆住了似的。\n"NOR, target->name(1)), ({me,target}));
        tell_object( target, HIR"你突然兩眼發直，整個人呆住了似的。 (造成忙時 "+target_busy+" 秒)\n"NOR );
        tell_object( me, HIR+target->name(1)+HIR+"突然兩眼發直，整個人呆住了似的。 (造成忙時 "+target_busy+" 秒)\n"NOR );
    }
    // 這裡才判斷是否要 delete use_tools.
    if( figh_type == "tools" && use_tools && query("use_times", use_tools) <= 0 )
        use_tools->delete_me();
    // 搞定！
    // 電之國度主動技能效果  戰鬥中可能附加攻擊
    if( random(8) == 2 && query_temp("hj_game_find", me) == "dian" )
    {
        message_vision( GRN"忽然不知從哪裡引出一道"BLINK+HIG"閃電"NOR+GRN"劈向$N"NOR+GRN"，打個正中！\n"NOR, target );
        damages=(query_temp("hj_game_damages/ydzj", me)/2);
        if( damages < 5 )
            damages = 5;
        if( damages > 20 )
            damages = 20;
        // 調用 標準攻擊函數進行攻擊。
        // ################################################
        do_attack( me, target, damages );
        // ################################################
    }
    // 這裡再加一次判斷，如果對方死了，直接就 return 了。
    // 目標是玩家，已死亡或有意外
    if( !query("hj_game/npc", target) && 
        (!query_temp("huanjing", target )
         || query_temp("huanjing", target) != "start"
         || !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1
         || !query_temp("hj_hp_max", target)) )
             return hj_halt( HIW"\n$N"HIW"擺了一個收式，對著$n"HIW"哈哈一笑，停下手來。\n\n"NOR );
    // 目標不是玩家，已死亡
    if( query("hj_game/npc", target) && 
        (!query_temp("hj_hp", target) || query_temp("hj_hp", target)<1) )
             return hj_halt( HIW"\n$N"HIW"擺了一個收式，對著$n"HIW"哈哈一笑，停下手來。\n\n"NOR );

    // 好了，循環 :)
    // 如果是更特別的道具，迅隱之劍，將直接調用下一次，而不等待1秒
    if( figh_type == "tools" && use_tools && query("id", use_tools) == "xy jian" )
    {
        fighting();
        return;
    }
    remove_call_out("fighting");
    call_out("fighting", 1);
    return;
}
