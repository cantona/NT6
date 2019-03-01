// bee.c
inherit NPC;

void create()
{
        set_name("蜜蜂", ({ "bee" }) );
        set("race", "昆蟲");
        set("subrace", "飛蟲");
        set("age", 1);
        set("long", "一隻瘋狂的殺人蜂。\n");

        set("limbs", ({ "頭部", "身體", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set_skill("dodge", 50);
        set("combat_exp", 500);
        set("bellicosity", 3000 );

        setup();
}
