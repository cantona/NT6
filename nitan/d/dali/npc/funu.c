// funu.c

inherit NPC;

void create()
{
    set_name("台夷婦女",({ "fu nv", "woman" }) );
        set("gender", "女性" );
        set("age", 37);
        set("long", "一位中年的台夷婦女，上着無領襯花對襟，下穿五色筒裙，正在編織漁網。\n");
         set_temp("apply/defense", 5);
        set("combat_exp", 3000);
        set("shen_type", 1);
        set("per", 20);
        set("str", 24);
        set("dex", 25);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/tongqun")->wear();
}
