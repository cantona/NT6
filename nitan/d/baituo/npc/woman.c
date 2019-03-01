inherit NPC;

void create()
{
        set_name("農家婦女", ({ "fu nv", "fu", "nv" }));
        set("gender", "女性" );
        set("age", 32);
        set("long", "一個很精明能幹的農家婦女。\n");
        set("shen_type", 1);
        set("combat_exp", 1200);
        set("str", 15);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin", 5);
}
