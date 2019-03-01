// npc: /d/xingxiu/herdsman.c
// Jay 3/18/96

inherit NPC;

void create()
{
        set_name("牧羊人", ({ "muyang ren", "ren", "heardsman" }));
        set("gender", "男性");
        set("age", 60 + random(10));

        set("long", "一個維吾爾族老漢，趕着幾十只羊。\n");

        set("attitude", "friendly");

        set("combat_exp", 1000);
        set("shen_type", 1);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("whip", 20);

        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set("inquiry", ([
                "星宿派" : "他們躲在星宿海。",
                "星宿海" : "星宿海在深澗西邊。\n",
                "深澗" : "我沒過去過。聽説只有採藥的和星宿派弟子能徒手過去。\n",
        ]) );

        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
              "牧羊老漢傷心地説道：那幫星宿派弟子昨天又搶了我一隻羊。\n",
              "牧羊老漢呆呆的望着羊羣發起愣來了。\n",
        }) );

        carry_object(__DIR__"obj/wcloth")->wear();
        carry_object(__DIR__"obj/bian")->wield();
}

