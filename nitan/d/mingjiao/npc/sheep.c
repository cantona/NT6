// sheep.c

inherit NPC;

void create()
{
    set_name("野羊", ({ "sheep" }) );
    set("gender", "雄性");
    set("race", "家畜");
    set("age", 2);
    set("long",
        "這隻野羊在低頭吃草，見了人也不驚避。\n");
    set("combat_exp", 5000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "羊角", "前蹄", "後蹄" }) );
    set("verbs", ({ "hoof" }) );

    set("water", 200);
    set("food", 200);

    set("apply/attack", 10);
    set("apply/defense", 10);

    setup();
}
