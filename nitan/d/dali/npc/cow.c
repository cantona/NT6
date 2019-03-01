// cow.c

inherit NPC;

void create()
{
        set_name("水牛", ({ "shui niu", "niu" }));
        set("long","一頭南方山區常見的水牛，是耕作的主力，也用來拉車載物。由於水草茂盛，長得十分肥壯。\n");
        set("race", "家畜");
        set("age", 5);
        set("int", 30);
        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("shen_type", 0);
        set("combat_exp",50000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "腹部", "尾巴","後腿","前腿" }) );
        set("verbs", ({ "bite","hoof" }) );
        set_temp("apply/attack", 50);
        set_temp("apply/armor", 15);
        set_temp("apply/damage", 25);

        setup();
}
