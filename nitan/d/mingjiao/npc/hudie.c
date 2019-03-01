// hudie.c

inherit NPC;

void create()
{
        set_name("蝴蝶", ({ "hudie"}) );
        set("race", "野獸");
        set("age", 3);
        set("long", "一只五顏六色的蝴蝶，十分可愛，是蝴蝶的珍品。\n");

        set("limbs", ({ "頭部", "身體", "前爪", "後爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 100);
    
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 10);

        setup();
}
