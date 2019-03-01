// wangwu.c 王五

inherit NPC;

void create()
{
        set_name("王五", ({ "wang wu", "wang" }));
        set("long",
                "他大約二十多歲，精明能幹，笑嘻嘻的和藹可親。但卻嫉惡如仇，性如烈火。\n");
        set("gender", "男性");
        set("age", 25);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 35);
        set("con", 27);
        set("dex", 28);

        set("inquiry",([
            "here" : "這裡當然就是俠客島啦",
            "俠客行" : "往南面走，進山後就明白了",
            "臘八粥":"\n去找龍島主看看你的緣分吧。\n",
//                 "石破天":"\n他是我的結拜兄弟呀，他也在這呢。\n",
//                 "賞善罰惡令":"\n這是我們兄弟的信物。\n",
        ]) );
        set("max_qi", 2000);
        set("qi", 2000);
        set("max_jing", 2000);
        set("jing", 2000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);
        set("combat_exp", 3000000);
        set("score", 60000);

        set_skill("force", 150);
        set_skill("taiji-shengong", 150);
        set_skill("dodge", 150);
        set_skill("lingxu-bu", 150);
        set_skill("unarmed", 150);
        set_skill("taiji-quan", 200);
        set_skill("parry", 150);
        set_skill("sword", 150);
        set_skill("taiji-jian", 200);
        set_skill("taoism", 100);
        set_skill("literate", 100);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "lingxu-bu");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");

        create_family("俠客島", 2, "弟子");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}
