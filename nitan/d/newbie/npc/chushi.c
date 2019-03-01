inherit NPC;

void create()
{
        set_name("廚師", ({ "chu shi", "chu", "shi" }));
        set("long", "古村的廚師，你可以問他要(yao)一些吃的。\n");
        set("gender", "男性");
        set("age", 50);
        set("combat_exp", 7500);
        set_skill("unarmed", 35);
        set_skill("force", 35);
        set_skill("dodge", 40);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 40);

        setup();
        carry_object("/clone/misc/cloth")->wear();
}