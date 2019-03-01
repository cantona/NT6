inherit NPC;

void create()
{
        set_name("王府親兵", ({ "qin bing", "qin", "bing" }));
        set("age", 32);
        set("gender", "男性");
        set("long", "一名盡忠職守的親兵，警惕的注視著過往的人。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 23);
        set("combat_exp", 100000);
        set("shen_type", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("sword", 60);
        set_skill("force", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/defense", 60);
        set_temp("apply/damage", 60);
        set_temp("apply/armor", 60);


        setup();
        carry_object(__DIR__"obj/changjian")->wield();
        carry_object(__DIR__"obj/armor")->wear();
}

