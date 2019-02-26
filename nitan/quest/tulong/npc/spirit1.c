inherit NPC;

void create()
{
        set_name("小精靈", ({ "spirit" }) );
        set("race", "人類");
        set("age", 5);
        set("long", 
"一隻長着透明羽翼的小精靈，在忽上忽下地飛舞，看上去似乎不難抓(catch)到。\n");
        set("max_qi", 90);
        set("limbs", ({ "頭部", "身體" }) );
        set("verbs", ({ "bite" }) );

        set_skill("dodge", 100); 
        set_skill("spirit-dodge", 100);
        map_skill("dodge", "spirit-dodge");
        setup();
}
