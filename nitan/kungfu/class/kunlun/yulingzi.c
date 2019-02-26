// yulingzi.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include "kunlun.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("玉靈子", ({ "yuling zi","yuling", "zi" }));
        set("long",
                "她崑崙派第五代弟子，容顏俏麗，身材豐滿，舉手投足間帶着點挑逗之意。\n");
        set("gender", "女");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 26);
        set("str", 30);
        set("int", 23);
        set("con", 25);
        set("dex", 28);

        set("max_qi", 850);
        set("max_qi", 850);
        set("max_jing", 600);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 30);
        set("combat_exp", 380000);
        set("score", 4000);

        set_skill("force", 95);
        set_skill("xuantian-wuji", 105);
        set_skill("dodge", 95);
        set_skill("taxue-wuhen", 125);
        set_skill("parry", 100);
        set_skill("sword", 101);
        set_skill("xunlei-sword", 155);
        set_skill("leg", 90);
        set_skill("chuanyun-leg", 120);
        set_skill("throwing", 80);
        set_skill("mantianhuayu", 95);

        map_skill("force", "xuantian-wuji");
        map_skill("dodge", "taxue-wuhen");
        map_skill("sword", "xunlei-jian");
        map_skill("leg", "chuanyun-leg");
        map_skill("sword", "xunlei-jian");
        prepare_skill("leg", "chuanyun-leg");

        create_family("崑崙派", 5, "弟子");
        set("env/wimpy", 60);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/kunlun/obj/pao3")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "男性" )
        {
                command("fear");
                command("say "+RANK_D->query_respect(ob)+
                        "，師母不准我收男弟子，你去找我師兄去吧。");
                return;
        }

        if(ob->query_skill("xuantian-wuji",1)<60)
        {
                command("hmm");
                command("say "+RANK_D->query_respect(ob)+
                        "你的玄天無極功太差，我可不想收你。");
                return;
        }

        if( query("appren_hezudao", ob) == 1 )
        {
                command("say 前輩怎敢開這等玩笑，真是折殺做晚輩的了。");
                return;
        }
        command("say 既然"+RANK_D->query_respect(ob)+
                "這麼努力，我就收下你吧。");
        command("recruit "+query("id", ob));
}
