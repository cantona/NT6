// caisunren.c

inherit NPC;

void create()
{
        set_name("採筍人",({ "caisun ren", "ren" }) );
        set("gender", "女性" );
        set("age", 22);
        set("long", "一個盧鹿部的青年台夷婦女，背後背了個竹筐，手拿一把砍柴刀，來採竹筍。\n");
        set_temp("apply/defense", 15);
        set("combat_exp", 170);
        set("shen_type", 1);
        set("per", 18);
        set("str", 24);
        set("dex", 25);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/tongqun")->wear();
        carry_object("/d/dali/npc/obj/kandao")->wield();
}
