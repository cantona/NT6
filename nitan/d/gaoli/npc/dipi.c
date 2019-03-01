// 大唐雙龍傳


inherit NPC;

void create()
{
  set_name("地痞", ({"di pi","pi"}));
  set("long","這是一個地痞，到處搗亂打架。\n");
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
     command("say 高麗的地頭我說了算，有事找我就行了！");
     break;
    case 1:
     command("say 今天還要去收保護費，不然就沒飯吃了。");
   }
   
}

