// pihuoshang.c

inherit NPC;

void create()
{
        set_name("皮貨商", ({ "pihuo shang", "shang" }));
        set("age", 32);
        set("gender", "男性");
        set("long", "一位來遠道而來的漢族商人，來此採購皮貨。\n");
        set("attitude", "peaceful");

        set("str", 24);
        set("per", 20);
        set("dex", 16);
        set("combat_exp", 1000);
        set("shen_type", 1);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("blade", 20);
        set_skill("force", 20);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 10);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
