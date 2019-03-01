// bing.c 官兵

inherit NPC;

void create()
{
        set_name("驛兵", ({ "yi bing", "bing" }));
        set("age", 22);
        set("gender", "男性");
        set("long","他就是管這個馬站的兵士。雖然不打戰，脾氣好，也不能隨便招惹哦。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 16);
        set("combat_exp", 10000);
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(ARMOR_DIR"junfu")->wear();
}