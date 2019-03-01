// 大唐雙龍傳
 
//書生。

inherit NPC;

void create()
{
  set_name("書生", ({"shu sheng","shu","sheng"}));
  set("long","這是高麗的一個書生，整天苦讀詩書。\n");
  set("gender", "男性");
  set("combat_exp", 3000);
  set("age", 20);
  set("attitude", "peaceful");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}


