// 大唐雙龍傳

inherit NPC;

void create()
{
  set_name("丫鬟", ({"ya huan","huan"}));
  set("long","這是一位丫鬟。\n");
  set("gender", "女性");
  set("combat_exp", 3000);
  set("age", 18);
  set("per", 23);
  set("attitude", "friendly");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
 
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}

void init()
{
   object ob;
   
   ob=this_player();
   
   if(!ob||is_fighting()) return;
   
   remove_call_out("welcome");
   call_out("welcome",1,ob);
   
}

void welcome(object ob)
{
   if(!ob) return;
   if(environment(ob)!=environment(this_object()))
   return;
   
   switch(random(2)){
    case 0:
     command("say 奴家這廂有禮了！");
     break;
    case 1:
     command("say 據説老爺要把我納做小妾，不知道是真是假。");
   }
   
}


