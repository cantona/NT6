// little_monkey.c

inherit NPC;

void create()
{
        set_name("小猴",({ "little monkey", "monkey"}) );
        set("gender", "雄性");
        set("race", "野獸");
        set("age", 1);
        set("long", "這是一隻調皮的小猴子，雖是畜牲，卻喜歡模仿人樣。\n");
        set("combat_exp", 500);
        set("shen_type", -1);
        set("str", 11);
        set("dex", 11);
        set("con", 11);
        set("int", 11);
        set("attitude", "peaceful");
        setup();
}