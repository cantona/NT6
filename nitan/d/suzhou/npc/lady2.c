// lady2.c

inherit NPC;

void create()
{
        set_name("蘇州少女",({ "girl" }) );
        set("gender", "女性" );
        set("age", 21);
        set("long", 
"她一臉聰明乖巧，滿口伶牙俐齒。見有人稍微示意，便過去加茶倒水。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 70);
//        set("shen", 100);
        set("shen_type", 1);
        set("str", 14);
        set("per", 28);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
