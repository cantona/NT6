// popo.c
// Last Modified by Winder on Jul. 15 2000

inherit NPC;
void create()
{
        set_name("老婆婆", ({ "lao popo","old","popo" }) );
        set("title", "平民" );
        set("gender", "女性" );
        set("age", 65);
        set("combat_exp",100);
        set("long","這老婆婆看起來慈眉善目，特別可親。\n");
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin",100);
}