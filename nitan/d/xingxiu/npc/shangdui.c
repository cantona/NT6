// Room: /d/xingxiu/npc/shangdui.c
// Last Modified by winder on Apr. 25 2001

#include <ansi.h>
inherit ITEM;
#include "dest.h";

void create()
{
        set_name("駱駝商隊", ({ "shangdui"}));
        set("unit", "只");
        set("location", 1);
        set_weight(900000);
        set("long", "
一只遠道而來的駱駝商隊，駱駝背上堆滿了貨物。商人們
手中提著一些布袋，看來是比較重要的東西。。。\n");
        set("no_get", 1);
        set("no_drop", 1);
        seteuid(getuid());
}

void init()
{
        if (!query("inited"))
        call_out("destroying", 20, this_object());  
        add_action("do_rob", ({"qiang"}));
}

int do_rob()
{
        object me, ob;   
        string arg ;
        int stage, i;
        me = this_player();
        ob = this_object();
        stage = 0;
        i = sizeof(dest);
        arg = query("arg");

        if(!living(me)) return 0;
        if( !query_temp("xx_job2", me) || !query_temp("rob_start", me) )
                return notify_fail("你這姦賊，竟敢光天化日之下攔截商隊，不怕被打入天牢嗎？\n");
        if(objectp(present("hubiao biaoshi", environment(me))))
                return notify_fail("護鏢鏢師看來武功不弱，你還是先打發了面前這個再說吧！\n");  
        message_vision(HIY "$N對著$n大吼一聲：星宿"+me->name()+"在此！留下你們的錢財來！\n"NOR, me, ob);
        set_temp("xx_rob", 1, me);
        if( !query("going", ob) )
        {
                while (i--) if (arg == dest[i]["name"]) break;
                remove_call_out("go_stage");
                set("f", 7*(query_temp("j", me)+1), ob);
                call_out("go_stage",1,ob,stage,i,sizeof(dest[i]["context"]),me);
                set("going", 1, ob);
        }
        remove_call_out("make_bs");
        call_out("make_bs", 1, me, ob); 
        return 1;     
}
void make_bs(object me, object ob)
{
        object obj, obj1;
        int j;
        j=query_temp("j", me);
//
        if(j>0)
        {
                obj = new("/d/xingxiu/npc/biaoshi");
                obj->move(environment(me));
                obj->do_copy(me);
                obj1 = new("/d/xingxiu/npc/biaoshi");
                obj1->move(environment(me));
                obj1->do_copy(me);
                addn_temp("j", -1, me);
                return;      
        }
        else
//
        {
                message_vision(HIW"$N見已經無人保護，在$n的威脅下，只得停了下來，將所帶的財物乖乖地獻上！\n"NOR, ob, me);    
                obj = new("/d/xingxiu/obj/red");
                obj->move(me);
                set("owner",query("id",  me), obj);
                addn("combat_exp", 150, me);
                addn("shen", -(query("combat_exp", me)/20), me);
                delete_temp("rob_start", me);
                delete_temp("xx_rob", me);
                delete_temp("xx_job2", me);
                delete_temp("j", me);
                message_vision("$N帶著駱駝，轉過幾個小山丘就不見了。\n", ob);
                destruct(ob);
        }        
}

void go_stage(object me, int stage, int i, int size, object player)
{
        object where;
        int f=query("f", me);
        if(stage < size)
        {
                message_vision(HIY"$N匆匆忙忙地向有駐軍的關口方向逃去。\n"NOR, me);
                me->move(dest[i]["context"][stage]);
                message_vision(HIY"$N匆匆忙忙地奔了過來。\n"NOR, me);
                where = environment(me); 
                tell_object(player,HIM+query("name", me)+"好象逃往了"+query("short", where)+"一帶。\n"NOR);
                call_out("go_stage", f, me, ++stage, i, size, player);
        }
        else
        {    
                tell_object(player,HIM+query("name", me)+"成功地逃進了城鎮。\n"NOR);
                delete_temp("xx_rob", player);
                delete_temp("xx_job2", player);
                delete_temp("rob_start", player);
                delete_temp("j", player);
                delete_temp("biaoshi", player);
                message_vision(MAG"\n$N轉進關中，在官兵的護送下離開了。\n"NOR,me);      
                destruct(me);
        }
}
void destroying(object me)
{
        if( !query("going", me) )
        {
                message_vision("$N帶著駱駝，轉過幾個小山丘就不見了。\n", me);        
                destruct(me);
                return;
        }
        set("inited",1);
  call_out("destroying2", 450, me);
}

void destroying2(object me)
{
        message_vision("$N帶著駱駝，轉過幾個小山丘就不見了。\n", me);        
        destruct(me);
        return;
}
