// shizhe1.c

inherit NPC;

void create()
{
        set_name("侍者", ({ "waiter","zhe"}) );
        set("gender", "男性" );
        set("age", 14);
        set("long", "一個身着黃衣的漢子。\n");
        set("shen_type", 1);
        set("combat_exp", 3000);
        set("str", 20);
        set("dex", 25);
        set("con", 20);
        set("int", 25);
        set("attitude", "friendly");
        create_family("俠客島", 2, "弟子");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

