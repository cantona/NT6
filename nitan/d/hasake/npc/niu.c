inherit NPC;

void create()
{
    set_name("牛", ({ "niu" }) );
        set("race", "野獸");
        set("age", 5);
    set("long", "一頭健壯的牛。\n");
        set("attitude", "peaceful");
        
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
    set("verbs", ({ "kick", "bite" }) );

    set("max_qi", 300);
    set("max_jing", 100);
    set("eff_jingli", 100);

    set("combat_exp", 1200);
        
    set_temp("apply/attack", 5);
        set_temp("apply/defense", 10);
    set_temp("apply/damage", 5);
    set_temp("apply/armor", 5);

        setup();
}
