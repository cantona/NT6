//                標準描述長度示例                                   |
// 幻境新添 NPC，鑄劍師
// by naihe  2003-11-05  于茂名
// 寶石的要求太高，降低點 05-9-1 14:43

#include <ansi.h>
#include <errs_func.h>
// 裡面有個 errs() 代替 notify_fail() ，即 write(msg), return 1;
inherit NPC;


#include "hj_settings/room_amount_hj.h"
#define        MY_ROOM_MARK        10
        // 此NPC僅出現在 HJ 密林東北方角落處才有效
#include "zj_lm_tarder_prefunc.h"


#define        SXF            20
        // 價格，即手續費

void create()
{
    set_name( "鑄劍師", ({ "zhujian shi", "shi" }) );
    set("nickname", HIW"鏽劍生輝 斷刃復回"NOR );

    set("long", "這是一位手藝精湛的鑄劍師，專接改造各類劍器的生意。
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    將某劍器改成 "GRN"青銅之劍"NOR"： <zj qtj 劍的ID>
    將某劍器改成 "HIW"白銀之劍"NOR"： <zj byj 劍的ID>
    將某劍器改成 "HIY"黃金之劍"NOR"： <zj hjj 劍的ID>
    將某劍器改成 "HIW"靈氣之劍"NOR"： <zj lqj 劍的ID>
    將某劍器改成 "HIM"盈動之劍"NOR"： <zj ydj 劍的ID>
    將某劍器改成 "HIY"耐力之劍"NOR"： <zj nlj 劍的ID>
    將某劍器改成 "HIW"迅隱之劍"NOR"： <zj xyj 劍的ID>
    將某劍器改成 "HIB"奪魂之劍"NOR"： <zj dhj 劍的ID>
    將某劍器改成 "HIR"必勝之劍"NOR"： <zj bsj 劍的ID>
需任意寶石 2 顆，及幻境得分 "+SXF+" 點 / 次。

修補某劍器（將之使用次數恢復）：<zj up 劍的ID>
需任意寶石 1 顆，幻境得分 "+(SXF/2)+" 點 / 次。
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    set("gender","男性");
    set("age",35);
    set("per",19);
    set("attitude","friendly");
    set("no_refresh",1);
    set("hj_game/npc","zhujian");

    setup();
}

void init()
{
    add_action("do_zhujian", ({ "zhujian", "zj" }) );
}

int do_zhujian( string arg )
{
    object me = this_player(), bs1, bs2, bs3, *all_mine, sword;
    string sword_id, type, *list, t;
    int i, set, score_need;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("你還忙著呢。\n");

    if( !arg || sscanf( arg, "%s %s", type, sword_id ) != 2 )
        return errs("你是想鑄劍嗎(look zhujian shi)？\n");

    if( query("working") )
        return errs("我這還有點工作沒完成，請稍等一會兒吧。\n");

    list = ({ "qtj","lqj","byj","ydj","hjj","nlj","xyj","dhj","bsj"});
    // 這裡的順序和 hj_obj_weapon.c 裡的順序是一樣的。

    set = member_array( type, list );
    if( set == -1 && type != "up" )
        return errs("我這裡可造不了 \""+type+"\" 這種劍，你還是另請高明吧。\n");

    sword = present( sword_id, me );
    if( !sword ) return errs("你可沒帶著這樣的劍，你以為我是那個什麼奈何啊，懂得憑空變把劍給你？\n");
    if( query("hj_game/obj", sword) != "sword" )
        return errs(query("name", sword)+"不是可以鑄造的劍器。\n");
    // 如果是“神力之劍”拿來改，那……哈哈哈，不認識

    score_need = (type == "up" ? SXF/2 : SXF);
    if( query_temp("hj_score", me)<score_need+1 )
        return errs("閣下身無分文，還是不要諸多要求的好，有什麼劍就將就著用吧。\n");

    // ok. up 劍
    if( type == "up" )
    {
        if( query("use_times", sword) >= query("real_use_times", sword) )
            return errs("這劍好好的，還鋒利得很呢，還是不必修了吧。\n");
        all_mine = all_inventory(me);
        // 玩家身上肯定有劍，不必進行 !all_mine 的判斷

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
            return errs("這……這需要三顆寶石，你好象不夠吧。\n");
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
            return errs("這需要一顆寶石，你好象沒有吧。\n");
        destruct( bs1 );
        // 全部OK，進行設置及描述等
        addn_temp("hj_score", -score_need, me);
        me->start_busy(1);
        set("use_times",query("real_use_times",  sword), sword);
        if( query("use_times", sword)<1)set("use_times", 1, sword);
        t = NOR+CYN;
        message_vision( sprintf(
            CYN"$N%s拿出一%s%s%s遞給了$n%s，說道：“麻煩你幫我修修這劍。”\n"
            "$N%s說罷，又拿出了一顆寶石，還夾了點什麼，一並塞給了$n%s。\n"
            "只見$n%s接過了劍，敲敲摸摸只弄了幾下，就把它遞給了$N%s。\n"
            "$n%s說道：“好啦，這劍已經修好了，保証好用。”\n"NOR,
                t,query("unit", sword),query("name", sword),t,t,
                t, t,
                t, t,
                t), me, this_object() );
        return 1;
    }
    // 那麼就是換劍嘍
    // 太爛的不行(使用了很多次的)
    if( query("use_times", sword)<query("real_use_times", sword)/2 )
        return errs("這劍刃口都卷了，你還是另請高明吧。\n");
    /*
    bs1 = present( "red baoshi", me );
    bs2 = present( "green baoshi", me );
    bs3 = present( "blue baoshi", me );
    if( !bs1 || query("hj_game/obj", bs1) != "other"
       || !bs2 || query("hj_game/obj", bs2) != "other"
       || !bs3 || query("hj_game/obj", bs3) != "other"
    )
        return errs("這……這需要各色寶石各一顆，你好象不夠吧。\n");
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
        return errs("這需要兩顆寶石，你好象不夠吧。\n");
    destruct( bs1 );
    destruct( bs2 );
    // 那麼就OK嘍
    addn_temp("hj_score", -score_need, me);
    me->start_busy(1);
    t = NOR+CYN;
    /*
    message_vision( sprintf(
        CYN"$N%s拿出一%s%s%s遞給了$n%s，說道：“麻煩你，我想把它改成 \"%s\" 。”\n"
        "$N%s說罷，又拿出了"HIR"紅%s、"HIG"綠%s、"HIB"藍%s共三顆寶石，還夾了點什麼，一並塞給了$n%s。\n"
        "$n%s接過了劍，說道：“好罷，稍後我就送去給你，放心即可。”\n"NOR,
            t,query("unit", sword),query("name", sword),t,t,type,
            t, t, t, t, t,
            t, t), me, this_object() );
    */
    message_vision( sprintf(
        CYN"$N%s拿出一%s%s%s遞給了$n%s，說道：“麻煩你，我想把它改成 \"%s\" 。”\n"
        "$N%s說罷，又拿出了兩顆寶石，還夾了點什麼，一並塞給了$n%s。\n"
        "$n%s接過了劍，說道：“好罷，稍後我就送去給你，放心即可。”\n"NOR,
            t,query("unit", sword),query("name", sword),t,t,type,
            t, t, t, t, t,
            t, t), me, this_object() );
    destruct(sword);
    set("working", 1);
    remove_call_out( "send_sword" );
    call_out("send_sword",5+random(11),me,query_temp("this_time_mark", me),set);
    // 稍微等待一下
    return 1;
}

void send_sword( object me, int me_mark, int set )
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
        CYN"$n%s把一%s%s%s遞給了$N%s，說道：“你要改的劍已經改好了，保証好用。”\n"NOR,
        t,query("unit", s),query("name", s),t,t),me,this_object());
    else message_vision( sprintf(
        CYN"只見一位%s%s匆匆地走了過來，拿出一%s%s%s交給了$N%s。\n"
        "%s%s說道：“你要改的劍已經改好了，保証好用。”說完，%s%s又匆匆地離開了。\n"NOR,
        query("name"),t,query("unit", s),query("name", s),t,t,
        query("name"), t, query("name"), t ), me );

    s->move( me );
}