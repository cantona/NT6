// wuliangdizi.c

inherit NPC;

void create()
{
        set_name("無量劍弟子", ({ "wuliang dizi", "dizi" }));
        set("age", 42);
        set("gender", "男性");
        set("long", "這是無量劍派的一名弟子，腰挎一柄長劍，神情有些鬼祟，象是懼怕些什麼。\n");
        set("attitude", "peaceful");

        set("str", 24);
        set("per", 20);
        set("dex", 16);
        set("combat_exp", 10000);
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("sword", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
