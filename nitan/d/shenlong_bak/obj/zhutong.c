// Rama@hx

#include <ansi.h>
inherit ITEM;
inherit F_SSERVER;
void setup()
{}
void init()
{
        add_action("do_entice","entice");
        add_action("do_throw","fang");
        add_action("do_put", "put");
}

void create()
{
        set_name("竹筒", ({"zhu tong" ,"zt"}));
        set_max_encumbrance(10000);
        set("unit", "個");
        set("long", "這是一節青竹制成的竹筒，如果在裡面放上誘餌，可以用來捕捉毒蟲(entice)。\n");
        set("value", 100);
//      set("no_drop", "這樣東西不能離開你。\n");
        set_weight(105);
        set("no_sell",1);
        setup();
}
int is_container() { return 1; }

int do_entice(string arg)
{
    object me,ob1,ob;
    string who,what;
    me = this_player();
    if( !arg
        ||      sscanf(arg, "%s in %s", who, what)!=2)
         return notify_fail("命令格式: entice <毒蟲> in <物品>。\n");
    ob1= present(what,me);
    ob = present(who,environment(me));
    if (!ob )
         return notify_fail("你要引誘什麼？\n");
    if( !ob1 || query("id", ob1) != "zhutong" )
         return notify_fail("你要把蟲子誘往那裡？\n");
    if(!present("long xianxiang",ob1))
         return notify_fail("竹筒似乎對"+query("name", ob)+"並沒有吸引力！\n");
    if( query("race", ob) != "蛇類" && query("race", ob) != "昆蟲" && query("name", ob) == HIW"怪蛇"NOR )
         return notify_fail("竹筒太小，似乎放不下"+query("name", ob)+"！\n");
    if( ((int)ob1->query_max_encumbrance()-(int)ob1->query_encumbrance())< ob->query_weight()  )
        return notify_fail("竹筒太小，似乎放不下"+query("name", ob)+"！\n");
    if (sizeof(all_inventory(ob1)) >= 2) 
        return notify_fail("竹筒裡面已經有東西了。\n");              
    message_vision("$N將竹筒的塞子拔掉，對著"+query("name", ob)+"輕輕的吹著口哨。\n",me);
    if(me->query_skill("poison",1) < 80)
    {
        message_vision("但是"+query("name", ob)+"不為所動，反而開始對$N發動攻擊！！\n",me);
        ob->kill_ob(me);
        return 1;
    }
    else {      
        message_vision("只見"+query("name", ob)+"在竹筒邊探頭探腦的聞了聞，忽然一閃，鑽進了$N的竹筒裡。\n",me);
        message_vision("$N急忙將竹筒塞住，抹了抹滿頭的冷汗，心想“好險啊！”。\n",me);
        ob->move(ob1);
        return 1;
        }
     return 1;
}
int do_throw(string arg)
{
    object me,ob1,ob,target;
    string who,what;
    me = this_player();
//  ob1= this_object();
    if( !arg
        ||      sscanf(arg, "%s from %s", who, what)!=2)
         return notify_fail("命令格式: fang <毒蟲> from <物品>。\n");
    ob1 = present(what,me);
    if (!ob1)
         return notify_fail("你要從那裡放毒蟲？\n");
    ob = present(who,ob1);
    if (!ob )
         return notify_fail("你要放什麼？\n");
    if( !target ) target = offensive_target(me);
    if( !target
        ||      !me->is_fighting(target) )
                return notify_fail(query("name", ob)+"只能用于戰鬥中暗算對手。\n");
    if( query("family/family_name", me) != "神龍教"
         ||me->query_skill("poison",1) < 50)
    {
         tell_object(ob, HIG "你從顫抖著從懷裡掏出竹筒，但怎麼也沒有膽量打開它！\n" NOR );
         message_vision(HIG"只見$N從懷裡掏出一個竹筒，臉色發白，手腳顫抖不知道要幹什麼？\n",me);
    }
    tell_object(me,  "你悄悄從懷裡掏出一個竹筒，打開了塞子。\n" );
    message_vision("只見$N虛晃一招把手一揚，一道閃光射向"+query("name", target)+"的嚥喉。\n",me);
    ob->move(environment(me));
    set("combat_exp",query("combat_exp",  ob)*2+query("combat_exp", target), ob);
    ob->kill_ob(target);
    target->start_busy(1);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision("只見"+query("name", ob)+"身子在空中一折，咬向"+query("name", target)+"的頭頂。\n",me);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision("只見"+query("name", ob)+"尾巴一彈，在空中一個回轉竟繞到了"+query("name", target)+"的背後。\n",me);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision(query("name", target)+"只見眼前一閃，"+query("name", ob)+"竟咬向"+query("name", target)+"的肩頭。\n",target);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision(query("name", ob)+"力氣用盡落向地面，順勢咬向"+query("name", target)+"的腳背。\n",me);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision(query("name", ob)+"落到地面，蜿蜒地遊走了。\n",me);
    destruct(ob);
    return 1;
}
int do_put(string arg)
{
    object me=this_player();
    object ob,item;
    if(!arg) return notify_fail("你要將什麼東西放進哪裡？\n");

    if( sscanf(arg,"%s in %s",ob,item)!=2 || !objectp(ob = present(ob, me)) || !objectp(item = present(item, me)))
    {
        write("你要放什麼東西？\n");
        return 1;
    }
    else if( query("id", item) != "zhutong" )
        return 0;
        else if( query("id", ob) != "longxianxiang" )
    {
        write("你不能把這件東西放到竹筒裡面。\n");
        return 1;
    }
    else if( present("long xianxiang", item) )
    {
        write("竹筒裡面已經有一塊龍涎香了。\n");
        return 1;
    }
    else return 0;
}
