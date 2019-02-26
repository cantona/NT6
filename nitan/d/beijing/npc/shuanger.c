#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
int ask_go();
int ask_kiss();
int do_chase();
void create()
{
        set_name("雙兒", ({ "shuang er", "shuang","er"}));
        set("title", HIW "天下無雙" NOR);
        set("nickname", HIM "大功告成" NOR);
        set("gender", "女性");
        set("age", 15);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);
        set("per", 27);
        
        set("max_qi", 500);
        set("max_jing", 200);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("sword", 80);
        set_skill("taiji-jian", 70);
        set_skill("taiji-quan", 70);
        set_skill("tiyunzong",50);
        map_skill("dodge", "tiyunzong");
          map_skill("parry", "taiji-jian");
          map_skill("sword", "taiji-jian");
          map_skill("unarmed", "taiji-quan");
        set_temp("apply/attack", 15);
        set_temp("apply/attack", 15);
        set_temp("apply/damage", 15);
       set("inquiry", ([
            "你願不願意跟我走" : (: ask_go :),
            "大功告成" :  (: ask_kiss :),
        ]));
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth")->wear();
}
int init()
{
       add_action("do_attack","attack");
       add_action("do_stop","stop");
       add_action("do_send","sendto");
       add_action("do_sha","sha");
}
int ask_kiss()
{
  object me;
  string host_id;
  me=this_player();
  if(query("id")!="shuang er")
        {
         sscanf(query("id"),"%s's shuang er",host_id);
         if( query("id", me) == host_id )
           {
           if(random(10)<1)               
           {
           say(query("name")+"滿臉羞得通紅,垂下頭來,緩緩的點了點頭.\n");
           addn("combat_exp",2000);
           }            
           else 
           say(query("name")+"啊的一聲,一下子跳將開去,説:不嘛,不要.\n");
           return 1;
           }
        }
    say(query("name")+"説道:呸,我不幹!\n");
return 1;
}
int ask_go()
{
  object me;
  string new_name,new_id,host_id;
   me=this_player();
           if(query("id")!="shuang er")
        {
                 sscanf(query("id"),"%s's shuang er",host_id);
                 if(query("id")==host_id)
           {say(query("name")+"睜大眼睛看了看"+
                                query("name", me)+"，説:當然願意啦,我都聽你的。\n");
            return 1;
           }
         if( query("id", me) != host_id )
           {say(query("name")+"睜大眼睛看了看"+
                                query("name", me)+"，説:不行的,我得聽我主人的。\n");
                        return 1;
           }
         }
         if( query("weiwang", this_player()) >= 70 && query_temp("zhuang_liwu", this_player()) )
           {
           write( HIY "雙兒道:夫人待我恩重如山,主人對我莊家又有大恩。\n" NOR);
           write( HIY "夫人要我服侍主人,我一定盡心。\n" NOR);
           command("nod");      
           set_leader(me);
       new_name=query("name", me)+"的丫環雙兒";
       new_id=query("id", me)+"'sshuanger";
       set("name",new_name);
       set("id",new_id);
           tell_object(me, "可用指令:\nattack sb 攻擊某人.\nsha sb 殺死某人.\nstop 停止戰鬥.\nsendto sb.--把雙兒送給sb.\n");
           set("long","這是"+new_name+"。\n"
                "她是一個十分清秀的少女,大約十四五歲年紀;\n"
                "一張雪白的臉龐,眉彎嘴小,笑靨如花,正笑嘻嘻地看着你。\n");
        call_out("do_chase",5);
       }
           else say(query("name")+"睜大眼睛看着"+query("name", me)+"，説:不行的,夫人沒有同意。\n");
        return 1;
}
int do_chase()
{
        object dest=this_object();
        object me=query_leader();
        if( !objectp(me) || me->is_ghost() ){
           set_leader(0);
                return 1;
        }
        if( !living(me) || !living(dest) || query("no_fight", environment()) || query("fight_room", environment())){
                call_out("do_chase", 5);
                return 1;
        }
        if ( environment(me)==environment(dest) )      
        {
                call_out("do_chase", 5);
                return 1;
        }
        message_vision("$N急急忙忙地跑開了！\n",this_object());
        dest->move(environment(me));
        message_vision("$n急急忙忙的追上來，撅起小嘴：“$N別跑這麼快，我有點累呢！\n" NOR, me,this_object());
        call_out("do_chase", 5);
         return 1;
}
int do_attack(string arg)
{
  object ob; 
  string host_id;
  object me=this_player();
  if(query("id")=="shuang er")
   {say("你無權使用此命令。\n");
    return 0;}
  sscanf(query("id"),"%s's shuang er",host_id);
  if( query("id", me) != host_id )
  return notify_fail("雙兒連理都不理你！\n");
  if(!arg||!objectp(ob=present(arg,environment(me))))
        return notify_fail("雙兒傻傻地望着你，不明白你的意思。\n");
  if (userp(ob)) return notify_fail("雙兒臉龐憋的通紅的説：對不起，我不能殺玩家的！\n");
  if( environment() && query("no_fight", environment()))return notify_fail("雙兒小心翼翼的看了你一眼説：這裏是安全區啊！\n");
  if(!living(ob)) 
         return notify_fail("雙兒説:"
              +query("name", ob)+"已經這樣啦你還要...??!!\n");
  message_vision("雙兒對主人$N點頭道: 嗯,好的.\n",me);
  fight_ob(ob);
  return 1;
}
int do_stop()
{
   string host_id;
  object me=this_player();
  if(query("id")=="shuang er")
   return notify_fail("你無權使用此命令。\n");
  sscanf(query("id"),"%s's shuang er",host_id);
  if( query("id", me) != host_id )
   return notify_fail("雙兒連理都不理你！\n");
 if(!is_fighting())
         return notify_fail("雙兒現在沒和人打鬥.\n");
 command("halt");
 message_vision("雙兒對主人$N微微一笑。\n",me);
 return 1;
}
int do_send(string arg)
{
  object ob; string host_id,new_name,new_id;
  object me=this_player();
  if(query("id")=="shuang er")
   return notify_fail("你無權使用此命令。\n");
  sscanf(query("id"),"%s's shuang er",host_id);
  if( query("id", me) != host_id )
   return notify_fail("雙兒連理都不理你！\n");
  if(!arg||!objectp(ob=present(arg,environment(me))))
        return notify_fail("你要把雙兒送給誰？\n");
  if(!living(ob) || !userp(ob)) 
         return notify_fail("你只能把雙兒給活人!\n");
 message_vision("雙兒眼淚汪汪地望着主人$N，説:\n主人待我好,是我命好;主人待我不好,是我命苦罷了.\n",me);
 set_leader(ob);
 new_name=query("name", ob)+"的丫環雙兒";
           set("long","這是"+new_name+"。\n"
                "她是一個十分清秀的少女,大約十四五歲年紀;\n"
                "一張雪白的臉龐,眉彎嘴小,卻象是剛受人欺負,眼淚汪汪地看着你。\n");
 new_id=query("id", ob)+"'sshuanger";
 set("name",new_name);
 set("id",new_id);
 write(HIY"雙兒對新主人"+query("name", ob)+"楚楚可憐地盈盈一拜。\n"NOR);
 tell_object(ob,"可用指令:\nattack sb 攻擊某人.\nsha sb 殺死某人.\nstop 停止戰鬥.\nsendto sb.--把雙兒送給sb.\n");
 return 1;
}
int do_sha(string arg)
{
        object me,ob;
        me = this_object();
        if(!arg||!objectp(ob=present(arg,environment(me))))
        return notify_fail("你要雙兒殺誰？\n");
        if( !query("no_fight", environment(ob)) )
        {
        message_vision("雙兒對$N點頭説道: 嗯,好的.\n",this_player());
        command("say 哼,主人要我殺了你!");
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob); 
        }
        return 1;
}       
int return_home(object room)
{
        if (query_leader())
                return 1;
        ::return_home(room);
}
