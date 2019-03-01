// jisi.c

inherit NPC;

void create()
{
        set_name("祭司", ({ "ji si", "si" }));
        set("age", 62);
        set("gender", "女性");
        set("long", "一位滿臉皺紋的老年婦女，是本村的大祭司，常年司守祭台。台夷時處母系氏族，祭司要職皆為婦女。\n");
        set("attitude", "peaceful");

        set("str", 20);
        set("per", 12);
        set("dex", 16);
        set("combat_exp", 40000);
        set("shen_type", 1);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("blade", 20);
        set_skill("force", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        setup();
        carry_object("/d/dali/npc/obj/tongqun")->wear();
}
