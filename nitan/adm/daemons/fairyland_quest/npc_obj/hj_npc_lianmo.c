//                標準描述長度示例                                   |
// 幻境新添 NPC，煉魔匠
// by naihe  2003-11-05  於茂名
// 寶石的要求太高，降低點 05-9-1 14:43

#include <ansi.h>
#include <errs_func.h>
// 裏面有個 errs() 代替 notify_fail() ，即 write(msg), return 1;
inherit NPC;

#include "hj_settings/room_amount_hj.h"
#define        MY_ROOM_MARK        HJ_ROOM_AMOUNT-9
        // 此NPC僅出現在 HJ 密林西南方角落處才有效
#include "zj_lm_tarder_prefunc.h"

#define        SXF            20
        // 價格，即手續費

void create()
{
    set_name( "煉魔匠", ({ "lianmo jiang", "jiang" }) );
    set("nickname", HIM"呼風喚雨 法力無窮"NOR );

    set("long", "這是一位魔力強大的煉魔匠，專接改造各類魔法水晶的生意。
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  將某魔法水晶改成 "HIW"狂風水晶"NOR"： <lm kfsj 水晶的ID>
  將某魔法水晶改成 "MAG"暴雨水晶"NOR"： <lm bysj 水晶的ID>
  將某魔法水晶改成 "HIC"落雷水晶"NOR"： <lm llsj 水晶的ID>
  將某魔法水晶改成 "HIG"引電水晶"NOR"： <lm ydsj 水晶的ID>
  將某魔法水晶改成 "YEL"滾石水晶"NOR"： <lm gssj 水晶的ID>
  將某魔法水晶改成 "RED"飛火水晶"NOR"： <lm fhsj 水晶的ID>
  將某魔法水晶改成 "BLU"奪魂水晶"NOR"： <lm dhsj 水晶的ID>
需任意寶石 2 顆，及幻境得分 "+SXF+" 點 / 次。

修補某魔法水晶（將之使用次數恢復）：<lm up 水晶的ID>
需任意寶石 1 顆，幻境得分 "+(SXF/2)+" 點 / 次。
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    set("gender","女性");
    set("age",91);
    set("per",11);
    set("attitude","friendly");
    set("no_refresh",1);
    set("hj_game/npc","lianmo");

    setup();
}

void init()
{
    add_action("do_lianmo", ({ "lianmo", "lm" }) );
}

// 該函數複製 zhujian shi 的，一些函數名懶得改了
// 而且又懶得做成 #include ，就這樣吧。
int do_lianmo( string arg )
{
    object me = this_player(), bs1, bs2, bs3, *all_mine, sword;
    string sword_id, type, *list, t;
    int i, set, score_need;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙着呢。\n");

    if( !arg || sscanf( arg, "%s %s", type, sword_id ) != 2 )
        return errs("你是想提煉魔法水晶嗎(look lianmo jiang)？\n");

    if( query("working") )
        return errs("我這還有點工作沒完成，請稍等一會兒吧。\n");

    list = ({ "kfsj","bysj","llsj","ydsj","gssj","fhsj","dhsj" });
    // 這裏的順序和 hj_obj_weapon.c 裏的順序是一樣的。

    set = member_array( type, list );
    if( set == -1 && type != "up" )
        return errs("咳…… \""+type+"\" 這種魔法水晶，我可是聽都沒聽過啊……\n");

    set += 9;
    // 配合 hj_obj_weapon.c 的設置。

    sword = present( sword_id, me );
    if( !sword ) return errs("你可沒帶着這樣的水晶，你以為我是那個什麼奈何啊，懂得憑空變給你？\n");
    if( query("hj_game/obj", sword) != "magic" )
        return errs(query("name", sword)+"不是可以提煉的魔法水晶。\n");
    // 如果是其他各類水晶……哈哈哈，也不認識

    score_need = (type == "up" ? SXF/2 : SXF);
    if( query_temp("hj_score", me)<score_need+1 )
        return errs("你身無分文，如何表示你的誠意呀？\n");
    // ok. up it.
    if( type == "up" )
    {
        if( query("use_times", sword) >= query("real_use_times", sword) )
            return errs("這水晶裏還充滿了魔力，還是不必提煉了吧。\n");

        all_mine = all_inventory(me);
        // 玩家身上肯定有sj，不必進行 !all_mine 的判斷
        /*
        for(i=0;i<sizeof(all_mine);i++)
        {
            // 任意寶石
            if( all_mine[i]->id("baoshi")
               && query("hj_game/obj", all_mine[i]) == "other" )
            {
                if( !bs1 ) bs1 = all_mine[i];
                else if( !bs2 ) bs2 = all_mine[i];
                else { bs3 = all_mine[i]; break; }
            }
        }
        if( !bs1 || !bs2 || !bs3 )
            return errs("這……這需要三顆寶石，你好像不夠吧。\n");
        destruct( bs1 );
        destruct( bs2 );
        destruct( bs3 );
        */
        // 改為任意寶石一顆即可
        for(i=sizeof(all_mine)-1; i>=0; i-- )
        {
            if( all_mine[i]->id("baoshi")
               && query("hj_game/obj", all_mine[i]) == "other"
            )
            {
                bs1 = all_mine[i];
                break;
            }
        }
        if( !bs1 )
            return errs("這需要一顆寶石，你好像沒有吧。\n");
        destruct( bs1 );
        // 全部OK，進行設置及描述等
        addn_temp("hj_score", -score_need, me);
        me->start_busy(1);
        set("use_times",query("real_use_times",  sword), sword);
        if( query("use_times", sword)<1)set("use_times", 1, sword);

        t = NOR+CYN;
        message_vision( sprintf(
            CYN"$N%s拿出一%s%s%s遞給了$n%s，説道：“麻煩你幫我煉煉這水晶。”\n"
            "$N%s説罷，又拿出了一顆寶石，還夾了點什麼，一併塞給了$n%s。\n"
            "只見$n%s接過了水晶，敲敲摸摸只弄了幾下，就把它遞給了$N%s。\n"
            "$n%s説道：“好啦，這水晶已經修好了，保證好用。”\n"NOR,
                t,query("unit", sword),query("name", sword),t,t,
                t, t,
                t, t,
                t), me, this_object() );
        return 1;
    }

    // 那麼就是換sj嘍
    // 太爛的不行(使用了很多次的)
    if( query("use_times", sword)<query("real_use_times", sword)/2 )
        return errs("這水晶的靈氣已經衰敗，你還是另請高明吧。\n");
    /*
    bs1 = present( "red baoshi", me );
    bs2 = present( "green baoshi", me );
    bs3 = present( "blue baoshi", me );
    if( !bs1 || query("hj_game/obj", bs1) != "other"
       || !bs2 || query("hj_game/obj", bs2) != "other"
       || !bs3 || query("hj_game/obj", bs3) != "other"
    )
        return errs("這……這需要各色寶石各一顆，你好像不夠吧。\n");
    destruct( bs1 );
    destruct( bs2 );
    destruct( bs3 );
    */
    // 改為任意2顆寶石
    all_mine = all_inventory(me);
    for(i=sizeof(all_mine)-1; i>=0; i-- )
    {
        if( all_mine[i]->id("baoshi")
             && query("hj_game/obj", all_mine[i]) == "other"
        )
        {
            if( !bs1 )
                bs1 = all_mine[i];
            else
            {
                bs2 = all_mine[i];
                break;
            }
        }
    }
    if( !bs1 || !bs2)
        return errs("這需要兩顆寶石，你好像不夠吧。\n");
    destruct( bs1 );
    destruct( bs2 );
    // 那麼就OK嘍
    addn_temp("hj_score", -score_need, me);
    me->start_busy(1);

    t = NOR+CYN;
    /*
    message_vision( sprintf(
        CYN"$N%s拿出一%s%s%s遞給了$n%s，説道：“麻煩你，我想把它改成 \"%s\" 。”\n"
        "$N%s説罷，又拿出了"HIR"紅%s、"HIG"綠%s、"HIB"藍%s共三顆寶石，還夾了點什麼，一併塞給了$n%s。\n"
        "$n%s接過了水晶，説道：“好罷，稍後我就送去給你，放心好啦……”\n"NOR,
            t,query("unit", sword),query("name", sword),t,t,type,
            t, t, t, t, t,
            t, t), me, this_object() );
    */
    message_vision( sprintf(
        CYN"$N%s拿出一%s%s%s遞給了$n%s，説道：“麻煩你，我想把它改成 \"%s\" 。”\n"
        "$N%s説罷，又拿出了兩顆寶石，還夾了點什麼，一併塞給了$n%s。\n"
        "$n%s接過了水晶，説道：“好罷，稍後我就送去給你，放心好啦……”\n"NOR,
            t,query("unit", sword),query("name", sword),t,t,type,
            t, t, t, t, t,
            t, t), me, this_object() );

    destruct(sword);
    set("working", 1);
    remove_call_out( "send_sj" );
    call_out("send_sj",5+random(11),me,query_temp("this_time_mark", me),set);
    // 稍微等待一下

    return 1;
}

void send_sj( object me, int me_mark, int set )
{
    object s;
    string t;

    set("working", 0);
    if( !me || !me_ok(me) || !me_mark || query_temp("this_time_mark", me) != me_mark )
        return;

    s = new( __DIR__"hj_obj_weapon" );
    s ->setme( set );
    t = NOR+CYN;

    if( environment(me) == environment(this_object()) )
        message_vision( sprintf(
        CYN"$n%s把一%s%s%s遞給了$N%s，説道：“你要改的水晶已經改好了，拿去用吧。”\n"NOR,
        t,query("unit", s),query("name", s),t,t),me,this_object());
    else message_vision( sprintf(
        CYN"只見一位%s%s匆匆地走了過來，拿出一%s%s%s交給了$N%s。\n"
        "%s%s説道：“你要改的水晶已經改好了，拿去用吧。”説完，%s%s又匆匆地離開了。\n"NOR,
        query("name"),t,query("unit", s),query("name", s),t,t,
        query("name"), t, query("name"), t ), me );

    s->move( me );
}