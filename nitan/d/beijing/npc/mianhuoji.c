inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("面館伙計", ({ "mianguan huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18+random(20));
        set("long", "他是小面館的伙計。\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
}