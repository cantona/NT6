//wolf2.c

inherit NPC;

void create()
{
        set_name("狼", ({ "wolf2", "lang" }) );
        set("race", "野獸");
        set("age", 5);
        set("long", "一匹昂首直立，兩眼放着綠光的狼。\n");
        set("attitude", "aggressive");

        set("str", 26);
        set("cor", 30);
        set("limbs", ({ "頭部", "身體", "腿部", "尾巴",}) );
        set("verbs", ({ "bite" }) );

        set("combat_exp", 5000);

        set("chat_chance",50);
        set_temp("apply/attack", 25);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 18);
        set_temp("apply/defence",20);

        setup();
}
