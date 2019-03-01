// yang.c 

inherit NPC;

void create()
{
        set_name("楊蓮亭", ({ "yang lianting", "yang" }));
        set("long","他身形魁梧，滿臉虯髯，形貌極為雄健。\n");
        set("title", "日月神教成德堂總管");
        set("gender", "男性");
        set("age", 40);
        set("per", 29);

        set("max_qi",500);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 10);

        set("combat_exp", 50000);
        set("shen_type", -1);
        setup();
        add_money("silver", 50);
        carry_object("/d/heimuya/npc/obj/yaoshi");
        carry_object("/d/heimuya/npc/obj/zaohong")->wear();
}
