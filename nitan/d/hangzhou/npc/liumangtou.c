// liumangtou.c 流氓頭

inherit NPC;

void create()
{
        set_name("流氓頭", ({ "liumang tou", "liumang", "liu" }));
        set("gender", "男性");
        set("age", 25);
        set("long", "他長得奸嘴猴腮的，一看就不像是個好人。\n");
        
        set("combat_exp", 7000);
        set("shen_type", -1);
        set("attitude", "peaceful");
        
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 2);
}
