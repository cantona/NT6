// 大唐雙龍傳


inherit NPC;

void create()
{
  set_name("王公子", ({"wang gongzi","wang","gongzi"}));
  set("long","這是一位勤學好問的公子。\n");
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
     command("say 這篇文章我有不同的看法，誰能與我交流一下？");
     break;
    case 1:
     command("say 書中自有黃金屋，這句話是一點也會錯的。");
   }
   
}

