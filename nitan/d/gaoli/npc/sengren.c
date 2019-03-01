// 大唐雙龍傳
 
// girl.女子。

inherit NPC;

void create()
{
  set_name("僧人", ({"seng ren","seng","ren"}));
  set("long","這是靈靜寺的僧人，在這裡掌管寺內事物。\n");
  set("gender", "男性");
  set("class","bonze");
  set("combat_exp", 90000);
  set("age", 18);
  set("attitude", "friendly");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  setup();
  carry_object("/d/gaoli/obj/sengyi")->wear();
}


