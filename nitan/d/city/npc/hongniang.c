// hongniang.c 紅娘

inherit NPC;

void create()
{
        set_name("紅娘", ({ "hong niang", "hong" }));
        set("long", 
                "她是一個長得很好看的小姑娘。\n"
                "因為被關在此處，臉上露出一絲倦容。\n");
        set("gender", "女性");
        set("age", 16);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 5);

        set("combat_exp", 3000);
        set("shen_type", 1);
        setup();
}