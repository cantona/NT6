// tongzi.c 錦衣童子

inherit NPC;

void create()
{
        set_name("錦衣童子", ({ "tong zi", "tong" }));
        set("age", 15);
        set("gender", "男性");
        set("long", "一個眉清目秀的童子，別看他年紀不大，已深得五毒教真傳。\n");
        set("attitude", "peaceful");
       set("max_qi",600);
        set("str", 25);
        set("dex", 25);
        set("combat_exp", 40000);
        set("shen_type", -1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("sword", 60);
        set_skill("force", 60);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 60);

        setup();
        carry_object(__DIR__"obj/jinyi")->wear();
}