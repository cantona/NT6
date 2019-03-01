inherit NPC;

void create()
{
        set_name("窈娘", ({ "yao niang", "yao", "niang" }) );
        set("gender", "女性" );
        set("long", "窈娘是白自在的妾侍，很得白自在寵信。\n");
        set("age", 17);
        set("max_qi", 800);
        set("max_jing", 500);
        set("combat_exp", 10000);

        set("str", 16);
        set("con", 24);
        set("dex", 30);
        set("int", 27);

        set("attitude", "friendly");
        set("inquiry", ([
                    "白自在" : "老爺子不知為什麼，把自己關到監獄裡。說是思什麼過。",
                    "監獄"   : "沒少爺同意，你是進不去的。",
        ]) );

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}


