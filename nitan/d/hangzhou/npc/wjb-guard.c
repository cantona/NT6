inherit NPC; 

#include <ansi.h> 

int ask_wjb(object me, object ob); 
void create() 
{ 
     set_name("守衞",({"shou wei","guard"}) ); 
     set("long","這是一位的無極幫的守衞。\n"); 
     set("title","無極幫幫眾"); 
     set("gender","男性"); 
     set("age",20); 
     set("combat_exp",100000); 
     set_skill("dodge",150); 
     set_skill("force",150); 
     set_skill("literate",150); 
     set_skill("unarmed",150); 
     set("inquiry",([ 
          "無極幫" : (: ask_wjb :), 
     ]) ); 
     setup(); 
} 

int ask_wjb(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if( query("good_bunch(me, me)") != "無極幫" && query("shen", me) >= 0 )
     { 
           command("famours"+query("id", me));
           tell_object(me,"守衞笑眯眯地對你説：“是想加入咱們無極幫吧？請進請進。”\n"); 
           set_temp("good_wjb1", 1, me);
           return 1; 
     } 
     if( bad_bunch(me) || query("shen", me)<0 )
     { 
           ob->command("say 哪裏來的邪魔歪道，找打麼？\n"); 
           return 1; 
     } 

     tell_object(me,"守衞奇怪道：“同為本幫兄弟，你何出此言啊？”\n"); 
     return 1; 
} 
