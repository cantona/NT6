// for hj_npc_quest.c  #include.
// naihe 16:30 03-10-19
// naihe 05-9-12 8:15 hj2003 繼續更新~~

void delete_me()
{
    int q_iii = query("iii"), award_score;
    object temp_obj,ob=this_object();

    if( q_iii == 0 || q_iii == 4 )
        message_vision("$N四下看了看，匆匆離開了。\n",ob);
    if( q_iii == 1 )
    {
        if(query("go_where") !="ok")
        {
            if(!query("following_name"))
                message_vision("$N滿臉迷茫地走了開去……又多了一個迷失兒童……\n",ob);
            else
            {
                message_vision("$N大聲哭道：“"+query("following_name")+"你又説帶我去，那麼久了都沒去到！”\n",ob);
                message_vision("只見$N傷心地往旁邊的路上走去……又多了一個迷失兒童……\n",ob);
                temp_obj=find_player(query("following_id"));
                if( temp_obj && query_temp("huanjing", temp_obj) == "start" && 
                   query_temp("hj_score", temp_obj)>200 )
                {
                    award_score = 30 + random(21);
                    addn_temp("hj_score", -award_score, temp_obj);
                    tell_object(temp_obj,"過了許久，你才想起來你曾答應過帶一個迷路的小精靈找什麼地方的！\n你覺得心裏掠過一絲內疚。\n"HIR"遊戲提示：你的得分減少了 "+award_score+" 點。\n"NOR);
                }
            }
        }
        else
        {
            message_vision("$N高興極了，甜甜地説道：“謝謝你，"+query("following_name")+"！”\n",ob);
            message_vision("$N揮了揮手，走了開去。\n",ob);
        }
    }
    if( q_iii == 2)
        message_vision("只見$N一拍腦袋，説道：“哎呀，忘記了家裏的小魚還沒喂！”\n$N急急忙忙地離開了。\n",ob);
    if( q_iii == 3)
    {
        if(!query("asking") )
            message_vision("$N輕歎一聲，説道：“罷了，罷了！”，竟爾就此離去。\n",ob);
        else
        {
            if(query("asking") == "ok")
            {
                message_vision("只見$N自言自語道：“想不到除了老頭子我，還有人對武林人士都那麼熟悉！”\n",ob);
                message_vision("$N一邊説着，一邊踱步前行，就此離去了。\n",ob);
            }
            if(query("asking") == "fail")
            {
                message_vision("$N搖頭歎道：“難道就再沒有人，能夠把這武林之人事熟知於心？”説罷，竟爾就此離去。\n",ob);
            }
            if(query("asking") == "waiting" && query("asking_for_id") )
            {
                temp_obj = present(query("asking_for_id"),environment(ob));
                if(temp_obj)
                {
                    message_vision("$N長歎一聲，説道：“"+query("asking_for_name")
                        +"，你仍未想得到嗎？這人是"+query("the_answer")+"！”\n",ob);
                    message_vision("$N十分失望地説道：“這人如此有名，你竟然不知道！你仔細想想吧！”\n",ob);
                    message_vision("$N慚愧之色立現於臉，頓時陷入了沉思中。\n",temp_obj);
                    temp_obj->start_busy(20);
                    message_vision("只見$N一邊搖着頭，一邊離開了。\n",ob);
                }
                else
                {
                    temp_obj=find_player(query("asking_for_id"));
                    if( temp_obj && query_temp("huanjing", temp_obj) == "start" )
                    {
                        ob->move(environment(temp_obj));
                        message_vision("只見一個老人走了過來，對着$N劈頭就罵道："
                            +"“哪有如你如此無理之人？答應回答我的問題，卻悄悄溜走！”\n",temp_obj);
                        message_vision("老人忽地一掌向$N擊來！$N躲閃不得，一陣麻木"
                            +"隨之而來，頓時動彈不得！\n",temp_obj);
                        temp_obj->start_busy(30);
                        message_vision("$N説道：“你給我好好反省反省罷！”言罷竟然就此離去！\n",ob);
                    }
                }
            }
        }
    }
    if( q_iii == 5 || q_iii == 6 )
    {
        if( query("all_found") )
            message_vision("$N一臉喜悦之情，往旁邊走了開去。\n", ob);
        else
            message_vision("$N長歎一聲，往旁邊走了開去。\n", ob);
    }
    destruct(ob);
}

void init()
{
    switch( query("iii") )
    {
        case 0: case 4:
            add_action("do_gmai",({ "gmai", "gbuy" }) );
            add_action("do_glist","glist");
            break;
        case 1: case 7:
            // 這個 set 好像必須要放在這裏的
            if( !query("go_where") )
                set("go_where", 2 + random( HJ_ROOM_AMOUNT -1 ) );
            add_action("do_answer","answer");
            break;
        case 2:
            add_action("do_lianli","lianli");
            break;
        case 3:
            add_action("do_huida","huida");
            break;
        case 5: case 6:
            add_action("do_found", "found" );
            add_action("do_foundall", "foundall" );
            break;
    }
}

int ask_help()
{
    switch(query("iii"))
    {
        case 0: case 4:
            command("hehe "+query("id"));
            command("say “我這裏有一些東西可以買(gmai)，你也可以先看看價格表(glist)。”");
            break;
        case 1:
            if(!query("following_name"))
            {
                command("say “我迷路了啊……有個地方叫做「"+chinese_number(query("go_where"))
                    +"」的，你能帶我去那裏嗎？(answer ok)”");
                remove_call_out("delete_me");
                call_out("delete_me",60);
            }
            else
                command("say “我迷路了，"+query("following_name")+"要帶我去找「"
                    +chinese_number(query("go_where"))+"」呢。”");
            break;
        case 2:
            command("say “哦？這個啊……來，你打我一拳，讓我看看你的力量有多高再説吧！”");
            command("say “不用怕，你小娃兒還傷不了我！我這就是準備讓你煉力(lianli)呢！”");
            break;
        case 3:
            if( !query("asking_for_id") )
            {
                command("say “恩……江山代代新人來，這英雄二字，卻不知有誰當得？”");
                command("say “你若知曉，可願意回答我的提問(huida 好)？”");
            }
            else
                command("say “古往今來，多少英雄好漢？我又如何道盡你知？”");
            break;
        case 5:
            if( query("found_sword") != "yes" )
            {
                command("say “我聽説有一柄"+query("finding_name")+"削鐵如泥，端的是鋒利異常，真想看一看。”");
                command("say “如果你能幫我找到(found 劍的id)，請告訴我好嗎？”");
            }
            if( query("found_all_sword") != "yes" )
                command("say “我正在蒐集一套寶劍，你能幫我找到的話(foundall)，請告訴我好嗎？”");
            if( query("all_found") )
                command("haha");
            break;
        case 6:
        if( query("found_crystal") != "yes" )
        {
            command("say “我聽説有一顆"+query("finding_name")+"神祕莫名，真想看一看。”");
            command("say “如果你能幫我找到(found 水晶的id)，請告訴我好嗎？”");
        }
        if( query("found_all_crystal") != "yes" )
            command("say “我正在蒐集一套魔法水晶，你能幫我找到的話(foundall)，請告訴我好嗎？”");
        if( query("all_found") )
            command("haha");
            break;
    }
    return 1;
}

int do_found( string arg )
{
    object me = this_player(), ob = this_object(), f_obj;
    string f_name;
    int award_score;

    if( !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waitting", me) )
        return notify_fail("你還忙着呢，有空了才幫人吧。\n");

    if( !arg ) return notify_fail("你找到了什麼？\n");
    f_obj = present( arg , me );
    if( !f_obj ) return notify_fail("你身上沒有這樣東西。\n");

    message_vision(CYN"$N"NOR+CYN"興奮地拿出一"+query("unit", f_obj)+f_obj->name(1)+NOR+CYN"，對着$n"NOR+CYN"説道：“你是不是在找這個？”\n",me,ob);

    if( query("found_sword") == "yes" || query("found_crystal") == "yes" )
    {
        command("haha");
        command("say “在下已經見識過"+query("finding_name")+"了，有勞費心了。”");
        return 1;
    }

    f_name = query("finding_name");

    if( !query("cj-sheng.zb-ke", f_obj) || query("cj-sheng.zb-ke", f_obj) != ob
        || delcolor( f_obj->name(1) ) != f_name )
    {
        command("shake");
        command("say “這不是我要找的"+f_name+"。”");
        return 1;
    }

    // 正確了！
    f_obj->move( ob );
    command("ah");
    command("touch "+query("id", me));
    command("say “對！這就是我要找的"+f_name+"！真是太感謝你了！”");
    message_vision( sprintf( CYN"$N"NOR+CYN"把%s"NOR+CYN"接了過去，審視良久，歎道：“這%s"NOR+CYN"我能得一見，已無憾矣！”\n", f_name, f_name ), ob );
    message_vision( CYN"$n"NOR+CYN"對$N"NOR+CYN"説道：“所謂寶物配英雄，這"+f_name+NOR+CYN"正是該由你所有！”\n$n"NOR+CYN"説完，把"+f_name+NOR+CYN"又交回了$N"NOR+CYN"手中。\n"NOR, me, ob);

    // 本任務主要是能夠得到超級道具獎勵
    set("power",query("power",  f_obj)*2, f_obj);
    if( query("power", f_obj)>50 )
        set("power", 50, f_obj);
    set("use_times",query("use_times",  f_obj)*2, f_obj);
    if( query("use_times", f_obj)>20 )
        set("use_times", 20, f_obj);

    award_score = 30 + random(21);
    f_obj->move( me );
    message_vision(CYN"$N"NOR+CYN"只覺得$n"NOR+CYN"入手沉甸，已不似原先的感覺。\n"NOR, me, f_obj);
    write(HIR"遊戲提示：你的得分增加了 "+award_score+" 點！\n"NOR);
    addn_temp("hj_score", award_score, me);

    set( "found_sword", "yes" );
    set( "found_crystal", "yes" );

    if( query("found_all_sword") == "yes" || query("found_all_crystal") == "yes" )
    {
        set("all_found", 1);
        remove_call_out("delete_me");
        call_out("delete_me", 3 );
    }

    return 1;
}

int do_foundall()
{
    object me = this_player(), ob = this_object(), *temp_obj_list, temp_obj;
    string *found_list_id;
    string msg, to_say;
    int i, award_score;

    if( !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waitting", me) )
        return notify_fail("你還忙着呢，有空了才幫人吧。\n");

    if( query("iii") == 5 )
    {
        msg = "劍";
        found_list_id = ({ "qt jian", "lq jian", "by jian", "bs jian",
            "yd jian", "hj jian", "nl jian", "xy jian", "dh jian", });
    }
    else
    {
        msg = "水晶";
        found_list_id = ({ "kf sj", "by sj", "ll sj", "yd sj",
                "gs sj", "fh sj","dh sj", });
    }

    message_vision(CYN"$N"NOR+CYN"衝着$n"NOR+CYN"興奮地説道：“我找齊那一套"+msg+"了！”\n"NOR, me, ob );

    if( query("found_all_sword") == "yes" || query("found_all_crystal") == "yes" )
    {
        command("haha");
        command("say “在下已經找齊這一套"+msg+"，有勞費心了。”");
        return 1;
    }

    // 判斷開始
    command( "oh2" );
    command( "say “快，讓我看看！”" );
    to_say = CYN"$N"NOR+CYN"細細數道：“我看看……";

    temp_obj_list = ({ });
    for( i=0; i<sizeof(found_list_id); i++ )
    {
        temp_obj = present( found_list_id[i] , me );
        if( !temp_obj ) break;
        if( i == 0 )
            to_say += temp_obj->name(1) + NOR+CYN;
        else to_say += "、"+ temp_obj->name(1) + NOR+CYN;
        temp_obj_list += ({ temp_obj });
    }
    to_say += "……”\n"NOR;

    message_vision( to_say, ob );
    if( sizeof( temp_obj_list ) != sizeof( found_list_id ) )
    {
        command( "shake" );
        command( "say “你身上所帶似乎並不齊全啊。”");
        return 1;
    }

    // 找齊了 :)
    // 把它們清理掉
    for( i = 0; i<sizeof( temp_obj_list ); i++ )
        destruct( temp_obj_list[i] );

    command("touch "+query("id", me));
    command("say “對，對，就是這些"+msg+"，太好了，我終於找齊它們了！”");
    command("say “無以為報，請接受我的一點心意吧！”");
    message_vision( CYN"$n"NOR+CYN"接過了這一套"+msg+"，接着伸掌在$N"NOR+CYN"臉前一晃。\n"NOR, me, ob);

    if( query("iii") == 5 )
        award_score = 400 + random(101);
    else award_score = 300 + random(101);
    addn_temp("hj_score", award_score, me);
    write(HIR"遊戲提示：你的得分增加了 "+award_score+" 點！\n");

    set( "found_all_sword", "yes" );
    set( "found_all_crystal", "yes" );

    if( query("found_sword") == "yes" || query("found_crystal") == "yes" )
    {
        set("all_found", 1);
        remove_call_out("delete_me");
        call_out("delete_me", 3 );
    }

    return 1;
}


// 回答失敗者，忙時 10 秒  未來得及回答者，若仍身處此地，忙時 20 秒
// 若已不見蹤跡（就是溜了之類的），重懲，忙時 30 秒。
int do_huida(string arg)
{
    object qxd,me=this_player();
    mapping data1,data2,data3,data4;
    string qt_name1,qt_name2,qt_name3,qt_name4,*qt_type,temp_type;
    int i,qt_temp1,qt_temp2,qt_temp3,qt_temp4, score_is;

    if( !me_ok(me) ) return 0;

    qxd = present("qixing deng",me);
    if(!qxd) return 0;

    if( !query("hj_quest_info1", qxd) || !query("hj_quest_info2", qxd) || 
       !query("hj_quest_info3", qxd) || !query("hj_quest_info4", qxd) )
        return 0;

    if( me->is_busy() || query_temp("hj_need_waitting", me) )
        return notify_fail("你還忙着呢，空閒點了再接受提問吧。\n");

    if( query("asking_for_id") && query("id", me) != query("asking_for_id") )
        return notify_fail(query("name")+"已經在問着"+query("asking_for_name")+"了，還是不要打擾的好。\n");

    if(!arg) return notify_fail("你要回答什麼？\n");

    if(!query("asking_for_id"))
    {
        if(arg!="好") return notify_fail("你若願意接受提問，就回答“好”吧！\n");

    // 若玩家在本輪遊戲裏，已把5個預設的問題都答對過了，將不再發放問題。
        message_vision("$N大聲説道：“好吧！你就儘管問我，看我知不知曉。”\n",me);
        if( sizeof(query_temp("hj_quest_answer", me)) >= 5 )
        {
            command("say “你所知武林之事甚多，看來非我之下。我又怎敢問你？”");
            command("smile");
            return 1;
        }

        remove_call_out("delete_me");
        set("asking_for_id",query("id", me));
        set("asking_for_name",query("name", me));
        set("asking","waiting");
        set("cannot_rdmove","yes");

        data1=query("hj_quest_info1", qxd);
        data2=query("hj_quest_info2", qxd);
        data3=query("hj_quest_info3", qxd);
        data4=query("hj_quest_info4", qxd);

        // 下面開始抽取問題類型

        qt_type = ({ "int","str","con","dex","balance" });
        // 悟性  膂力  根骨  身法  存款
        temp_type = qt_type[random(sizeof(qt_type))];
        // 防止玩家在本輪遊戲內重複回答問題
        for(i=0;i<sizeof(qt_type);i++)
        {
            if( query_temp("hj_quest_answer/"+temp_type, me) == "ok" )
                temp_type = qt_type[i];
            else break;
        }
        set("quest_type",temp_type);

        qt_name1 = data1["name"];
        qt_name2 = data2["name"];
        qt_name3 = data3["name"];
        qt_name4 = data4["name"];
        qt_temp1 = data1[temp_type];
        qt_temp2 = data2[temp_type];
        qt_temp3 = data3[temp_type];
        qt_temp4 = data4[temp_type];

        // 這裏我不知道LPC是否有 max 的函數，只好自己寫；幸好不太多數據
        if( qt_temp1>=qt_temp2 && qt_temp1>=qt_temp3 && qt_temp1>=qt_temp4 )
            set("the_answer",qt_name1);
        if( qt_temp2>=qt_temp1 && qt_temp2>=qt_temp3 && qt_temp2>=qt_temp4 )
            set("the_answer",qt_name2);
        if( qt_temp3>=qt_temp1 && qt_temp3>=qt_temp2 && qt_temp3>=qt_temp4 )
            set("the_answer",qt_name3);
        if( !query("the_answer") )
            set("the_answer",qt_name4);
        // 加入去掉顏色的句子，防止小BUG
        set("the_answer", delcolor( query("the_answer") ) );
        // 內部運作OK，告訴玩家去慢慢猜吧 :)
        command("nod");
        command("say “你是否聽過這幾個人？他們是 "+qt_name1+"、"+qt_name2+"、"+qt_name3+"和"+qt_name4+" 。”");
        switch(temp_type)
        {
            case "int":
            command("say “這其中一人，領悟之力奇高，因此過人一籌，終於了其心願，\n          成就大事。如此之人，當稱英雄！”");
            break;
            case "str":
            command("say “所謂英雄俠客，焉能有手無搏雞之力之人？這其中一人，\n          力大無窮，堪堪劈石開山，也該配稱英雄二字！”");
            break;
            case "con":
            command("say “人言道，吃得苦中苦，方為人上人。這其中一人，不但耐力\n          驚人，也是骨格精奇。如此之人，何愁不成大事，又有何不能稱之英雄？”");
            break;
            case "dex":
            command("say “自古英雄皆好漢，但這裏面卻有一位，卻非以武藝見長，乃是\n          天賦奇高，輕功過人，終闖出一片天地！如此之人，也該可稱英雄！”");
            break;
            case "balance":
            command("say “有言云：一文難倒英雄漢。這其中一位，富敵四方，接朋濟友，\n          雖無過人武藝，但又如何不能稱之英雄？”");
            break;
        }
        command("say “你若知曉他的名字，就回答(huida)予我罷！”");
        message_vision("$N似有所悟，一時間呆住了，竟似忘了應聲一般。\n",me);
        write(HIR"遊戲提示：你只有60秒的時間！快快回答！\n"NOR);
        remove_call_out("delete_me");
        call_out("delete_me",61);
        return 1;
    }
    // 加入強制去除多餘的空格的語句
    arg = replace_string( arg, " ", "" );
    arg = replace_string( arg, "　", "" ); // 連全角符號的“空白”也去掉。
    message_vision("$N想了想，説道：“這個人是"+arg+"！”\n",me);
    // 回答錯誤。
    if( arg != query("the_answer") )
    {
        set("asking","fail");
        remove_call_out("delete_me");
        command("sure "+query("id", me));
        command("say “你説得不對。這個人哪，他的名字是"+query("the_answer")+"！”");
        message_vision("$N十分失望地説道：“這人如此有名，你竟然不知道！你仔細想想吧！”\n",this_object());
        message_vision("$N慚愧之色立現於臉，頓時陷入了沉思中。\n",me);
        me->start_busy(10);
        set("asking_for_id","no");
        call_out("delete_me",1);
        return 1;
    }
    // 回答正確！玩家得到獎勵，並且設置值，本輪遊戲內若再遇上老人，不會再提這個問題。
    remove_call_out("delete_me");
    message_vision("$N摸了摸鬍子，説道：“不錯！想不到你也能知曉他的名字！”\n",this_object());
    command("say “你所知如此之廣，我有一物贈送予你。”");
    message_vision("老人説完，卻不見拿出些什麼來；只是突地把手往$N身上一拍！\n",me);
    message_vision("$N只覺得怪異莫名，卻似乎又覺得有些什麼變化……\n",me);
    set_temp("hj_quest_answer/"+query("quest_type"), "ok", me);
    if( query_temp("hj_score", me) )
    {
        score_is = 200 + random(101); // 最高可獲 300 點獎勵
        addn_temp("hj_score", score_is, me);
        write(HIR"遊戲提示：你的遊戲得分增加了 "+score_is+" 點！\n"NOR);
    }
    set("asking","ok");
    me->start_busy(1);
    call_out("delete_me",1);
    return 1;
}

// naihe 05-9-12 8:06 修改，lianli 成功時低忙時。
int do_lianli()
{
    object me=this_player();
    string id=query("id", me);
    int temp,power=query_temp("hj_game_mepower", me);

    if( !me_ok(me) ) return 0;

    if(!power) return 0;

    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return notify_fail("你還忙着呢，還是等空閒了，專心點來煉力吧！\n");

    if( query_temp("hj_hp", me)<power*2 )
        return notify_fail("你的氣息太弱，無法使力打人，又如何煉力？\n");

    if(query("last_id") && query("last_id") == id )
    {
        command("say “哎呀，我已經教過你了，你怎麼那麼愚笨哪？”");
        return 1;
    }
    message_vision("$N大喝一聲，使勁向着"+query("name")+"打出了一拳！\n",me);
    if( !random(3) )
    {
        me->start_busy(3+random(3));
        message_vision("只見$N用盡全力，卻似打到了銅牆鐵壁之上！$N頓時疼痛異常，感覺就似斷了手臂一般！\n",me);
        addn_temp("hj_hp", -power, me);
        message_vision(query("name")+"「呵呵」笑了笑，拍了拍$N的頭説道：“娃兒的力氣不對哪。”\n",me);
        addn("use_times", -1, this_object());
        if(query("use_times") <=0 )
        {
            remove_call_out("delete_me");
            call_out("delete_me",1);
        }
        return 1;

    }
    me->start_busy(1); // 煉力成功時只有1秒忙時。
    set("last_id",id);
    if(power<15)
    {
        message_vision("只見"+query("name")+"似是沒知覺般全數受下了！\n",me);
        command("pat "+id);
        command("say “娃兒力氣不行啊。來，我來教教你，要這般用力才對……”");
        temp=3+random(3);
    }
    else if(power<30)
    {
        message_vision("只聽得「嘭」的一聲，"+query("name")+"受下了這拳，但卻只是微微一震！\n",me);
        command("nod");
        command("say “娃兒還有點力氣。不過你用得不太對，我來教教你吧……”");
        temp=2+random(2);
    }
    else if(power<50)
    {
        message_vision("只聽得一聲重響，"+query("name")+"受下了這拳，登時往後退了一步！\n",me);
        command("consider");
        command("say “娃兒的力氣不小哇！不過這還能打得更好，來來來，我來告訴你……”");
        temp=1+random(2);
    }
    else
    {
        message_vision("只聽得"+query("name")+"悶哼一聲受下這拳，登時往後退了好幾步！\n",me);
        command("thumb "+id);
        command("say “娃兒的力氣很不錯哇！老頭兒我告訴你這最後一點要領吧！……”");
        temp=1;
    }
    command("whisper "+id+" 這樣這樣，這樣這樣……明白了麼？");
    message_vision("$N覺得茅塞頓開，頓時覺得力量似乎立竿見影般上漲了許多！\n",me);
    addn_temp("hj_game_mepower", temp, me);
    addn("use_times", -1, this_object());
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_answer(string arg)
{
    object me = this_player();
    int award_score;

    if( !me_ok(me) ) return 0;

    if(!arg || (arg!="ok" && arg!="byebye" && arg!="here?"))
        return notify_fail("回答什麼？答應(ok)還是放棄(byebye)？或是找到了地方了(here?)？\n");

    if(arg == "ok")
    {
        if(query("following_name"))
        {
            if( query("id", me) == query("following_id") )
                write("你説了要帶她去了的。\n");
            else command("say “"+query("following_name")+"説了要帶我去了呀。”");
            return 1;
        }
        else
        {
            if( query("last_follow") == query("id", me) )
                return notify_fail("剛才你不是也説好嗎！騙小孩子，不要臉～～\n");

            set("following_name",query("name", me));
            set("following_id",query("id", me));
            set("cannot_rdmove","yes");
            message_vision("$N對着"+query("name")+"大聲説道：“我帶你去吧！”\n",me);
            command("nod2 "+query("id", me));
            command("say “我要去的是「"+chinese_number(query("go_where"))+"」啊。”");
            command("say “如果到了就告訴我(answer here?)，真是很感謝你啊！”");
            remove_call_out("delete_me");
            call_out("delete_me",180); // 這個任務很簡單啦，3分鐘有夠多的了
            command("follow "+query("id", me));
            return 1;
        }
    }

    if(arg == "byebye")
    {
        if(!query("following_id")) return notify_fail("還沒答應她呢，就説拜拜！\n");
        if( query("id", me) != query("following_id") )
            return notify_fail("又不是你答應帶她去的，你愛走便走麼。\n");

        message_vision("$N撓了撓腦袋，對着"+query("name")+"説道：“我帶不了你去了，就這樣吧，我走了。”\n",me);
        delete("following_name");
        delete("following_id");
        command(":( "+query("id", me));
        set("last_follow",query("id", me));
        command("follow none");
        award_score = 5 + random(6);
        addn_temp("hj_score", -award_score, me);
        if( query_temp("hj_score", me)<0 )
            set_temp("hj_score", 0, me);
        // 放棄答應的事情，將減少遊戲得分。不過這還算是好的，起碼明確表示放棄。將減少最多10點的得分；
        // 若是半途不見了、不管她之類的，那麼，時限到了之後，將減少最多50點的得分。
        write("你心裏感到一絲內疚！\n"HIR"遊戲提示：你的得分減少了 "+award_score+" 點。\n"NOR);
        delete("cannot_rdmove");
        remove_call_out("random_move");
        call_out("random_move",1);
        remove_call_out("delete_me");
        addn("use_times",-1);
        if(query("use_times") < 1)
            call_out("delete_me",1);
        else call_out("delete_me",30+random(31));
        return 1;
    }
    if(arg == "here?")
    {
        if( !query("following_id") || query("following_id") != query("id", me) || !query("go_where") )
            return 0;
        if( query("room_mark", environment(this_player())) != query("go_where") )
            return notify_fail(query("name")+"搖了搖頭，説道：“好像不是這裏啊。”\n");

        message_vision("$N向"+query("name")+"問道：“你是不是要來這裏？”\n",me);
        command("jump");
        command("say “是啊！真的很謝謝你！”");
        set("go_where","ok");
        award_score = 50 + random(31);
        // 最高可獲得 80 分的獎勵！很不錯啦。
        write("你幫助了別人，覺得愉快極了。\n"HIR"遊戲提示：你的得分增加了 "+award_score+" 點！\n"NOR);
        addn_temp("hj_score", award_score, me);
        remove_call_out("delete_me");
        call_out("delete_me",1);
        return 1;
    }
    return 1;
}


// naihe 05-9-12 8:09 glist 時為什麼要 cmd(say) ? 別人無緣無故就被 flood ，鬱悶。
int do_glist()
{
    object me=this_player();
    int i,iii;
    string *lists;
    string *for_debug;
    string go_on="no";

    if( !me_ok(me) ) return 0;
    lists = keys(list_temp);
    for_debug= keys(all_values);
    write("----[ 共有以下共"+chinese_number(sizeof(lists))+"件 "+HIG+query("sell_this_time")+NOR+" 物品出售：]----\n\n");

    // 費盡心機，即學即用（之前什麼叫映射我都不懂哎）
    // 寫了個除了負擔似乎比較大之外，還算自認為完美的防止bug判斷流程
    // yeah 這下不怕了，obj_copy.h 裏的映射變量亂改都沒問題！哈哈哈
    // 8:29 02-10-30
    for(i=0;i< sizeof(lists);i++)
    {
        for(iii=0;iii<sizeof(for_debug);iii++)
        {
            go_on="no";
            if(lists[i] != for_debug[iii]) continue;
            go_on="yes";
            break;
        }
        if(go_on == "yes")
            printf("%-10s( %-4s )     價格： %-30d\n",list_temp[lists[i]],lists[i],all_values[lists[i]]);
    }
    // 這裏的 對齊 終於弄好啦，呵呵呵 太笨，以為是 (%-4)s 的，弄死都弄不好！ papaya
    write("\n----[ 用遊戲積分購買貨品，並且需要一個寶石才能買一件  指令：gmai 物品id ]----\n");
    return 1;
}

// naihe 05-9-12 8:15 gmai 時偶爾讓NPC“無端端”地 say 出一句話來，除了購買時的玩家，別人會感到迷惑滴~~
int do_gmai(string arg)
{
    object money,gem,goods,me=this_player();  // goods  n.商品;貨物
    string goods_name,have_gem="yes";
    int temp_set,temp_value;

    if( !me_ok(me) ) return 0;

    if( query("use_times") <= 0) return 0;

    if(!arg) return notify_fail("你要買什麼東西？\n");


    if(sscanf(arg, "%s ok", goods_name) )
        have_gem="no";
    else goods_name = arg;

    if(have_gem == "yes")
    {
        gem = present("red baoshi",me);
        if(!gem) gem = present("blue baoshi",me);
        if(!gem) gem = present("green baoshi",me);
        if(!gem)
        {
            return notify_fail( "你沒有寶石，如果你確實要買，價錢可得加倍。 <gmai 物品id ok>\n");
            return 1;
        }
    }

    if(!list_temp[goods_name] || !all_dir[goods_name] ||
       !all_set[goods_name] || !all_values[goods_name] )
        return notify_fail("沒有這個東西賣。\n");

    temp_value = all_values[goods_name];
    if(have_gem == "no") temp_value += temp_value;
    if( !query_temp("hj_score", me) || query_temp("hj_score", me) <= temp_value )
        return notify_fail("你沒有足夠的遊戲得分，不能夠購買它。\n");
    goods=new(__DIR__+all_dir[goods_name]);
    if( all_set[goods_name] == 111) temp_set = 0;
    else temp_set = all_set[goods_name];
    goods->setme( temp_set );
    goods->move(me);
    addn_temp("hj_score", -temp_value, me);
    if(have_gem == "yes")
    {
        message_vision(sprintf("$N掏出一%s%s，向%s買下了一%s%s。\n",
            query("unit", gem),query("name", gem),query("name"),
            query("unit", goods),query("name", goods)),
            me
        );
        destruct(gem);
    }
    else
    {
        message_vision(sprintf("$N向%s買下了一%s%s。\n",
            query("name"),query("unit", goods),query("name", goods)),
            me
        );
    }
    addn("use_times", -1, this_object());
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}
