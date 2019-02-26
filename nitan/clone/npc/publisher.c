inherit NPC;

void create()
{
        set_name("王老闆", ({ "wang laobang", "publisher", "wang"}));
        set("long", "這是一位白白胖胖的中年人，身子微微發福，是個富商豪紳模樣。\n"
                "他手中提着一個小箱子，正笑眯眯地上下打量着你。\n"
                "據説他曾經試過科舉，但幾次不中後便改行以販書為業了。\n");
        set("gender", "男性");
        set("age", 45);
        set("str", 25);
        set("dex", 25);
        set("attitude", "peaceful");

        set("combat_exp", 75000);
        set("shen_type", 0);

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("literate", 300);

        set("neili", 4000); 
        set("max_neili", 4000);
        set("jiali", 500);

        setup();
        carry_object("/clone/cloth/cloth")->wear();

}
