// nongfu1.c

inherit NPC;

void create()
{
        set_name("台夷農婦",({ "nong fu", "fu" }) );
        set("gender", "女性" );
        set("age", 22);
        set("long", "一位年輕的台夷農婦，在田裡辛勤地勞作著。\n");
        set_temp("apply/defense", 15);
        set("combat_exp", 700);
        set("shen_type", 1);
        set("per", 18);
        set("str", 24);
        set("dex", 25);
        set("con", 36);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/tongqun")->wear();
}
