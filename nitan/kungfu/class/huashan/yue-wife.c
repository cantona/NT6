// This program is a part of NITAN MudLIB
// yue-wife.c 嶽夫人

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include "qizong.h"

void create()
{
        set_name("甯中則", ({ "ning zhongze", "ning", "zhongzhe", "yue wife" }) );
        set("nickname", "淑女劍");
        set("gender", "女性");
        set("class", "swordsman");
        set("age", 50);
        set("long", "嶽夫人原姓寧，閨名甯中則，"
                    "是嶽不羣的師妹，也是他的妻子。\n");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 24);
        set("int", 25);
        set("con", 23);
        set("dex", 22);

        set("max_qi", 3000);
        set("max_jing",1500);
        set("neili", 3700);
        set("max_neili", 3700);
        set("jiali", 30);
        set("combat_exp", 760000);
        set("level", 30);
        set("apprentice_available", 3);

        set_skill("cuff", 600);
        set_skill("strike", 600);
        set_skill("sword", 650);
        set_skill("blade", 650);
        set_skill("force", 650);
        set_skill("parry", 600);
        set_skill("dodge", 600);
        set_skill("literate", 600);
        set_skill("huashan-sword", 650);
        set_skill("yunu-sword", 650);
        set_skill("fanliangyi-dao", 650);
        set_skill("huashan-neigong", 650);
        set_skill("zixia-shengong", 650);
        set_skill("huashan-quan", 650);
        set_skill("huashan-zhang", 650);
        set_skill("poyu-quan", 600);
        set_skill("hunyuan-zhang", 600);
        set_skill("feiyan-huixiang", 600);
        set_skill("jianyi", 600);
        set_skill("martial-cognize", 600);

        map_skill("sword", "yunu-sword");
        map_skill("parry", "yunu-sword");
        map_skill("blade", "fanliangyi-dao");
        map_skill("force", "zixia-shengong");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");
        map_skill("dodge", "feiyan-huixiang");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        set_temp("apply/attack", 220);
        set_temp("apply/dodge", 220);
        set_temp("apply/parry", 600);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 600);

        create_family("華山派", 13, "掌門夫人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ning" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "cuff.lei" :),
                (: perform_action, "cuff.po" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob",4);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一個一個來。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 今天好累喲。");
        }
}

void do_recruit(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "女性" )
        {
                command("say 這位" + RANK_D->query_respect(ob) + "你還是找我師哥去吧.");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say 你行俠仗義的事還做得不夠，我還不能收你！");
                return;
        }

        if (ob->query_skill("huashan-neigong", 1) < 140)
        {
                command("say 我華山派以修氣為主，你連本門內功都還不熟練，我不能收你！");
                return;
        }

        if (ob->query_skill("huashan-sword", 1) < 140)
        {
                command("say 你華山劍法還不夠熟練，下去多練習練習再來找我吧！");
                return;
        }

        command("say 微笑道：好，好，只要你用心學，他日必有成就。");
        command("recruit "+query("id", ob));
}

int recruit_apprentice(object ob)
{
        if (::recruit_apprentice(ob))
                set("class", "swordman", ob);
        addn("apprentice_availavble", -1);
}

void reset()
{
        set("apprentice_available", 3);
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "寧氏一劍" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunu-sword/ning",
                           "name"    : "寧氏一劍",
                           "sk1"     : "yunu-sword",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600,
                           "shen"    : 30000, ]));
                break;

        case "無雙無對" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunu-sword/wushuang",
                           "name"    : "無雙無對",
                           "sk1"     : "yunu-sword",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600,
                           "shen"    : 30000, ]));
                break;

        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}


*/
