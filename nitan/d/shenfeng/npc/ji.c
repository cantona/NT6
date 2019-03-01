inherit NPC;

void create()
{
        set_name("計老人", ({ "ji laoren", "ji" , "laoren" }));
        set("gender", "男性");
        set("age", 70);
        set("long", "他滿頭白發，竟無一根是黑的。身材甚是高大，只\n"
                    "是弓腰曲背衰老已極。\n");
        set("attitude", "friendly");
        set("combat_exp", 10000);
        set("shen_type", 1);
        set("shen", 1000);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 24);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 10);
        set_skill("unarmed", 50);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 15);
        set("inquiry", ([
                "李文秀" : "這孩子真是命苦。",
        ]));

        setup();

        carry_object(__DIR__"obj/ycloth")->wear();
}