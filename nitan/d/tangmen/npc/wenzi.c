// wenzi.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("蚊子", ({ "wen zi" }) );
        set("long",     "一隻長嘴的小蟲正笑嘻嘻的看著你。\n");

        set("race", "野獸");
        set("age", 1);
        set("attitude", "peaceful");

        set("max_jingli", 80);
        set("max_qi", 80);

        set("str", 10);
        set("cor", 50);

        set("limbs", ({ "頭部", "身體", "翅膀" }) );
        set("verbs", ({ "bite" }) );

        set_temp("apply/attack", 10);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        set("combat_exp", 1000);
        setup();
}

void init()
{
        object me,ob;
        
        ::init();
        if (interactive(me = this_player())&& !is_fighting())
        {
        if( query_temp("lianyl", me) )
               {
               remove_call_out("telling");
               call_out("telling", 1, me);
                }
        }
        add_action("do_zha", "zhua");
}

int telling(object me)
{   
    if (!me || environment(me) != environment()) return 1; 
    if( query("tangmen/yanli", me) >= 50 )
       return notify_fail("這位唐門弟子好眼力啊！加油啊！\n");
       return notify_fail("唉，想不到啊，想不到，你的眼力太水了吧！要努力啊！\n");
}

int do_zha(string arg)
{       
        object ob;
        object obb = this_object();
        int jing_drop;
        mapping myfam;
        
        ob = this_player();
        myfam=query("family", ob);
        jing_drop = random(40);
        
        if ( myfam["family_name"] != "唐門世家" )
           {
           message_vision(HIR"$N想調戲蚊子啊！\n"NOR,ob);
           return 1;
           }          
        if ( !arg||(arg != "wenzi" && arg != "wen zi"))
           return notify_fail("你想抓什麼啊? \n");
        
        if( query_temp("find_wz", ob) )
           return notify_fail("心不要太黑！你要幾隻啊！\n");
        
        if( query_temp("minchen", ob) != query("short") )
           return notify_fail("你不要見到蚊子就抓啊！\n");   
           
/*
        if( query("jingli", ob)<20 )
           return notify_fail("身體重要，不要忘了休息啊！\n");
*/
         
        if( query("d3name") != query("id", ob) )
           return notify_fail("這個世界真奇怪，真奇怪！\n");   
           
        if( query_temp("lianyl", ob) )
          {   
        message_vision(YEL"$N眯起眼睛來，小心翼翼的靠近蚊子，猛的一撲......\n"NOR, ob);
                 if( random(query("tangmen/yanli", ob)/3+10+query("dex", ob)/3)>random(50) )
                    {
                        message_vision(HIG"$N哈哈一笑，定睛一看，蚊子已被$N抓住了，心中不由的一陣得意。\n"NOR,ob);
                        tell_object(ob,HIR"你再一看，蚊子已死，算了，不要了。回去交差吧！\n"NOR);
                        delete_temp("lianyl", ob);
                        set_temp("find_wz", 1, ob);
                        delete_temp("started", ob);
                        set_temp("jobok", 1, ob);
                        ob->clear_condition("tmjob");
                        obb->die();
                        return 1;
                     }
                 else 
                  {   
                  switch( random(3))
                   {case 0:
                     say("蚊子嗡嗡的飛開了。你差點跌倒！\n");
                    break;
                    case 1:
                     say(HIY"一不小心你來了個狗啃泥，可憐啊！\n"NOR);
                    break;
                    case 2:   
                     say(HIC"唉，又一個大馬趴！\n"NOR);
                    break;
                   }
                  return 1; 
                  } 
           }     
       return notify_fail(HIR"又是一個沒有事做的人！\n"NOR);
}                     
                  
                     
