//                標準描述長度示例                                   |
// 幻境新添 NPC，支持玩家之間進行交易的指令
// by naihe  2003-11-04  於茂名
// naihe 05-9-1 16:04 debug, 購買時居然不給錢給委託者，煩躁

#include <ansi.h>
#include "errs_func.h"
// 裏面有個 errs() 代替 notify_fail() ，即 write(msg), return 1;

inherit NPC;

#include "hj_settings/room_amount_hj.h"
#define     MY_ROOM_MARK        HJ_ROOM_AMOUNT
// 此NPC僅出現在 HJ 密林東南方角落處才有效
#include "zj_lm_tarder_prefunc.h"



#define        MAX_DS_AMOUNT        50
        // 最大同時 代售 數量
#define        MAX_DS_AMOUNT_ME     10
        // 最大個人同時代售數量
#define        SXF                  1
        // 手續費嘍

object *get_goods_list( object who );
void new_goods_in( string id );


void create()
{
    set_name( "代售商", ({ "daishou shang", "shang" }) );
    set("nickname", HIY"童叟皆欺 絕不公平"NOR );

    set("long", "這是一個專做代售生意的商人，幻境裏勇士們之間的交易都是到這裏來進行的。

代售貨品：    "HIY"(daishou 貨品ID #價格)"NOR"
取回貨品：    "HIY"(quhui ID)"NOR"
查看貨品列表："HIY"(list)"NOR"
查看求購信息："HIY"(list qg)"NOR"
發佈求購信息："HIY"(qiugou ID)"NOR"
購買貨品：    "HIY"(goumai ID)"NOR"

代售貨品、發佈求購信息都需要"HIR"手續費 "+SXF+" 點"NOR"（以你的幻境得分兑現）。
代售貨品時，如果原物主已離開幻境或已死亡，將會取消代售，貨品將扔在本地。
發佈求購信息後，將於半小時後清除；或在此期間若有該ID的新貨到來，將在通知後清除。\n\n");

    set("gender","男性");
    set("age",45);
    set("per",16);
    set("attitude","friendly");
    set("no_refresh",1);
    set("hj_game/npc","trader");

    setup();

    remove_call_out("checking");
    call_out("checking", 1);  // 檢查貨品有效性

    remove_call_out("me_do_ads");
    call_out("me_do_ads", 1 ); // 發佈廣告什麼的
}

void init()
{
    add_action("do_daishou", "daishou");
    add_action("do_goumai", "goumai");
    add_action("do_quhui", "quhui");
    add_action("do_list", "list");
    add_action("do_qiugou", "qiugou");
}

// 這個文件裏許多描述都不用  message() ，是不想對其他人造成太多的騷擾



// 獲得有效的貨品列表
// 無效的，當即處理
object *get_goods_list( object who )
{
    object *temp, *ok_goods, *bad_goods, t, me, env;
    int i;

    temp = all_inventory(this_object());
    if( !temp || sizeof( temp ) < 1 )
        return 0;

    if( !who ) who = this_object();

    ok_goods = ({ });
    bad_goods = ({ });

    for( i=0;i<sizeof(temp);i++)
    {
        t = temp[i];
        // 非hj內物件，立刻刪除
        if( !query("hj_game/obj", t) )
        {
            destruct( t );
            continue;
        }

        // 發生意外的 hj 內物件，準備丟下
        if( !query("sell_value", t) || !query("seller_mark", t) || !query("sell_id", t) )
        {
            bad_goods += ({ t });
            continue;
        }

        // 售賣者已離開 hj (退出、死亡)，準備丟下
        // 這是為了避免有人揀了別人的寶物，又故意放到這裏賣高價
        // 這時候，被揀了寶物的人可以選擇PK該人，即可得回寶物！哈哈哈
        me=query("seller", t);
        if( !me || !me_ok( me )
           || !environment(me) || !query("room_mark", environment(me) )
           || query_temp("this_time_mark", me) != query("seller_mark", t) )
        {
            bad_goods += ({ t });
            continue;
        }

        // 好的，此物件OK
        if( who == this_object() || me == who )
            ok_goods += ({ t });
    }

    // 如果有要丟下的東西
    if( bad_goods && sizeof(bad_goods) )
    {
        env = environment(this_object());
        for(i=0;i<sizeof( bad_goods);i++)
        {
            message_vision( sprintf("$N扔下一%s%s，口裏嘀咕了一句什麼。\n",
                query("unit", bad_goods[i]),query("name", bad_goods[i])),
                    this_object() );
            bad_goods[i]->move( env );
        }
    }

    if( !ok_goods || sizeof( ok_goods ) < 1 )
        return 0;
    return ok_goods;
}

int do_daishou( string arg )
{
    object me = this_player(), ob = this_object(), g, *temp;
    int value;
    string g_id, *no_sell_list;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙着呢。\n");

    // 先判斷夠不夠錢給手續費，不夠則免了一系列判斷。
    // 雖然這個位置不該判斷手續費在先
    if( query_temp("hj_score", me)<SXF+1)//這個+1可別改了
        return errs("你這個窮光蛋，手續費都給不起，難道還想要我幫你白做事？！\n");

    if( !arg || sscanf( arg, "%s #%d", g_id, value ) != 2 )
        return errs("你要代售什麼貨品(daishou 貨品ID #價格)？例如： daishou xy jian #10\n");

    if( value<10 ) return errs("這東西賣那麼便宜，還不夠賺回手續費，還是省省吧。\n");
    if( value > 1000 ) return errs("你這價錢太嚇人了，我這可不敢代着賣，免得沒人要，放着又佔地方。\n");

    g = present( g_id, me);
    if( !g ) return errs("你身上沒有這東西。\n");
    if( !query("hj_game/obj", g) )
        return errs(query("name", g)+"是什麼東西？我怎麼不認識？……\n");

    // 禁止售賣id列表
    no_sell_list = ({ "qixing deng", "shenren ling", "youling ling",  });

    if( member_array(query("id", g),no_sell_list) != -1 )
        return errs("這"+query("name", g)+"啊，不能賣。\n");

    if( query("hj_game/obj", g) == "other" && query("id", g) != "slguo" )
        return errs(query("name", g)+"？！這個東西可不好賣……\n");

    // 看看是否貨滿
    temp = get_goods_list( me );
    if( temp && sizeof( temp ) >= MAX_DS_AMOUNT_ME )
        return errs("你還有很多貨在我這裏呢，還是等賣掉一些了再説吧。\n");
    temp = get_goods_list( ob );
    if( temp && sizeof( temp ) >= MAX_DS_AMOUNT )
        return errs("我這裏的貨都快多得放不下了，還是等賣掉一些了再説吧。\n");


    // ok, 可為代售。
    addn_temp("hj_score", -SXF, me);
    g->move( ob );
    set("seller", me, g);
    set("sell_id",query("id",  me), g);
    set("sell_value", value, g);
    set("seller_mark",query_temp("this_time_mark",  me), g);
    set("new_goods_msg",({query("name", me),g->short(),sprintf("%d",value)}));
    set( "new_goods", g );

    message_vision(CYN"$N"NOR+CYN"拿出一"+query("unit", g)+query("name", g)+NOR+CYN"遞給了$n"NOR+CYN"，説道：“請幫忙賣掉這個，要賣\""+value+"\"這個價錢啊！”\n"NOR,me,ob);
    message_vision( CYN"$N"NOR+CYN"又拿出一點什麼塞給了$n"NOR+CYN"，説道：“這裏是小小意思，麻煩你了！”\n"NOR,me,ob);
    command("ok"+query("id", me));

    // 新貨品進倉，查找是否有求購該品的玩家，有就通知
    // 放到另一個函數里弄它。
    call_out("new_goods_in",3,query("id", g));

    me->start_busy(1);

    return 1;
}


// 取回代售貨品
int do_quhui( string arg )
{
    object g, me = this_player();

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙着呢。\n");

    if( !arg ) return errs("你要取回什麼東西？\n");

    // 清一遍先
    get_goods_list( this_object() );

    g = present( arg, this_object() );
    if( !g ) return errs("我這沒有這樣東西。\n");
    if( query("seller", g) != me)return errs("這"+query("name", g)+"不是你拿來代售的，想搶劫啊？\n");


    // ok.

    g->move(me);
    message_vision( sprintf( CYN"$N"NOR+CYN"對着$n"NOR+CYN"説道：“我想取回我的%s"NOR+CYN"。”\n$n"NOR+CYN"點了點頭，拿出一%s%s"NOR+CYN"遞給了$N"NOR+CYN"。\n"NOR, 
        query("name", g),query("unit", g),query("name", g)),me,this_object());

    me->start_busy(1);
    return 1;
}


// 購買貨品
// 判斷流程和 do_quhui 基本一樣。
int do_goumai( string arg )
{
    object g, me = this_player(), seller;
    int value;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙着呢。\n");

    if( !arg ) return errs("你要購買什麼東西？\n");

    // 看夠不夠基本的錢先，免得又拉一次 all_inv
    if( query_temp("hj_score", me)<10 )
        return errs("窮鬼，攢點錢再來吧。\n");

    // 清一遍先。此時將把不合條件的都清掉
    get_goods_list( this_object() );

    g = present( arg, this_object() );
    if( !g ) return errs("我這沒有這樣東西。\n");
    if( query("seller", g) == me)return errs("這"+query("name", g)+"是你拿來代售的，你是要取回嗎？(quhui)\n");

    value=query("sell_value", g);
    if( value < 10 )
        value = 10;
    if( query_temp("hj_score", me)<value )
        return errs("這個啊……你好像買不起。\n");

    // ok.
    addn_temp("hj_score", -value, me);
    g->move(me);
    message_vision( sprintf( CYN"$N"NOR+CYN"對着$n"NOR+CYN"説道：“我想買個%s"NOR+CYN"。”\n$n"NOR+CYN"點了點頭，拿出一%s%s"NOR+CYN"遞給了$N"NOR+CYN"。\n"NOR, 
        query("name", g),query("unit", g),query("name", g)),me,this_object());
    me->start_busy(1);
    if( !(seller=query("seller", g) )
      || !me_ok(seller)
       || query_temp("this_time_mark", seller) != query("seller_mark", g )
    )
        return 1;
    if( environment(seller) == environment(this_object() ) )
        message_vision( CYN +query("name")+NOR+CYN"對着$N"NOR+CYN"説道："
            "“嘿，你上次寄售的"+query("name", g)+NOR+CYN"賣出去了，這裏是得到的收入。”\n"NOR,seller);
    else
        message_vision( CYN"只見一個"+query("name")+NOR+CYN"匆匆走了過來，對着$N"
            NOR+CYN"説道：“你上次寄售的"+query("name", g)+NOR+CYN"賣出去了，這裏是得到的收入。”\n"
            +query("name")+NOR+CYN"説完，又匆匆地離開了。\n"NOR,  seller);
    tell_object( seller, "你得到了 "+value+" 點積分。\n");
    addn_temp("hj_score", value, seller);
    return 1;
}

int do_list( string arg )
{
    object me = this_player(), ob = this_object(), *list, who;
    int i, j;
    string msg, *key, *kkk;
    mapping qg_list;


    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙着呢。\n");

    if( !arg ) who = ob;
    else
    {
        if( arg != "qg" )
        {
            if( arg == "me")arg=query("id", me);
            who = find_player( arg );
        }
    }

/* 求購信息設置格式
    set("qg_list", ([
        "tmxk yyf" : ({ "naihe", "zhu", "haha", "money" }),
        "dh jian" : ({ "yes" }),
        "test" : 0,
    ]) );
*/

    if( !who )
    {
        if( arg!= "qg" ) return errs( arg+" 沒有任何貨品在我這裏代售。\n");

        qg_list = query("qg_list");
        if( !qg_list || sizeof(qg_list) < 1 )
            return errs("現在沒有任何求購貨品的信息。\n");

        msg = "現在有如下求購信息：\n";
        key = keys(qg_list);
        for(i=0;i<sizeof(key);i++)
        {
            kkk = qg_list[key[i]];
            if( kkk && sizeof(kkk) )
            {
                msg += sprintf( "\n(%s) 有求購者如下：", key[i] );
                for(j=0;j<sizeof(kkk);j++)
                    msg += sprintf( "    %s", kkk[j] );
            }
        }
        msg += "\n";
        me->start_busy(1);
        me->start_more( msg );
        return 1;
    }

    list = get_goods_list( who );
    if( !list || sizeof(list) < 1 )
    {
        if( who == ob )
            return errs("現在沒有任何貨品代售。\n");
        else return errs( arg+" 沒有任何貨品在我這裏代售。\n");
    }

    if( who == ob )
        msg = "我這裏現有這些貨品代售：\n\n";
    else msg = "我這裏現有這些貨品是 "+arg+" 委託代售的：\n\n";

    for(i=0;i<sizeof(list);i++)
    {
        msg += sprintf( "%-40s  售價：%4d    %-20s  出售者：%s\n",
            query("name", list[i])+"("+query("id", list[i])+")",
            query("sell_value", list[i]),
            query("use_times", list[i] )
                ?"剩餘使用次數"+query("use_times", list[i])+""
                : "特別物品",
            query("sell_id", list[i]));
    }
    me->start_busy( 1 );
    me->start_more( msg );
    return 1;
}


// 發佈求購信息
int do_qiugou( string arg )
{
    object me = this_player(), *goods_list;
    string id = query("id", me), *temp;
    int i;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙着呢。\n");

    if( !arg ) return errs("你要求購什麼物品？(qiugou 物品ID)\n");

    if( query_temp("hj_score", me)<SXF+1 )
        return errs("你這個窮光蛋，手續費都給不起，難道還想要我幫你白做事？！\n");

    temp = query( "qg_list/" + arg );
    if( temp && sizeof(temp) )
    {
        if( member_array( id, temp ) != -1 )
            return errs("你的事我會留心的了，一有消息我立刻通知你！\n");
        temp += ({ id });
        set( "qg_list/"+arg, temp );
    }
    else set( "qg_list/" + arg, ({ id }) );

    addn_temp("hj_score", -SXF, me);

    message_vision( CYN"$N"NOR+CYN"拿出一點什麼塞給了$n"NOR+CYN"，説道：“我急需 \""+arg+"\" 這個貨，如果有消息請儘快通知我！”\n"NOR, me, this_object() );
    command( "nod2 "+id );
    command( "say “當然當然，請放心，一有貨到，立刻通知！”");

    call_out("delete_msg", 1800, arg, id); // 半小時後刪除此求購信息
    me->start_busy(1);


    // 收了錢再查是不是有現貨
    goods_list = get_goods_list( this_object() );
    if( goods_list && sizeof( goods_list ) )
    {
        for( i=0;i<sizeof( goods_list );i++ )
        {
            if( query("id", goods_list[i]) == arg )
            {
                command("say “喲……這個我這裏好像有現貨，你要不要看看？(list)”");
                break;
            }
        }
    }
    return 1;
}


// 半小時內自動清除求購信息
void delete_msg( string qg_id, string who_id )
{
    string *list;
    if( !qg_id || !who_id ) return;
    list = query("qg_list/"+qg_id );
    if( !list || sizeof(list) < 1 || member_array( who_id, list) == -1 ) return;
    list -= ({ who_id });
    if( !list || !sizeof(list) )
    {
        delete( "qg_list/"+qg_id );
        return;
    }
    set("qg_list/"+qg_id, list );
}


// 新貨進倉，通知曾求購的玩家
void new_goods_in( string id )
{
    int i;
    string *ids;
    object who;

    ids = query("qg_list/"+id);
    if( !ids || sizeof(ids) < 1 ) return;
    // 沒有此物品的求購信息

    for(i=0;i<sizeof(ids);i++)
    {
        who = find_player( ids[i] );
        if( !who || !me_ok(who) ) continue;
        // 這裏有個漏洞，玩家在上一輪遊戲發佈的求購信息，也會通知
        // 不過也無所謂~ 給了錢的，這點好處也是應該滴~

        if( environment(who) == environment(this_object() ) )
            message_vision( CYN"$n"NOR+CYN"對着$N"NOR+CYN"説道：“嘿，你不是説要買"
                +id+"嗎，現在有貨了。”\n"NOR,who, this_object() );
        else
            message_vision( CYN"只見一個"+query("name")+NOR+CYN"匆匆走了過來，對着$N"
                NOR+CYN"説道：“你早些時候想買的"+id+"，現在有貨了！”\n"
                +query("name")+NOR+CYN"説完，又匆匆地離開了。\n"NOR, who);
    }

    delete( "qg_list/"+id );
}



// 廣告內容：新貨入倉，閒話
void me_do_ads()
{
    string *msg;
    string temp;
    int i;

    if( !environment( this_object() ) ) return;

    msg = ({
"這裏代售各類貨品，手續從簡，收費低廉哪！(daishou)",
"你急需求購什麼東西嗎？來我這發個消息，一有貨到，立刻通知！(qiugou)",
"如果你有什麼代售的東西又不想賣了，來我這取回就是，分文不取！(quhui)",
"來來來，走過路過不要錯過，這裏有好東西賣哪，快來看看吧！(list)",
"你有什麼東西不需要的，來看看別人是不是正在求購它，也好賣掉啊！(list qg)",
    });


    // 新貨信息
    if( query("new_goods") && environment( query("new_goods") ) == this_object() )
    {
        temp = query("new_goods_msg");
        if( temp && sizeof(temp) == 3 )
        {
            i=3;  // 讓新貨消息發佈的頻率高些
            while(i--) 
            msg += ({ sprintf( "現在有%s委託的最新貨品%s"NOR+CYN"，僅售 %s 點，快來看看啦！",
                temp[0], temp[1], temp[2] ) });
        }
    }

    message_vision(CYN"$N"NOR+CYN"説道：“"+msg[random(sizeof(msg))]+"”\n"NOR,this_object());

    remove_call_out("me_do_ads");
    call_out("me_do_ads", 30 );
}


// 每3鍾例行檢查一次物品有效性
void checking()
{
    get_goods_list( this_object() );
    remove_call_out("checking");
    call_out("checking", 180);
}
