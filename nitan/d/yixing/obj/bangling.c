// /d/yixing/obj/bangling.c
// Last Modified by winder on Jul. 12 2002

#include <changle.h>
#define THE_BANGZHU BANGS"npc/bangzhu"

#include <ansi.h>
#include <localtime.h>

inherit ITEM;

#include "/d/yixing/doc/info_store.h" 

void create()
{
        set_name("幫令", ({ "bang ling", "ling" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是一塊幫會中常用的幫令。\n");
                set("value", 0);
                set("material", "wood");
                set("partyname", HIC"長樂幫"NOR);
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
        setup();
}

void init()
{
        add_action("do_collect", "collect");
        add_action("do_sign", "sign");
        add_action("do_find", "find");
        add_action("do_bargain", "bargain");
}

int do_find(string arg)
{
        object *obj, room;
        string file, region, fam, result;
        int i;
        mapping job;

        if( query("owner") != query("id", this_player()) )
        {
               write("你連自己的幫令都管不好，還是離開幫會吧。\n");
               return 1;
        }
        if( !stringp(fam=query("party/party_name", this_player())) )
        {
               write("你沒有加入幫會。\n");
               return 1;
        }
        if( arg == "score" )
        {
                write("你掙了" + chinese_number((int)query("changle/score")) + "點功勞點。\n");
                return 1;
        }
        if( arg != "job" )
        {
    return 0;
        }

        if( !mapp(job = query("changle/job")) )
        {
                write("你現在沒有被指派幫務。\n");
                return 1;
        }

        result = "你當前的幫務是";
        switch(job["type"]) {
        case "尋":
                result += "找" + job["name"]; 
                break;
        case "殺":
                result += "殺" + job["area"] + "的" + job["name"]; 
                break;
        case "攤費":
                result += "要" + job["name"] + "的攤費";
                break;
        case "截鏢":
                result += "截" + job["name"] + "的鏢";
                break;
        case "示威":
                result += "向" + job["name"] + "示威";
                break;
        case "送禮":
                result += "送禮給" + job["area"] + "的" + job["title"];
                break;
        case "護駕":
                result += "護送幫主至" + job["dest"];
                break;
        case "買賣":
                result += "將" + job["name"] + "賣個好價錢";
                break;
        case "伙計":
                result += "在天寶閣做伙計";
                break;
        default:
                write("你現在沒有被指派幫務。\n");
                return 1;
        }

        write(result + "。\n");
        return 1;     
}

int do_collect(string arg)
{
        object me = this_player();
        object victim, obj;
        int ap, dp, myexp, yourexp, bonus, record;
        mapping job;

        if( time() < (int)query("collect_time") + random(10) )
                return notify_fail("你剛向此人要過錢。\n");
        if( query("qi", me)<50 || query("jing", me)<50 )
                return notify_fail("你太累了，先歇會兒。\n");
        if( query("owner") != query("id", me) )
                return notify_fail("幫令豈能瞎用？\n");
        if( query("fam") != query("party/party_name", me) )
                return notify_fail("你已經不是此幫的人了。\n");
        if( !mapp(job = query("changle/job")) )
                return notify_fail("你現在沒有幫務纏身。\n");
        if( job["type"] != "攤費" )
                return notify_fail("你當前的幫務不是收攤費。\n");
        if( base_name(environment(me)) != job["place"] )
                return notify_fail("你還沒到" + job["name"] + "收什麼攤費？\n");
        if( !arg ) return notify_fail("你要向誰收括錢？\n");
        if( !(victim = present(arg, environment(me))) )
                return notify_fail("這兒沒有這個人。\n");
        if( victim->name() != job["boss"] )
                return notify_fail("你找錯人了。\n");
        if( !living(victim) )
                return notify_fail("你還是等此人醒來後再收括錢吧。\n");
        if( victim->is_busy() || victim->is_fighting() )
                return notify_fail("此人正忙著。\n");

        message_vision(HIR"\n$N向$n大聲吆喝道：我是" + (string)query("fam") + "來收攤費的，識時務的趕快給錢！！！\n"NOR, me, victim);

        me->receive_damage("qi", 20 + random(10));
        me->receive_damage("jing", 20 + random(10));

        set("collect_time", time());

        myexp=query("combat_exp", me);
        ap = (int)query("combat_exp") + myexp * 10;

        yourexp=query("combat_exp", victim);
        if( yourexp < 30000 ) yourexp = 30000;
        dp = yourexp * 30;
 
        if( random(ap + dp) < dp )
        {
                message_vision("$N大怒道：什麼" + (string)query("party/party_name") + "，還不快滾！！！\n", victim);
                return 1;
        }
        message_vision("$N對$n說道：" + RANK_D->query_respect(me) + "辛苦了，這一點攤費是小的該付的。\n", victim, me);
        message_vision("$N接著說道：" + RANK_D->query_respect(me) + "請放心，我馬上派人將錢送到貴幫！！！\n", victim);

        bonus = 1 + yourexp * 2 / (myexp + 10000);
        record = bonus + random(bonus);
        addn("combat_exp", record, me);
        log_file("test/BangJob",sprintf("%-10s于%-20s時因收攤費得%-5s經驗點\n",query("name", me),ctime(time()),chinese_number(record)));

        bonus /= 4;
        addn("shen", -bonus, me);
        addn("score", bonus);
        return 1;
}

int do_sign(string arg)
{
        object obj, room;
        object me = this_player();
        int bonus, record;
        mapping job;

        if( query("owner") != query("id", me) )
                return 0;
        if( (string)query("fam") !=
                query_temp("party/party_bname", me) )
                return 0;
        if( !arg || arg != "corpse" || !(obj = present(arg, environment(me))) )
                return 0;
        if( !mapp(job = query("job")) )
        {
                tell_object(me, "你現在沒有幫務。\n");
                return 1;
        }
        if( query("kill_by", obj) != me || 
                query("signed", obj) || 
                query("victim_name", obj) != job["name"] )
                return 0;

        set("signed", 1, obj);
        bonus=job["bonus"]*job["max"]/(1000+query("combat_exp", me));
        record = bonus + random(bonus);
        addn("combat_exp", record, me);
        log_file("test/BangJob",sprintf("%-10s于%-20s時殺%-10s得%-5s經驗點\n",query("name", me),ctime(time()),job["name"],chinese_number(record)));

        bonus = job["score"];
        addn("shen", -bonus, me);
        addn("score", bonus);

        message_vision("$N在屍體旁寫下“與" + (string)query("fam") + "為敵者殺！”幾個大字。\n", me);
        delete("job");
        return 1;
}

int do_bargain(string arg)
{
        object target, obj, me = this_player();
        mapping job;
        int bonus, exp;

        if( query("owner") != query("id", me) )
                return notify_fail("幫令豈能瞎用？\n");
        if( query("fam") != query("party/partyname", me) )
                return notify_fail("你已經不是此幫的人了。\n");
        if( !mapp(job = query("changle/job")) )
                return notify_fail("你現在沒有幫務纏身。\n");
        if( !arg ) return notify_fail("你要和誰討價還價？\n");
        if( !(target = present(arg, environment(me))) )
                return notify_fail("這兒沒有這個人。\n");
        if( !living(target) )
                return notify_fail("你還是等此人醒來後再說吧\n");
        if( userp(target) )
                return notify_fail("玩家不會出好價錢的。\n");
        if( target->is_busy() || target->is_fighting() )
                return notify_fail(target->name() + "正忙著。\n");
        if( (exp=query("combat_exp", target))<10000 )
        {
                message_vision("$N擺了擺手說道：我買不起，你賣給別人吧。\n", target);
                return 1;
        }
        if( !(obj = present(job["good"], me)) )
                return notify_fail("你把" + job["name"] + "弄丟了。\n");
        if( time()<query("trader/time", target)+600){
                message_vision("$N擺了擺手說道：我剛買了一"+query("unit", obj)+obj->name()+"。\n",target);
                return 1;
        }
        if( (bonus = (int)job["prices"][explode(base_name(environment(target)), "/")[1]]) < 5 ) {
                message_vision("$N擺了擺手說道：這東西現在在此地一點也不值錢，你自己用吧。\n", target);
                return 1;
        }
        set("trader/time", time(), target);
        bonus*=(1+query("combat_exp", target)/100000);
        message_vision("$N想了想說道：好吧，" + chinese_number(bonus) + "兩銀子，再貴我不買了。\n", target);
        message_vision("$N點了點頭，將"+query("unit", obj)+obj->name()+"交給$n。\n",me,target);
        obj->move(CANGKU);
        message_vision("$N說道：下次貴幫來人時我再付款。\n", target);
        message_vision("$N說道：沒關系，下次還有更好的貨。\n", me);

        bonus /= 20;
        addn("combat_exp", bonus, me);
        log_file("test/BangJob",sprintf("%-10s于%-20s時因賣%-10s得%-5s經驗點\n",query("name", me),ctime(time()),obj->name(),chinese_number(bonus)));
        addn("score", bonus/4);
        delete("job");
        return 1;
}