// Npc: /kungfu/class/shaolin/hui-he.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("慧合尊者", ({
                "huihe zunzhe",
                "huihe",
                "zunzhe",
        }));
        set("long",
                "他是一位兩鬢斑白的老僧，身穿一襲青布鑲邊袈裟。他身材略高，\n"
                "太陽穴微凸，雙目炯炯有神。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 50);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 450);
        set("max_jing", 300);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 50);
        set("combat_exp", 50000);
        set("score", 100);

        set_skill("force", 70);
        set_skill("hunyuan-yiqi", 70);
        set_skill("shaolin-xinfa", 70);
        set_skill("dodge", 70);
        set_skill("shaolin-shenfa", 70);
        set_skill("finger", 68);
        set_skill("nianhua-zhi", 68);
        set_skill("parry", 70);
        set_skill("sword", 80);
        set_skill("damo-jian", 80);
        set_skill("buddhism", 70);
        set_skill("literate", 70);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("parry", "damo-jian");
        map_skill("sword", "damo-jian");

        prepare_skill("finger", "nianhua-zhi");

        create_family("少林派", 38, "弟子");

        set("inquiry", ([
                "買鐵" :    (: ask_me :),
        ]));

        set("master_ob",2);
        setup();

        carry_object("/d/shaolin/obj/changjian")->wield();
        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}

#include "hui.h"

string ask_me()
{
        return "買鐵？ 他現在又不缺鐵！ 前天老喬不是剛送來一堆鐵塊，鐵手掌什麼的給他嗎？！";
}