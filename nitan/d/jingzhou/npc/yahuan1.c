// yahuan1.c
//
inherit NPC;
void create()
{
        set_name("丫鬟",({ "girl" }) );
        set("gender", "女性" );
        set("age", 15);
        set("long","她是知府大人的丫鬟，大約十四、五歲，清麗絕俗，一臉温柔的顏色。\n");
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