// guest.c 遊客

inherit NPC;

void create()
{
        set_name("遊客", ({ "youke" }));
        set("gender", "男性");
        set("age", 20 + random(30));

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set("apply/attack", 15);
        set("apply/defense", 15);
        set("apply/damage", 5);
        set("combat_exp", 750);
        set("shen_type", 1);
        setup();
        add_money("silver", 5);
}
        
