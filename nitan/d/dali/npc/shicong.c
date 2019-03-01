// shicong.c

inherit NPC;

void create()
{
        set_name("侍從", ({ "shi cong", "shi", "cong" }));
        set("age", 32);
        set("gender", "男性");
        set("long", "這位倒也打扮的利索，一身短打，白布包頭，翹起的褲腿，一雙
潔白的布鞋，格外醒目。他正準備出去籌備白尼族一年一度的大會。\n");
        set("attitude", "peaceful");

        set("str", 24);
        set("per", 20);
        set("dex", 16);
        set("combat_exp", 20000);
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 100);
        set_skill("parry", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
