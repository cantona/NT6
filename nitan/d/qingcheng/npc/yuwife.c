// yuwife.c

inherit NPC;

void create()
{
        set_name("余小星",({ "yu wife"}) );
        set("gender", "女性" );
        set("age", 26);
        set("long", 
"這是個二十六、七歲的川妹子，不知道是余老道的第幾房小妾。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 70);
        set("shen_type", 1);
        set("str", 14);
        set("per", 28);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/female-cloth")->wear();
}
