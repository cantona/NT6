// yuanwai.c
inherit NPC;

void create()
{
        set_name("侯員外", ({ "hou yuanwai", "hou" }));
        set("long",
                "侯員外據説是這長安鎮上的首富，誰也不知道他到底有多少\n"
                "家財。他大約五十出頭，長的富富態態。\n");
        set("gender", "男性");
        set("age", 52);

        set("combat_exp", 12000);
        set_skill("unarmed", 45);
        set_skill("force", 42);
        set_skill("dodge", 35);
        set_temp("apply/attack", 35);
        set_temp("apply/defense", 42);

        setup();
        carry_object(__DIR__"obj/jinduan")->wear();
        add_money("silver",120);
}
