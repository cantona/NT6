// wenyoudao.c
#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("温有道", ({ "wen youdao", "wen" ,"youdao"}));
        set("gender", "無性");
        set("title", HIC"御書房太監"NOR);
        set("age", 16);
        set("long", "一個文弱的小太監，和他兄弟温有方共司御書房。\n");

        set("combat_exp", 1000);
        set("shen_type", 0);
        set("per", 20);

        set_skill("unarmed", 10);
        set_skill("blade", 10);
        set_skill("parry", 10);
        set_skill("dodge", 10);
        
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 20);

        setup();
        add_money("silver", random(10));
        carry_object(__DIR__"obj/tjcloth")->wear();
}
        