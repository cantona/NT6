// 大唐雙龍傳


inherit NPC;

void create()
{
  set_name("李夫人", ({"li furen","li","furen"}));
  set("long","這是李夫人，正在忙著抓藥。\n");
  set("gender", "女性");
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
     command("say 大夫，請快點好嗎？我家人病的很重。");
     break;
    case 1:
     command("say 這陣子疾病流行，真是倒霉。");
   }
   
}

