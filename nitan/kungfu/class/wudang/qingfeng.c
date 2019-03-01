// qingfeng.c

inherit NPC;

void create()
{
        set_name("清風", ({ "qing feng", "qing", "feng" }));
        set("long", "他是武當山的小道童。\n");
        set("gender", "男性");
        set("age", 16);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "taoist");

        set("str", 20);
        set("int", 20);
        set("con", 22);
        set("dex", 25);
        
        set("max_qi", 150);
        set("max_jing", 100);
        set("neili", 150);
        set("max_neili", 150);

        set("combat_exp", 5000);
        set("score", 1000);

        set_skill("force", 30);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_skill("parry", 20);
        set_skill("wudang-quan", 20);
        map_skill("parry", "wudang-quan");
        map_skill("unarmed", "wudang-quan");
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 5);
        set("inquiry", ([
                "清風" : "貧道便是清風。",
                "武當" : "貧道便是武當派弟子。",
                "武當派" : "貧道便是武當派弟子。",
                "張無忌" : "小師叔？唉，不知道他現在病好了沒有，大家都好生掛念他。",
                "張三豐" : "祖師爺就在裡面，不知你是否有要事找我們祖師爺?",
        ]));

        create_family("武當派", 5, "弟子");
        setup();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}
