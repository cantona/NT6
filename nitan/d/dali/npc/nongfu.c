// nongfu.c

inherit NPC;

void create()
{
        set_name("農夫",({ "nong fu", "fu" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "一位烏夷族的農夫，束髮總於腦後，用布紗包着，上半身裸露，下著獸皮。\n");
        set_temp("apply/defense", 15);
        set("combat_exp", 1700);
        set("shen_type", 1);
        set("per", 18);
        set("str", 24);
        set("dex", 25);
        set("con", 36);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/wdahui")->wear();
}
