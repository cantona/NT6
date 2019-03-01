// lu.c
inherit NPC;
void create()
{
        set_name("梅花鹿", ({ "meihua lu", "lu" }) );
        set("race", "野獸");
        set("age", 5);
        set("long", "一只溫順可愛的梅花鹿。\n");
        set("limbs", ({ "頭部", "身體", "前爪", "後爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 1000);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);
        setup();
}
