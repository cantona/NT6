// monkey.c

inherit NPC;

void create()
{
        set_name("山猴",({"monkey", "houzi", "hou"}) );
        set("race", "野獸");
        set("gender", "雄性" );
        set("age", 15);
        set("long", "這是一只兇悍的山猴。\n");
        set("combat_exp", 20000);
        set("str", 25);
        set("dex", 25);
        set("con", 25);
        set("int", 25);
        set("attitude", "heroism");

        set("max_qi",800);
        set("qi",800);
        set("max_jingli",800);
        set("jingli",800);
        
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "knock", "hoof" }) );

        set_temp("apply/damage", 20);
        set_temp("apply/armor", 20);

        setup();
}