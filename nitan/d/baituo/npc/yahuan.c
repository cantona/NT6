inherit NPC;

void create()
{
        set_name("丫環", ({ "ya huan", "ya", "huan" }));
        set("gender", "女性" );
        set("age", 14);
        set("long", "一個很能幹的丫環。\n");
        set("shen_type", 1);
        set("combat_exp", 300);
        set("str", 18);
        set("dex", 18);
        set("con", 18);
        set("int", 19);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
