// girl.c

inherit NPC;

void create()
{
        set_name("女孩",({ "girl" }) );
        set("gender", "女性" );
        set("age", 12);
        set("long", 
"這是個平民少女，只有十二、三歲，身材已經很成形了。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 70);
//        set("shen", 100);
        set("shen_type", 1);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
