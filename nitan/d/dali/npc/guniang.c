// guniang.c

inherit NPC;

void create()
{
        set_name("台夷姑娘",({ "gu niang", "girl" }) );
        set("gender", "女性" );
        set("age", 17);
        set("long", "一位年輕的台夷姑娘，上著無領襯花對襟，下穿五色筒裙。\n");
         set_temp("apply/defense", 5);
        set("combat_exp", 7000);
//        set("shen", 100);
        set("shen_type", 1);
        set("per", 28);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/tongqun")->wear();
}