// 大唐雙龍傳


inherit NPC;

void create()
{
  set_name("公子", ({"gong zi","zi","gong"}));
  set("long","這是一位風度翩翩的公子。\n");
  set("gender", "男性");
  set("combat_exp", 30000);

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
     command("say 我的年齡也不小了，不知道誰家的姑娘肯嫁給我呢？");
     break;
    case 1:
     command("say 憑我的才華風度，找一個漂亮的姑娘還不是輕而易舉。");
   }
   
}

