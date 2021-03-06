// Npc: /kungfu/class/shaolin/qing-xiao.c
// Date: YZC 96/01/19

inherit NPC;


void create()
{
        set_name("清曉比丘", ({
                "qingxiao biqiu",
                "qingxiao",
                "biqiu",
        }));
        set("long",
                "他是一位體格強健的壯年僧人，他身得虎背熊腰，全身似乎藴含\n"
                "着無窮勁力。他身穿一襲白布黑邊袈裟，似乎身懷武藝。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 30);
        set("shen_type", 1);
        set("str", 23);
        set("int", 21);
        set("con", 18);
        set("dex", 22);
        set("max_qi", 350);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("shaolin-xinfa", 30);
        set_skill("dodge", 30);
        set_skill("shaolin-shenfa", 30);
        set_skill("claw", 35);
        set_skill("longzhua-gong", 35);
        set_skill("parry", 30);
        set_skill("buddhism", 30);
        set_skill("literate", 30);

        map_skill("force", "shaolin-xinfa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "longzhua-gong");

        prepare_skill("claw", "longzhua-gong");

        create_family("少林派", 40, "弟子");

        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}


#include "/kungfu/class/shaolin/qing.h"
