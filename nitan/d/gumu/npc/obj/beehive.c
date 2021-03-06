// beehive.c 蜂箱
// by April     01.08.26
// update by April 01.10.30


#include <ansi.h>

inherit COMBINED_ITEM;

int auto_check(object me, object ob);

void create()
{
        set_name(HIW "玉蜂箱" NOR, ({ "feng xiang", "beehive", "box", "xiang" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", HIW "這是古墓派木製的玉蜂箱。裏面嗡嗡的，不知道有多少玉蜂。\n" NOR);
                set("base_unit", "個");
                set("value", 1000);
                set("material", "wood");
                set("no_sell", 1);
                set("no_give",0);
                set("no_get",1);
                set("base_weight",5000);
        }

        set("no_refresh", 1);

        set_amount(1);
        setup();
}

void init()
{
        object me = this_player();
        if( query("id", me) != "sunpopo"){
                set("no_drop",  "這麼有用的東西怎麼能扔了呢。\n");
                set("no_steal", "這個東西你偷不到。\n");
        }

        add_action("do_open", "open");
        add_action("do_close", "close");
        add_action("do_fang", "fang");
        add_action("do_give","give");
        add_action("do_cai", "cai");
        add_action("do_dest", "dest");

}

int do_fang(string arg)
{
        object me, ob;
        me = this_player();
        ob = this_object();

        if(!arg || (arg != "feng xiang" && arg != "beehive" && arg != "box" && arg != "xiang"))
                return 0;
        if( query("down", ob))return notify_fail("你糊塗了？\n");
        if( !ob) return notify_fail("你並沒有拿着蜂箱啊？\n");
        if(strsrch(query("short", environment(me)), "樹林") == -1)
                return notify_fail("你找不到合適的地方放蜂箱！ \n");
        if( query("owner", ob) != me)return notify_fail("這你的蜂箱嗎？\n");
        if(present("feng xiang", environment(me))) return notify_fail("這裏已經有別人在放養玉蜂了。\n");
        if( query("lastplace", ob) == environment(me))return notify_fail("玉蜂剛在這裏採過蜜！\n");

        ob = present("feng xiang", me);

        if(me->is_busy())
                return notify_fail("你正忙着呢! \n");

        message_vision(HIB"$N在樹林中找了一塊兒空地，輕輕地把蜂箱放在地上。\n"NOR,me);

        set("down", 1, ob);
        ob->move(environment(me));
        remove_call_out("auto_check"); 
        call_out("auto_check", 5+random(5),me,ob);
        return 1;
}

int do_open(string arg){
        object me = this_player();
        object ob = this_object();
        string descrp;

        if(!arg || (arg != "feng xiang" && arg != "beehive" && arg != "box" && arg != "xiang"))
                return 0;
        if( query("open", ob))return notify_fail("你糊塗了？\n");
        if( query("owner", ob) != me)return notify_fail("這你的蜂箱嗎？\n");
        if(me->is_busy()) return notify_fail("你正忙着呢！ \n");
        if( !query("down", ob))return notify_fail("你得先把玉蜂箱放下！\n");
        if( query("open", ob))return notify_fail("玉蜂箱門開着呢！\n");
//      if(query("bee_out")) return notify_fail("你的玉蜂羣忙着呢！\n");

        remove_call_out("auto_check");
        call_out("auto_check", 5+random(5),me,ob);

        message_vision(HIG"$N輕輕地打開玉蜂箱的門，玉蜂陸陸續續地飛出來，採蜜去了。\n"NOR,me);

        set("open", 1, ob);
        set("lastplace", environment(me), ob);
        set("mi", 1, ob);

        return 1;
}

int do_close(string arg){
        object me = this_player();
        object ob = this_object();
        string descrp;

        if(!arg || (arg != "feng xiang" && arg != "beehive" && arg != "box" && arg != "xiang"))
                return 0;
        if( !query("open", ob))return notify_fail("你糊塗了？\n");
        if( query("owner", ob) != me)return notify_fail("這是你的蜂箱嗎？\n");
        if(me->is_busy()) return notify_fail("你正忙着呢！ \n");
        if( !query("down", ob))return notify_fail("你得先把玉蜂箱放下！\n");
        if( !query("open", ob))return notify_fail("玉蜂箱門關着呢！\n");
        if( query("qi", me)<100)return notify_fail("你已經精疲力竭，無法召喚玉蜂回來了！\n");

        message_vision(HIG"$N口中唸唸有詞，一會兒玉蜂陸陸續續地都飛了回來，$N輕輕關上玉蜂箱門,把蜂箱背在身上。\n"NOR,me);

        set("open", 0, ob);
        set("down", 0, ob);
        ob->move(me);

        me->receive_damage("qi", 10+random(10));

        remove_call_out("auto_check");

        return 1;
}


int auto_check(object me,object ob)
{
        int lvl;
        if (! me)
        {
                destruct(this_object());
                return 1;
        }
        lvl = me->query_skill("qufeng", 1);

        if( environment(ob) != environment(me) ){
                set("escaped", 1, ob);
                destruct(this_object());
                message_vision(HIR"工作時你怎麼跑了？玉蜂都沒人管啦！。\n"NOR,me);
                return 0;
        }
        if( query("mi", ob)<40 )
                addn("mi", 10, ob);
        if( query("mi", ob)>25 && random(2) == 0 || 
            query("mi", ob) >= 40 )
        {
                message_vision(HIW"玉蜂團團打轉，看樣子蜂箱的蜜已經採滿了,你應該回去了。\n"NOR,me);
                return 1;

        }
        else if (random(15) == 0)
        {
                if (random(3) == 0)
                {
                        message_vision("$N看見一些玉蜂在一個地方奇怪地舞着，也許有什麼藥材可以採(cai yao)吧。\n",me);
                        set("yaocai_h", 1, environment(me));
                }
                else
                {
                        message_vision("$N看見一些玉蜂在一個地方奇怪地舞着，也許有什麼藥材可以採(cai yao)吧。\n",me);
                        set("yaocai", 1, environment(me));
                }

        }
        else if( query("mi", ob)%2 == 0 && random(2) == 0 )
        {
                message_vision(HIY"$N嘴裏不斷髮出嗡嗡聲，指導玉蜂更有效率的採蜜。\n"NOR, me);
                me->start_busy(random(3));
                addn("qi", -(2+random(3)), me);
                if (lvl < 600)
                me->improve_skill("qufeng",lvl/3+random(lvl/2));
                me->improve_skill("force",lvl/5+random(lvl/3));

        }

        call_out("auto_check",5,me,ob);
        return 1;
}

int do_give(string arg)
{
        string target, item;
        object obj, who,ping, me=this_player();
        string msg;
//        int    exp,qn,gj,i,j;
        int    qn,gj,i,j;
        mixed exp;
        object *inv;


    if(!arg) return notify_fail("你要給誰什麼東西？\n");

    if( sscanf(arg, "%s to %s", item, target)==2
        || sscanf(arg, "%s %s", target, item)==2 );
    else return notify_fail("你要給誰什麼東西？\n");

        if ( item != "beehive" && item !="box" && item != "xiang" ) return 0;
        if ( target != "sun" && target !="nanny" ) return 0;
        if ( !objectp(obj = present(item, me)) ) return notify_fail("你身上沒有這樣東西。\n");
        if (me->is_busy()) return notify_fail("你正忙着呢。\n");
    if (!objectp(who = present(target, environment(me))) || !living(who))
        return notify_fail("這裏沒有這個人。\n");
        if ( userp(who) ) return notify_fail("對方不接受這樣東西。\n");
        if( query("race", who) != "人類" )
                return notify_fail("別找碴兒！怎麼把玉蜂箱交給畜生？\n");
        if( who == me) return notify_fail("自己給自己？！\n");

        message_vision("$N給$n一個"+HIW"玉蜂箱。\n"NOR, me, who);

        if( query("owner", obj) == me )
        {
                if(query("escaped")) {
                        message_vision(CYN"$N不好意思地搔了搔頭。\n"NOR, me, who);
                        message_vision(CYN"$N紅着臉對孫婆婆説道，這次工作沒幹好。\n"NOR, me, who);
                        message_vision(CYN"$n輕輕拍了拍$N的頭。\n"NOR, me, who);
                        message_vision(CYN"$n和藹地對$N説道：沒關係，下次注意就好。\n"NOR, me, who);
                        if( query_temp("gm_xunfeng", me) ) delete_temp("gm_xunfeng", me);
                }
                else if( query("mi", obj)<25 )
                {
                        message_vision(CYN"$n説道：蜂蜜沒有采滿啊，沒關係，下次注意就好。\n"NOR,me,who);
                        if( query_temp("gm_xunfeng", me) ) delete_temp("gm_xunfeng", me);
                }
                else
                {
                        message_vision(CYN"$n輕輕拍了拍$N的頭。\n"NOR, me, who);
                        message_vision(CYN"$n和藹地對$N説道：辛苦$N啦，下去休息一下吧。\n"NOR, me, who);
                        exp = 140+random(40);
                        qn = 40 + random(40);
                        gj = 5 + random(5);
                        if( query("potential", me)>me->query_potential_limit() )
                                qn = 1 + random(2);
                        msg=sprintf(HIW"這次養蜂任務共得到:%d經驗、%d潛能和%d門派功績。\n"NOR,exp,qn, gj);
                        tell_object(me,msg);
                        if( query_temp("gm_xunfeng", me) ) delete_temp("gm_xunfeng", me);
                        addn("combat_exp", exp, me);
                        addn("potential", qn, me);
                        addn("family/gongji", gj, me);

                        if (random(1)==0)
                        {
                                inv = all_inventory(me);
                                j=0;
                                for(i=0; i<sizeof(inv); i++)
                                        if( query("name", inv[i]) == CYN"青瓷瓶"NOR )
                                        j += 1;
                                if (j > 4)
                                tell_object(me,"孫婆婆對你説：你已經有好多青瓷瓶了，我就不給你了。\n");
                                else if (random(5)==0)
                                {
                                        ping = new("/d/gumu/npc/obj/qingci-ping");
                                        set("liquid/remaining", 10, ping);
                                        set("liquid/name", "玉蜂王漿", ping);
                                        ping->move(me);
                                        tell_object(me,"孫婆婆給你一瓶玉蜂王漿。\n");

                                }
                                else
                                {
                                        ping = new("/d/gumu/npc/obj/qingci-ping");
                                        set("liquid/remaining", 10, ping);
                                        ping->move(me);
                                        tell_object(me,"孫婆婆給你一瓶玉蜂蜜。\n");

                                }
                        }
                }

        }
        else
        {
                message_vision(CYN"$n對$N微微笑了笑。\n"NOR, me, who);
                message_vision(CYN"$n説道：多謝啦！\n"NOR, me, who);
        }

        destruct(obj);

        return 1;
}

int do_cai(string arg)
{
        object me = this_player();
        object here = environment(me);
        int i;
        object yaocai;

        if ( !arg && arg != "yao" ) return 0;
        if( !query("yaocai", here) && !query("yaocai_h", here))return 0;

        if( query("yaocai", here)){
                set("yaocai", 0, here);
                switch (random(5)){
                case 0 : yaocai = new("/clone/herb/chantui");
                        break;
                case 1 : yaocai = new("/clone/herb/muxiang");
                        break;
                case 2 : yaocai = new("/clone/herb/shengma");
                        break;
                case 3 : yaocai = new("/clone/herb/chaihu");
                        break;
                case 4 : yaocai = new("/clone/herb/shanju");
                        break;
                }
                yaocai->move(me);
                message_vision("$N撥開雜草發現了"+query("name", yaocai)+"。\n",me);
        }
        if( query("yaocai_h", here)){
                set("yaocai_h", 0, here);
                switch (random(3)){
                case 0 : yaocai = new("/clone/herb/renshen");
                        break;
                case 1 : yaocai = new("/clone/herb/heshouwu");
                        break;
                case 2 : yaocai = new("/clone/herb/tufuling");
                        break;
                }
                yaocai->move(me);
                message_vision("$N撥開雜草發現了"+query("name", yaocai)+"。\n",me);
        }
        return 1;
}
int do_dest(string arg){
         object obj;
         object me = this_player();

         if (arg != "box" && arg != "xiang" )
                return notify_fail("你只能摧毀蜂箱。\n");
         obj = present(arg, environment(me));
         if (!obj)  return notify_fail("你只能摧毀自己的蜂箱。\n");
         if( query("owner", obj) != me || !obj )
                return notify_fail("你只能摧毀自己的蜂箱。\n");
         if (obj)
         {
                   message_vision(HIG"$N發現這個蜂箱已經廢棄了，一腳把它踢了個粉碎。\n"NOR,me);
                   destruct(obj);
         }
         else return notify_fail("沒有這樣東西。。。。\n");
         return 1;
}
