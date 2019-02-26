// little_monkey.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("小猴",({ "little monkey", "monkey"}) );
        set("race", "走獸");
        set("gender", "雄性" );
        set("age", 7);
        set("long", "這是一隻調皮的小猴子，雖是畜牲，卻喜歡模仿人樣。\n");
        set("combat_exp", 50);
        set("shen_type", -1);
        set("str", 11);
        set("dex", 11);
        set("con", 11);
        set("int", 11);
        set("attitude", "peaceful");
        setup();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}