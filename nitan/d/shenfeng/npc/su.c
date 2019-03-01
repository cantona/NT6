inherit NPC;

void create()
{
        set_name("蘇普", ({ "su pu", "su", "pu" }));
        set("gender", "男性");
        set("age", 23);
        set("long", "一個年輕的哈薩克牧羊人，哈薩克第一勇士蘇魯克的兒子。\n");
        set("attitude", "friendly");
        set("combat_exp", 30000);
        set("shen_type", 1);
        set("shen", 3000);
        set("str", 36);
        set("int", 20);
        set("con", 24);
        set("dex", 20);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 80);
        set_skill("unarmed", 100);
        set_skill("blade", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_temp("apply/attack", 60);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 60);
        set("inquiry", ([
                    "阿曼" : "她是我老婆，怎麼著？不服咱們就摔摔跤。\n",
                    "李文秀" : "嘆，不知她上哪兒去了。這麼多年我一直沒法忘了她。\n",
                    "計老人" : "計老人會釀又香又烈的美酒，會醫牛羊馬匹的疾病。\n",
        ]) );

        setup();
        carry_object(__DIR__"obj/duandao")->wield();
        carry_object(__DIR__"obj/ycloth")->wear();
}