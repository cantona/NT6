// yingying.c 崔鶯鶯

inherit NPC;

void create()
{
        set_name("崔鶯鶯", ({ "cui yingying", "cui", "ying" }));
        set("long", "她長得極美，尤其是那對眼睛，媚得直可以勾人魂魄。\n");
        set("title", "財主女兒");
        set("gender", "女性");
        set("age", 17);

        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 5);

        set("combat_exp", 20000);
        set("shen_type", 1);
        setup();
        carry_object("/d/city/npc/obj/necklace")->wear();
        carry_object("/d/city/npc/obj/pink_cloth")->wear();
}
        