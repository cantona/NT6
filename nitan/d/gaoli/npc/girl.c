// 大唐雙龍傳
 
// girl.女子。

inherit NPC;

void create()
{
  set_name("小姐", ({"girl"}));
  set("long","這是高麗的一個小姐，正在這裡閒逛。\n");
  set("gender", "女性");
  set("combat_exp", 3000);
  set("age", 18);
  set("per", 29);
  set("attitude", "friendly");
  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  set("inquiry",([
    "真冰河":"他啊，他也是高麗人呢，你們不知道嗎？！\n",
    "yanyan":"他其實是朝鮮人，也就是現在的高麗人。\n",
    ]));
  setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}


