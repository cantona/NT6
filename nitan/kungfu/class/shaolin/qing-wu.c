// Npc: /kungfu/class/shaolin/qing-wu.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

#define DEFINED_ATTEMPT_APPRENTICE

#include "qing.h"

void create()
{
        set_name("清無比丘", ({
                "qingwu biqiu",
                "qingwu",
                "biqiu",
        }));
        set("long",
                "他是一位體格強健的壯年僧人，他身得虎背熊腰，全身似乎蘊含\n"
                "著無窮勁力。他身穿一襲白布黑邊袈裟，似乎身懷武藝。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 30);
        set("shen_type", 1);
        set("str", 23);
        set("int", 17);
        set("con", 20);
        set("dex", 24);
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
        set_skill("blade", 30);
        set_skill("cibei-dao", 30);
        set_skill("parry", 30);
        set_skill("buddhism", 30);
        set_skill("literate", 30);

        map_skill("force", "shaolin-xinfa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("blade", "cibei-dao");
        map_skill("parry", "cibei-dao");

        create_family("少林派", 40, "弟子");

        set("master_ob",1);
        setup();

        carry_object("/d/shaolin/obj/jiedao")->wield();
        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query("gender", ob) != "男性" )
        {
                command ("say 阿彌陀佛！女施主呀，貧僧可不敢開這等玩笑啊。");
                return;
        }
        
        if (! permit_recruit(ob))
                return;

        if( query("class", ob) != "bonze" )
        {
                command ("say 阿彌陀佛！貧僧就收下你做『俗家弟子』了。");
        }
        command("say 阿彌陀佛，善哉！善哉！");
        command("recruit "+query("id", ob));
}