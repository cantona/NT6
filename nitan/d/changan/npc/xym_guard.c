//xym_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_xym(object me, object ob); 
void create() 
{ 
     set_name("守衞",({"shou wei","guard"}) ); 
     set("long","這是一位長的英姿勃勃的年輕人。\n"); 
     set("title","俠義盟劍客"); 
     set("gender","男性"); 
     set("age",20); 
     set("combat_exp",100); 
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
           tell_object(me,"守衞笑眯眯地對你説：“是想加入咱們俠義盟吧？請進請進。”\n"); 
           set_temp("good_xym1", 1, me);
           return 1; 
     } 
     if( bad_bunch(me) || query("shen", me)<0 )
     { 
           ob->command("say 哪裏來的邪魔歪道，找打麼？\n"); 
           return 1; 
     } 

     tell_object(me,"俠義盟守衞奇怪道：“同為本幫兄弟，你何出此言啊？”\n"); 
     return 1; 
} 
