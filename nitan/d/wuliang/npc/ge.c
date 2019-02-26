// Npc: /ge.c
// Date: Oct.18 1999 by Winder

inherit NPC;
string ask_me();
void create()
{
        set_name("葛光佩", ({ "ge guangpei", "ge", "guangpei"}));

        set("long" ,"她長着一張鵝蛋臉，左頰上有幾粒白麻子，倒也頗有幾分姿色。\n");
        set("gender", "女性");
        set("attitude", "friendly");

        set("age", 18);
        set("shen_type", -1);
        set("per", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 500);
        set("max_jing", 500);
        set("neili", 550);
        set("max_neili", 550);
        set("jiali", 40);
        set("combat_exp", 50000);
        set("score", 100);

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_skill("changquan", 40);
        set_skill("parry", 40);
        set_skill("damo-jian", 40);
        set_skill("sword", 40);

        map_skill("unarmed", "changquan");
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");
        set("inquiry", ([
                "幹光豪"    : (: ask_me :),
                "狗男女"    : (: ask_me :),
                "姦夫淫婦"  : (: ask_me :),
                "忘八"      : (: ask_me :),
                "無量玉壁"  : "那是本派禁地，任何外人不得擅入。干犯禁忌，可叫你死葬身之地。",
        ]));

        create_family("無量劍西宗", 5, "弟子");
        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

string ask_me()
{
        set_temp("marks/wuliang", 1, this_player());
        return "既然被你撞破了我們的好事，也不用我們動手，自己到懸崖了斷吧。";
}
