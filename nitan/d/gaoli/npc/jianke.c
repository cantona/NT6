// 大唐雙龍傳


inherit NPC;

void create()
{
  set_name("劍客", ({"jian ke","ke"}));
  set("long","這是一名高麗的劍客。\n");
  set("gender", "男性");
  set("combat_exp", 600000);

  set_skill("unarmed", 310);
  set_skill("dodge",320);
  set_skill("parry",320);
  set_skill("sword",320);
  set_skill("force",320);
  
  //set_skill("babu-ganchan",120);
  //set_skill("leveltwo-sword",120);
  
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
  carry_object("/d/gaoli/obj/changjian")->wield();
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
     command("say 我的劍術是和弈劍派學的，非常高超的！");
     break;
    case 1:
     command("say 不是我吹牛，如今我的劍術在高麗也數一數二了。");
   }
   
}

