inherit NPC;

void create()
{
        set_name("農民", ({ "nong min", "nong", "min" }));
        set("gender", "男性" );
        set("age", 29);
        set("long", "一個很健壯的壯年農民。\n");
        set("shen_type", 1);
        set("combat_exp", 2000);
        set("str", 20);
        set("dex", 18);
        set("con", 18);
        set("int", 18);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin", 10);
}