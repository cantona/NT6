// lady1.c

inherit NPC;

void create()
{
        set_name("無錫女孩",({ "girl" }) );
        set("gender", "女性" );
        set("age", 16);
        set("long", 
"這是個十六、七歲的無錫女孩，清麗絕俗，一臉溫柔的顏色。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 200);
//        set("shen", 100);
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
