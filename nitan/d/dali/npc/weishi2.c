// weishi2.c

inherit NPC;

void create()
{
        set_name("錦衣衛士", ({ "wei shi", "shi", "wei" }));
        set("age", 32);
        set("gender", "男性");
        set("long", "這是位錦衣衛士，身著錦衣，手執鋼刀，雙目精光炯炯，警惕地巡視著四周的情形。\n");
        set("attitude", "peaceful");

        set("str", 24);
        set("per", 24);
        set("dex", 16);
        set("combat_exp", 30000);
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 100);
        set_skill("parry", 40);
        set_skill("blade", 100);
        set_skill("force", 40);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/d/dali/npc/obj/jjunfu")->wear();
}