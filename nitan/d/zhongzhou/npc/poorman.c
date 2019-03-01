inherit NPC;

void create()
{
        set_name("窮漢", ({ "qong han","han"}) );
        set("gender", "男性" );
        set("age", 33);
        set("long", "一個窮困潦倒的漢子。\n");
        set("attitude", "friendly");
        set("combat_exp", 5000);
        set("shen_type", 1);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 15);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
