//                標準描述長度示例                                   |
// 幻境內物品  遊戲工具類型
// by naihe  2002-10-24 ~ 25  于茂名
// 改善一下 fx, dx, xr 的效力 05-8-31 10:16

#include <ansi.h>

inherit ITEM;

#include "hj_settings/obj_list.h"          // 具體定義的變量請參看該文件
#include "hj_settings/room_amount_hj.h"

string *names=({
    HIG"定向水晶"NOR,
    HIC"飛翔之石"NOR,
    YEL"脫離水晶"NOR,
    HIW"回歸之鏡"NOR,
    HIY"祈禱之石"NOR,
    HIM"召喚之盒"NOR,
    HIM"發呆之旗"NOR,
    HIM"驅逐之旗"NOR,
    HIG"尋人水晶"NOR,
    HIB"窺探水晶"NOR,
    HIW"定位之儀"NOR,
});

/************************************
 本來還有諸多的想法，但：
1、道具太多，玩家將無所適從
2、每次想到新的都要添加，何時才是個頭？
3、一些特強力的道具，可留待 幻境系列 第2集 裡寫！

by the way, 第2集的情節已想好幾個國度的構思了！
玩家將能夠進一步深入遊戲中去，繼續延續第1集裡
的故事！！！

並且，第2集裡將是以情節為主的內容！大家
拭目以待一個迷一般、史詩一般的情節吧！

YEAH~~   all by naihe 2002-10 ~ 11

終于未寫，唉。 naihe 14:04 03-10-15
**************************************/



string *ids=({
    "dx shuijing",
    "fx zhishi",
    "tl shuijing",
    "hg zhijing",
    "qd zhishi",
    "zh zhihe",
    "fd zhiqi",
    "qz zhiqi",
    "xr shuijing",
    "kt shuijing",
    "dw zhiyi",
});

string *ids2=({
    "shj",
    "shi",
    "shj",
    "jing",
    "shi",
    "he",
    "qi",
    "qi",
    "shj",
    "shj",
    "yi",
});

string *longs=({
    "這是一個定向水晶，用它你可以(dingxiang / dx)查得自己身在何處。\n",
    "這是一顆飛翔之石，用它你可以(feixiang / fx)瞬間飛翔到幻境裡的任何地方。\n",
    "這是一個脫離水晶，用它你可以(tuoli / tl)逃開怪物，隨機脫離去到別的地方。\n",
    "這是一面回歸之鏡，用它你可以(huigui / hg)立刻離開幻境，回到現實裡來（遊戲得分將保持）。\n",
    "這是一顆祈禱之石，用它你可以(qidao / qd)祈禱隨機寶物出現于自己所處之地。\n",
    "這是一個召喚之盒，用它你可以(zhaohuan / zh)召喚隨機精靈出現于自己所處之地。\n",
    "這是一面發呆之旗，用它你可以(fadai / fd)讓同一個地方的人發呆一會兒。\n",
    "這是一面驅逐之旗，用它你可以(quzhu / qz)讓某地不許除了你之外的有著幻境氣息的人停留。\n",
    "這是一顆尋人水晶，用它你可以(xunren / xr)尋找如你一樣的勇士們所處何方。\n",
    "這是一顆窺探水晶，用它你可以(kuitan / kt)窺探如你一樣的勇士們身上所帶何物。\n",
    "這是一個定位之儀，用它你可以(dingwei here / dw here)先定位，再快速返回該地點(dw back)。\n",
});

string *units=({
    "個",
    "顆",
    "個",
    "面",
    "顆",
    "個",
    "面",
    "面",
    "顆",
    "顆",
    "個",
});

int *times=({
    10+random(6),
    3+random(3),
    3,
    1,
    2+random(2),
    3+random(3),
    2+random(2),
    1,
    9,
    9,
    3,
});


// 程序優化，所有能否使用道具的判斷在此進行。
int can_use( string id, object me )
{
    if( !me || !id || query("id") != id ||
        !query_temp("huanjing", me) || query_temp("huanjing", me) != "start" || 
        !query_temp("hj_hp", me) || query_temp("hj_hp", me)<1 || 
        query("use_times") <= 0 || !environment(me) ||
        !query("room_mark", environment(me)) )

        return 0;

    return 1;
}

// 程序優化，這裡判斷 busy .
int hj_busy_now( object me )
{
    if( !me || me->is_busy() || query_temp("hj_need_waiting", me))return 1;
    return 0;
}

void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set( "iii" , iii );

    set_name(names[ iii ],({ ids[ iii ] , ids2[ iii ] }));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", units[ iii ]);
    set("value", 1);  // 該物件扔下後不會消失。

    set("use_times",times[ iii ] );
    set("hj_game/obj","tools");
    set("msg","你似乎忽地眼睛一花，地上不知怎麼的就多了一件物事。\n");
}


void create()
{
    setme( 99 );
    setup();
}

void init()
{
    switch( query("iii") )
    {
        case 0: add_action("do_dingxiang", ({ "dingxiang", "dx" }) ); break;
        case 1: add_action("do_feixiang", ({ "feixiang", "fx" }) ); break;
        case 2: add_action("do_tuoli", ({ "tuoli", "tl" }) ); break;
        case 3: add_action("do_huigui", ({ "huigui", "hg" }) ); break;
        case 4: add_action("do_qidao", ({ "qidao", "qd" }) ); break;
        case 5: add_action("do_zhaohuan", ({ "zhaohuan", "zh" }) ); break;
        case 6: add_action("do_fadai", ({ "fadai", "fd" }) ); break;
        case 7: add_action("do_quzhu", ({ "quzhu", "qz" }) ); break;
        case 8: add_action("do_xunren", ({ "xunren", "xr" }) ); break;
        case 9: add_action("do_kuitan", ({ "kuitan", "kt" }) ); break;
        case 10: add_action("do_dingwei", ({ "dingwei", "dw" }) ); break;
    }

    if(query("qzzq_host_is"))
    {
        remove_call_out("get_out_here");
        call_out("get_out_here",1);
    }
}

void delete_me()
{
    if( query("real_name") )
    {
        message_vision(query("real_name", this_object())+"靈氣已盡，「□」地一聲消失不見了。\n",this_object());
        delete("qzzq_now", environment());
    }
    else
        message_vision(query("name", this_object())+"靈氣已盡，「□」地一聲消失不見了。\n",this_object());
    destruct(this_object());
}

int do_dingxiang()
{
    object me = this_player(), ob = this_object(), rooms;
    int temp_mark;

    // 已優化的判斷句
    if( !can_use( "dx shuijing" , me ) )
        return 0;
    // 本道具不受 busy 限制。
    //if( hj_busy_now( me ) ) return notify_fail("你還有別的事情忙著呢！\n");
    rooms = (environment(me));
    if( rooms && temp_mark=query("room_mark", rooms) )
    {
        message_vision(CYN"$N"NOR+CYN"拿起"NOR"$n"NOR+CYN"凝神注視著。\n"NOR, me, ob );
        addn("use_times",-1);
        // 報假的幾率降低了。
        if( !random(5) )
        {
            temp_mark+= random(2) - random(2);
            if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT )
                temp_mark = 1+random( HJ_ROOM_AMOUNT );
        }
        write(query("name")+"裡隱約顯現著一個標記，似乎是 " + chinese_number(temp_mark) + " 。 \n");
    }
    else
        return notify_fail("此地並非幻境密林內。\n");
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_feixiang(string arg)
{
    object me = this_player(), ob = this_object(), rooms;
    int temp_mark;
    string goto_rooms;

    // 已優化的判斷句
    if( !can_use( "fx zhishi" , me ) )
        return 0;
    if ( !arg || !sscanf(arg, "%d",temp_mark) ) 
        return notify_fail("這裡的區域標記為 1 - "+HJ_ROOM_AMOUNT+" 。輸入你想要去的地方的標記吧……\n");
    if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT)
        return notify_fail("這裡的區域標記為 1 - "+HJ_ROOM_AMOUNT+" 。輸入你想要去的地方的標記吧……\n");
    if( hj_busy_now( me ) )
        return notify_fail("你還有別的事情忙著呢！\n");
    message_vision(CYN"$N"NOR+CYN"左手把$n"NOR+CYN"握在手心，右手伸出，指了一個方向。\n"NOR,me, ob);
    addn("use_times",-1);
    // 飛錯的幾率降低了。
    if( !random(5) )
    {
        temp_mark+= random(2) - random(2);
        if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT)
            temp_mark = 1+random(HJ_ROOM_AMOUNT);
    }
    goto_rooms = HJ_DIR +"hj_room"+ temp_mark;
    rooms = find_object(goto_rooms);
    if(!rooms)
        rooms = load_object(goto_rooms);
    message_vision(HIC"$N"HIC"騰空而起，往遠處飛去了。\n"NOR,me);
    me->move(rooms);
    message_vision(HIC"只見$N"HIC"從空中飄然而下，穩穩地落在地上。\n"NOR,me);
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_tuoli()
{
    object me = this_player(), ob = this_object(), rooms;
    string random_rooms;

    // 已優化的判斷句
    if( !can_use( "tl shuijing" , me ) )
        return 0;
    message_vision(CYN"$N"NOR+CYN"把$n"NOR+CYN"緊緊抓在手心裡高舉過頭，大聲叫道：“脫離此地！”\n"NOR,me, ob);
    addn("use_times",-1);
    random_rooms = HJ_DIR +"hj_room"+ (1+random(HJ_ROOM_AMOUNT));
    rooms = find_object(random_rooms);
    if(!rooms)
        rooms = load_object(random_rooms);
    message_vision(HIR"$N"HIR"身形一晃，隨即消失不見了。\n"NOR,me);
    me->move(rooms);
    message_vision(HIR"$N"HIR"突然出現在這裡，一副驚魂未定的樣子。\n"NOR,me);
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_huigui()
{
    object me = this_player(), ob = this_object(), rooms,qxd;

    // 已優化的判斷句
    if( !can_use( "hg zhijing" , me ) )
        return 0;
    if( hj_busy_now( me ) )
        return notify_fail("你還有別的事情忙著呢！\n");
    qxd = present( "qixing deng",me);
    if( !qxd || query("my_master", qxd) != me )
        return notify_fail("你身上沒有七星燈？……或者你不是它的主人？……\n請使用 quit 指令強行退出遊戲！\n");
    if( !query("can_quit_hj", qxd) )
        return notify_fail("你才剛進來遊戲沒多久，就要離開？\n");
    if( query("wait_over", qxd) == "yes" )
        return notify_fail("你的遊戲時間即將結束，不必使用"+query("name")+"了吧。\n");
    message_vision(CYN"$N"NOR+CYN"拿起"NOR"$n"NOR+CYN"高舉過頂，口裡叫道：“現實映現！”\n"NOR,me, ob);
    set("use_times",0);
    set("use_huigui", "yes", qxd);
    message_vision(WHT"只見一陣白霧不知從何處飄來，癒來癒濃……\n"NOR,me);
    remove_call_out("delete_me");
    call_out("delete_me",1);
    return 1;
}

int do_qidao()
{
    object ob = this_object(),me = this_player(),obj;
    string msg,*temp_list;

    if( !can_use( "qd zhishi", me ) )
        return 0;
    if( hj_busy_now( me ) )
        return notify_fail("你還有別的事情忙著呢！\n");
    message_vision(CYN"$N"NOR+CYN"雙手握起"NOR"$n"NOR+CYN"捧在心口，閉目喃喃說著什麼。\n"NOR,me, ob);
    addn("use_times",-1);
    if( !random(30) )  // 玩家將有更多的機會得到屬于自己的寶物組成部分
    {
        if( !query_temp("hj_game_find", me))return 1;
        temp_list=({"wait","wait"});
        switch(query_temp("hj_game_find", me) )
        {
            case "feng":
                temp_list=obj_list_feng; break;
            case "yu":
                temp_list=obj_list_yu; break;
            case "lei":
                temp_list=obj_list_lei; break;
            case "dian":
                temp_list=obj_list_dian; break;
        }
        if( temp_list[0] == "wait")
            return 1;
        obj=new( temp_list[0] );
        set("host_id",query("id",  me), obj);
        obj->setme( 1+random(2) );
        obj->move(environment(me));
        if( query("msg", obj))msg=query("msg", obj);
        else msg="忽然一小陣輕煙掠過……這裡似乎多了一些什麼。\n";
        tell_room(environment(me),msg);
    }
    else
    {
        obj=new( obj_list_obj[random(sizeof(obj_list_obj))] );
        obj->move(environment(me));
        if( query("msg", obj))msg=query("msg", obj);
        else msg="忽然一小陣輕煙掠過……這裡似乎多了一些什麼。\n";
        tell_room(environment(me),msg);
    }
    // busy 由 3秒降為 1秒。
    me->start_busy(1);
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_zhaohuan()
{
    object ob = this_object(),me = this_player(),obj;
    string msg,*temp_list;

    if( !can_use( "zh zhihe", me ) )
        return 0;
    if( hj_busy_now( me ) )
        return notify_fail("你還有別的事情忙著呢！\n");
    message_vision(CYN"$N"NOR+CYN"右手捧起"NOR"$n"NOR+CYN"放在身前，猛地喝了一聲：“精靈顯現！”\n"NOR,me, ob);
    addn("use_times", -1);
    //ob->set("use_times",0);  // 這裡不知為何有BUG，為了解決，附加這一句。
    // 已無BUG
    if( !random(30) )  // 玩家將有更多的機會得到屬于自己的寶物組成部分。這裡是NPC攜帶寶物。
    {
        if( !query_temp("hj_game_find", me))return 1;
        temp_list=({"wait","wait"});
        switch(query_temp("hj_game_find", me) )
        {
            case "feng":
                temp_list=obj_list_feng; break;
            case "yu":
                temp_list=obj_list_yu;break;
            case "lei":
                temp_list=obj_list_lei;    break;
            case "dian":
                temp_list=obj_list_dian;break;
        }
        if( temp_list[0] == "wait")
            return 1;
        obj=new( temp_list[1] );
        set("host_id",query("id",  me), obj);
        obj->move(environment(me));
        if( query("msg", obj) )
            msg=query("msg", obj);
        else
            msg="忽然一小陣輕煙掠過……這裡似乎多了一些什麼。\n";
        tell_room(environment(me),msg);
    }
    else
    {
        obj=new( obj_list_npc[random(sizeof(obj_list_npc))] );
        obj->move(environment(me));
        if( query("msg", obj) )
            msg=query("msg", obj);
        else
            msg="忽然一小陣輕煙掠過……這裡似乎多了一些什麼。\n";
        tell_room(environment(me),msg);
    }
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

void fadai( object target, int time )
{
    object srl;
    // 奪魂之技特殊技能體現之三(1)，有效抵抗發呆之旗
    if( query_temp("hj_special/sh", target) )
    {
        message_vision( HIB"只聽得$N"HIB"四周忽地響起一陣凄厲之聲，似是把$N"HIB"保護起來了一般。\n"
            "$N"HIB"哈哈一笑，精神奕奕，竟是對發呆之旗毫無所懼。\n"NOR, target);
    }
    else if( (srl=present( "shenren ling", target )) )
    {
        message_vision(CYN"$N"NOR+CYN"身上的"+query("name", srl)+NOR+CYN"突然發出一陣光芒，"
            +"似是把$N"NOR+CYN"保護起來了一般。\n"NOR, target );
    }
    // 臨時離開遊戲，保証其安全
    else if( present( "hj temp leave obj", target ) )
    {
        message_vision( CYN"$N"NOR+CYN"身形忽隱忽現，竟似並無實體一般，發呆之旗卻是毫無用處。\n"NOR, target );
    }
    else
    {
        message_vision(HIY"只見$N"HIY"忽地雙目發直，果然就是個呆子般模樣。\n"NOR,target);
        target->start_busy( target->query_busy() + time );
    }
}
int do_fadai(string arg)
{
    object *inv_here,target,me=this_player(),ob=this_object(), srl;
    int time,human_amount,i;

    if( !can_use( "fd zhiqi", me ) )
        return 0;
    // 不限制忙時
    //if( hj_busy_now( me ) )
        //return notify_fail("你還有別的事情忙著呢！\n");
    if(!arg)
        return notify_fail("你要讓誰發呆？格式：\n"
            "讓某人發呆<fadai"+query("id", me)+">\n"
            "讓這個地方的所有有氣息的人發呆 <fadai all> (需要消耗自身的氣息)\n");
    if( !query_temp("hj_game_mepower", me) )
        time=3;
    else
        time=5+random(query_temp("hj_game_mepower", me));
    if(time > 60)
        time = 60;
    if(time < 10)
        time = 10;
    if(arg != "all")
    {
        target = present(arg , environment( me ) );
        if(!target)
            return notify_fail("這裡沒有這個人。\n");
        if(!target->is_character())
            return notify_fail("這不是活物！\n");
        if( !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1 )
            return notify_fail(query("name", target)+"沒有幻境裡的氣息，無法對其進行攻擊。\n");
        if(!living(target))
            return notify_fail("這個遊戲裡必須是清醒的對手才能攻擊。\n");
        if( target == me )
            return notify_fail("讓自己發呆？沒必要吧……\n");
        message_vision(HIY"$N"HIY"舉起"NOR"$n"HIY"大聲叫道：“呆子出現！”\n"NOR,me, ob);
        fadai( target, time );
    }
    else
    {
        if( query_temp("hj_hp", me)<60 )
            return notify_fail("你的氣息不夠，使喚不了這個東西。\n");
        inv_here = all_inventory(environment(me));
        if(!inv_here || sizeof(inv_here) < 2)
            return notify_fail("這兒沒別的人，這可是個寶貝，還是省著點用吧。\n");
        for(i=0;i<sizeof(inv_here);i++)
        {
            if( query_temp("hj_hp", inv_here[i]) && 
                query_temp("hj_hp", inv_here[i])>0 && 
                inv_here[i] != me )
            human_amount++;
        }
        if( human_amount < 1 )
            return notify_fail("這兒沒別的人，這可是個寶貝，還是省著點用吧。\n");
        message_vision(HIY"$N"HIY"舉起"NOR"$n"HIY"聲嘶力竭般大聲叫喊道：“一堆呆子，快快出現！”\n"NOR,me, ob);
        for(i=0;i<sizeof(inv_here);i++)
        {
            if( query_temp("hj_hp", inv_here[i]) && 
                query_temp("hj_hp", inv_here[i])>0 && 
                inv_here[i] != me
            )
                fadai( inv_here[i], time );
        }
        addn_temp("hj_hp", -(25+random(26)), me);
        tell_object(me,"你大叫之後，覺得氣喘吁吁的。\n");
    }
    addn("use_times",-1);
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_quzhu()
{
    object env, me=this_player(), ob=this_object();
    if( !can_use( "qz zhiqi", me ) )
    {
        write("什麼？\n");
        return 1;
    }
    // 不受忙時限制。
    //if( hj_busy_now( me ) ) return notify_fail("你還有別的事情忙著呢！\n");
    env = environment(me);
    if( query("room_mark", env) == 1 )
        return notify_fail("你不能在這個地方插下驅逐之旗。\n");
    if( query("qzzq_now", env) )
    {
        write("這裡已經有人插下驅逐之旗了。\n");
        return 1;
    }
    set("qzzq_host_is",query("id", me));
    addn("use_times",-1);
    set("use_times",0); // 有bug噢，不加這句不行，怪事.
    set("real_name","插在地上的驅逐之旗");
    set("no_refresh", 1 );
    if( environment(this_object()) != me )
        message_vision(CYN"$N"NOR+CYN"把"NOR"$n"NOR+CYN"揀了起來，使勁地插到了地上！\n"NOR,me, ob);
    else
        message_vision(CYN"$N"NOR+CYN"從身上取出"NOR"$n"NOR+CYN"，使勁地插到了地上！\n"NOR,me, ob);
    message_vision(HIB"霎時間狂風大作，就連天空也暗了下來！\n"NOR,me);
    move( env );
    set_weight(6300000);
    set("qzzq_now", 1, env);
    ob->get_out_here();
    ob->set_name(HIM"　　　　　　　一面 驅逐之旗 插在地上　　　　　　　"NOR,({"　"}));
    remove_call_out("delete_me");
    call_out("delete_me",180+random(300));
    // 時間延長，由原來的 2-3 分鐘延長到 3-5 分鐘。
    return 1;
}

void get_out_here()
{
    object *inv_here,srl,random_rooms;
    string temp;
    int i;
    inv_here = all_inventory(environment(this_object()));
    for(i=0;i<sizeof(inv_here);i++)
    {
        if( query("id", inv_here[i]) == query("qzzq_host_is") )
            continue;
        if( !query_temp("hj_hp", inv_here[i]) )
            continue;
        srl = present("shenren ling" , inv_here[i] );
        if(srl)
        {
            message_vision( HIC+query("real_name")+""HIC"發出一陣耀眼光芒！……\n"
                +"卻見$N"HIC"身上的"+query("name", srl)+HIC
                +"也散出一陣光芒，似是保護圈般把$N"HIC"圍了起來！\n"NOR,
                inv_here[i] );
            continue;
        }
        // 玩家暫時離開，保護其角色的安全。
        if( present( "hj temp leave obj", inv_here[i] ) )
        {
            continue;
        }
        message_vision(HIC+query("real_name")+""HIC"發出一陣耀眼光芒！……只見$N"
            +HIC"身不由己地往外飛了出去！\n"NOR,inv_here[i]);
        if( query_temp("hj_flying", inv_here[i]) )
        {
            delete_temp("hj_flying", inv_here[i]);
            temp = HJ_DIR  +"hj_room"+ 1;
        }
        else
        {
            set_temp("hj_flying", 1, inv_here[i]);
            temp= HJ_DIR  + "hj_room" + ( 1+random(HJ_ROOM_AMOUNT) );
        }
        random_rooms=find_object( temp );
        if(!random_rooms)
            random_rooms=load_object( temp );
        inv_here[i]->move(random_rooms);
        message_vision("$N從半空中跌了下來，不知道是怎麼回事。\n",inv_here[i]);
    }
}

int do_xunren(string arg)
{
    object ob=this_object(),me=this_player(),target,rooms;
    int temp_mark;

    if( !can_use( "xr shuijing", me ) )
        return 0;
    // 不受忙時限制。
    //    if( hj_busy_now( me ) ) return notify_fail("你還有別的事情忙著呢！\n");
    if(!arg)
        return notify_fail("你要尋找什麼人？\n");
    if( arg == query("id", me) )
        return notify_fail("幻境裡雖然有些妖魔鬼怪，但你"+query("name", me)+"還是一個而已，沒有更多的了。\n");
    target = find_player(arg);
    if(!target)
        return notify_fail("現在並沒有這個玩家在線，莫要說在這裡了。\n");
    rooms = (environment(target));
    if( !rooms || !query("room_mark", rooms) )
        return notify_fail("幻境﹒密林裡並沒有這個玩家。\n");
    temp_mark=query("room_mark", rooms);
    message_vision(CYN"$N"NOR+CYN"拿起"NOR"$n"NOR+CYN"凝神注視著，似要從中看出什麼來。\n"NOR,me, ob);
    addn("use_times",-1);
    // 尋錯的幾率降低了。
    if( !random(5) )
    {
        temp_mark += random(2) - random(2);
        if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT )
            temp_mark = 1+random( HJ_ROOM_AMOUNT );
    }
    write(query("name")+"裡隱約顯現著出標記，似乎是 "+chinese_number(temp_mark)+" 。\n");
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_kuitan(string arg)
{
    object target,*inv,me=this_player();
    int i;
    string target_name;

    if( !can_use( "kt shuijing", me ) )
        return 0;
    // 不受忙時限制。
    //    if( hj_busy_now( me ) ) return notify_fail("你還有別的事情忙著呢！\n");
    if(!arg)
        return notify_fail("你要窺探誰的行囊？\n");
    target = present(arg , environment( me ) );
    if(!target)
        return notify_fail("這裡沒有這個人。\n");
    if(!target->is_character())
        return notify_fail("這不是活物！\n");
    if( query("hj_game/npc", target) )
        return notify_fail("這不是與你一樣的玩家勇士。\n");
    if( !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1 || 
       query_temp("huanjing", target) != "start" )
        return notify_fail(query("name", target)+"已沒有絲毫幻境裡的氣息，算了吧。\n");
    if(!living(target))
        return notify_fail("這個遊戲裡必須是清醒的對手才能進行操作。\n");
    inv = all_inventory(target);
    if(target == me)
        target_name="你";
    else
        target_name=query("name", target);
    tell_object(me,"你悄悄地拿起水晶，仔細地看著……\n");
    if( !inv || sizeof(inv)<1 )
        return notify_fail(target_name+"身上沒帶著任何東西。\n");
    for(i=0;i<sizeof(inv);i++)
    {
        if( query("hj_game/obj", inv[i]) && random(3) )
        {
            tell_object(me,sprintf("%s身上似乎帶有一%s%s。\n",
                target_name,query("unit", inv[i]),query("name", inv[i])));
        }
    }
    // 使用忙時取消，不再給對方提示。
    //     if( target != me) tell_object(target,HIB"你只覺得似乎有些異樣的眼光在探視著自己一般……\n"NOR);
    //    tell_object(me,"你盯著看久了，竟然覺得有些累似的。\n");
    //    me->start_busy(5+random(6));
    addn("use_times",-1);
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_dingwei( string arg )
{
    object me = this_player(), ob = this_object(), the_room;
    string room_name;

    if( !can_use( "dw zhiyi", me ) )
        return 0;
    if( hj_busy_now(me) )
        return notify_fail("你還忙著呢。\n");
    if( !arg || (arg != "here" && arg != "back") )
        return notify_fail("你要將這裡定位(dingwei here)還是要返回(dingwei back)之前定位的地點？\n");
    if( arg == "here" )
    {
        message_vision(CYN"$N"NOR+CYN"拿出$n"NOR+CYN"，做了一個標記。\n"NOR, me, ob );
        set("dingwei_"+query("id", me),query("room_mark", environment(me)));
        me->start_busy(1);
        return 1;
    }
    // 否則就是返回該地點
    if( !query("dingwei_"+query("id", me)) )
        return notify_fail("這"+query("name")+"沒有你做的定位標記，你想回到哪裡去？\n");
    room_name=HJ_DIR+"hj_room"+query("dingwei_"+query("id", me));
    the_room = find_object( room_name );
    if( !the_room )
        the_room = load_object( room_name );
    if( !the_room )
        return notify_fail("你先前定下的標記不知怎麼的消失了，回不去。\n");
    message_vision(CYN"$N"NOR+CYN"舉起$n"NOR+CYN"，大聲喝道：“去！”\n"NOR, me, ob);
    message_vision(HIW"$N"HIW"忽地身形一晃，消失不見了。\n"NOR, me);
    me->move( the_room );
    message_vision(HIW"$N"HIW"突然出現在這裡。\n"NOR, me );
    me->start_busy(1);
    addn( "use_times", -1 );
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}
