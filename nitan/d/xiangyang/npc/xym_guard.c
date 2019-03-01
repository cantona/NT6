//xym_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_xym(object me, object ob); 
void create() 
{ 
     set_name("守衛",({"shou wei","guard"}) ); 
     set("long","這是一位長的英姿勃勃的年輕人。\n"); 
     set("title","俠義盟劍客"); 
     set("gender","男性"); 
     set("age",20); 
     set("combat_exp",100000); 
     set_skill("dodge",150); 
     set_skill("force",150); 
     set_skill("literate",150); 
     set_skill("unarmed",150); 
     set("inquiry",([ 
          "俠義盟" : (: ask_xym :), 
     ]) ); 
     setup(); 
} 

int ask_xym(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "俠義盟" && query("shen", me) >= 0 )
     { 
           command("famours"+query("id", me));
           tell_object(me,"守衛笑眯眯地對你說：“是想加入咱們俠義盟吧？請進請進。”\n"); 
           set_temp("good_xym1", 1, me);
           return 1; 
     } 
     if( bad_bunch(me) || query("shen", me)<0 )
     { 
           command("say 哪裡來的邪魔歪道，找打麼？"); 
           return 1; 
     } 

     tell_object(me,"俠義盟守衛奇怪道：“同為本幫兄弟，你何出此言啊？”\n"); 
     return 1; 
} 
