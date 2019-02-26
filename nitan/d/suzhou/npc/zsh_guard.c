//zsh_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_zsh(object me, object ob); 
void create() 
{ 
     set_name("守衞",({"shou wei","guard"}) ); 
     set("long","這是一位長的英姿勃勃的年輕人。\n"); 
     set("title","紫衫會會眾"); 
     set("gender","男性"); 
     set("age",20); 
     set("combat_exp",100); 
     set("inquiry",([ 
          "紫衫會" : (: ask_zsh :), 
     ]) ); 
     setup(); 
     carry_object("/clone/cloth/cloth")->wear();  
     carry_object("/clone/weapon/changjian")->wield();  
} 

int ask_zsh(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "紫衫會" && query("shen", me) >= 0 )
     { 
           tell_object(me,"守衞上上下下看了看你，嗯了一聲。\n"); 
           tell_object(me,"守衞對你説道：“想加入紫衫會？當家的在裏面，你自己進去吧。”\n"); 
           set_temp("good_zsh", 1, me);
           return 1; 
     } 
     if( bad_bunch(me) || query("shen", me)<0 )
     { 
           command("say 哼！還不快滾？我紫衫會對你這種人是不留情面的！"); 
           return 1; 
     } 

     tell_object(me,"守衞奇怪道：“大家都是會內兄弟，你何出此言啊？”\n"); 
     return 1; 
} 
