#include <ansi.h>
#include "xuanming.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#define ZHANG "/clone/lonely/lutouzhang"

void create()
{
        set_name("鹿杖客", ({ "luzhang ke", "luzhang", "ke" }));
        set("gender", "男性");
        set("shen_type", -1);
        set("age", 52);
        set("str", 30);
        set("con", 38);
        set("int", 20);
        set("dex", 26);
        set("max_qi", 5400);
        set("max_jing", 2400);
        set("qi", 5400);
        set("jing", 2400);
        set("neili", 6500);
        set("max_neili", 6500);
        set("jiali", 220);
        set("combat_exp", 2200000);

        set_skill("force", 280);
        set_skill("xuanming-shengong", 280);
        set_skill("minggu-xinfa", 280);
        set_skill("dodge", 260);
        set_skill("liuying-bu", 260);
        set_skill("staff", 280);
        set_skill("ningxue-zhang", 280);
        set_skill("lutou-zhang", 280);
        set_skill("strike", 280);
        set_skill("feihua-zhang", 280);
        set_skill("xuanming-zhang", 280);
        set_skill("cuff", 260);
        set_skill("piaofeng-quan", 260);
        set_skill("parry", 260);
        set_skill("claw", 260);
        set_skill("dulong-shenzhua", 260);
        set_skill("literate", 240);
        set_skill("martial-cognize", 220);

        map_skill("staff",  "lutou-zhang");
        map_skill("strike", "xuanming-zhang");
        map_skill("force",  "xuanming-shengong");
        map_skill("dodge",  "liuying-bu");
        map_skill("parry",  "xuanming-zhang");
        map_skill("cuff",  "piaofeng-quan");
        map_skill("claw", "dulong-shenzhua");

        prepare_skill("strike", "xuanming-zhang");

        create_family("玄冥谷", 2, "弟子");

        set("no_teach", ([
                "xuanming-shengong" : "玄冥神功要我師父百損道人親自傳授。",
                "xuanming-zhang"    : "玄冥神掌要我師父親自傳授，你還是去找他老人家吧！",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.ying" :),
                (: perform_action, "strike.zhe" :),
                (: perform_action, "strike.lang" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "張無忌"    :   "哼，臭小子屢次壞我大事！我非殺了他不可！\n",
                "趙敏"      :   "那丫頭詭計多端，忘恩負義，枉我兄弟為她出生入死。\n",
                "百損道人"  :   "他是我恩師，你問這幹什麼？\n",
                "鶴筆翁"    :   "他是我師弟，我們從小跟著師父學藝，親同手足。\n",
        ]));

        set_temp("apply/attack", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 120);

        set("coagents", ({
                ([ "startroom" : "xxxxxxxxxxxx",
                   "id"        : "baisun daoren" ]),
        }));

        setup();

        carry_object("/clone/cloth/baipao")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<-20000 )
        {
                command("say 哼，看見你一副正義凜然的樣子我就是氣。");
                return;
        }

        if (ob->query_skill("minggu-xinfa", 1) < 120)
        {
                command("say 你冥谷心法火候不足，還是跟我師弟多練習練習吧！");
                return ;
        }

        if (ob->query_skill("strike", 1) < 120)
        {
                command("say 你基本掌法修為還不夠，以後如何學習我玄冥谷絕學玄冥神掌？");
                return ;
        }

        command("nod");
        command("say 好，好，今日我就收你為弟子。");
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "繽紛雪舞" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/ningxue-zhang/xue",
                           "name"    : "繽紛雪舞",
                           "sk1"     : "ningxue-zhang",
                           "lv1"     : 50,
                           "gongxian": 220,
                           "shen"    : -20000, ]));
                break;

        case "通天徹地" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lutou-zhang/tong",
                           "name"    : "通天徹地",
                           "sk1"     : "lutou-zhang",
                           "lv1"     :  100,
                           "force"   :  140,
                           "gongxian":  380,
                           "shen"    : -23000, ]));
                break;

        case "只手遮天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuanming-zhang/zhe",
                           "name"    : "只手遮天",
                           "sk1"     : "xuanming-zhang",
                           "lv1"     : 150,
                           "sk2"     : "xuanming-shengong",
                           "lv2"     : 150,
                           "neili"   : 2000,
                           "gongxian": 880,
                           "shen"    : -50000, ]));
                break;


         case "鹿頭杖" :
                return MASTER_D->give_item(me, this_object(),
                               (["item"     :  ZHANG,
                                 "master"   :  1,
                                 "sk1"      :  "lutou-zhang",
                                 "lv1"      :  100,
                                 "shen"     :  -20000 ]));
                  break;

        default:
                return 0;
        }
}

void unconcious()
{
        die();
}
