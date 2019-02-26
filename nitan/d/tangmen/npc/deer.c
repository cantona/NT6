// yelu.c 野鹿

inherit NPC;

void create()
{
        set_name( "野鹿", ({ "ye lu", "lu", "deer"}) );
        set("race", "野獸");
        set("age", 2 + random(3));
        set("long", "一隻滿身斑點的小野鹿，不停的蹦蹦跳跳。\n");
        set("attitude", "peaceful");
        set("str",30);
        set("max_qi",500);
        set("qi",500);
        set("max_jingli",800);
        set("jingli",800);
        
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "knock", "hoof" }) );

        set("combat_exp", 30000);

        set_temp("apply/attack", 90);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 70);

        setup();
}