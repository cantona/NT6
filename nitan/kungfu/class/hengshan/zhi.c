// Last Modified by Sir on May. 22 2001
// zhi.c
inherit NPC;
inherit F_MASTER;

#include <ansi.h>;
#include "hengshan.h";

void create()
{
        set_name("儀質", ({ "yi zhi", "zhi" }) );
        set("long", "她是一位年青女尼，慈眉善目。\n");
        set("gender", "女性");
        set("class", "bonze");
        set("age", 25);
        set("attitude", "peaceful");
        set("per", 24);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 30);
        set("max_qi", 2000);
        set("max_jing", 800);
        set("combat_exp", 500000);
        set("shen_type", 1);

        set_skill("unarmed", 90);
        set_skill("sword", 100);
        set_skill("force", 90);
        set_skill("parry", 90);
        set_skill("dodge", 100);
        set_skill("strike", 90);
        set_skill("hand", 90);
        set_skill("buddhism", 100);
        set_skill("baiyun-xinfa",90);
        set_skill("hengshan-jian", 150);
        set_skill("chuanyun-shou",120);
        set_skill("tianchang-zhang",120);
        set_skill("lingxu-bu", 150);

        map_skill("force","baiyun-xinfa");
        map_skill("sword", "hengshan-jian");
        map_skill("strike","tianchang-zhang");
        map_skill("hand","chuanyun-shou");
        map_skill("parry", "hengshan-jian");
        map_skill("dodge", "lingxu-bu");
        prepare_skill("strike", "tianchang-zhang");
        prepare_skill("hand", "chuanyun-shou");
        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.yuyin" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );

        create_family("恆山派", 14, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)>10000 && query("family/family_name", ob) != "恆山派" )
        {
                command("say 我恆山派注重清修，對弟子要求能忍受寂寞。");
                command("say 在江湖閱歷方面，" + RANK_D->query_respect(ob) +
                        "經歷豐富，是否能在恆山修道？");
                return;
        }
        if( query("shen", ob)<0){
                command("say 我恆山乃是堂堂五岳劍派之一，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }
        if( query("gender", ob) != "女性" )
        {
                command("say 我恆山只收女徒。");
                return;
        }
        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}
