// This program is a part of NT MudLIB

#include <ansi.h>
#include "xuanming.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

void create()
{
        set_name("百損道人", ({ "baisun daoren", "baisun", "daoren" }));
        set("gender", "男性");
        set("long", @LONG
他就是玄冥谷開山祖師百損道人，只見他百發飄忽，雙眼神光四射，令人敬畏。
LONG);
        set("shen_type", -1);
        set("age", 72);
        set("str", 40);
        set("con", 38);
        set("int", 40);
        set("dex", 46);
        set("max_qi", 7650);
        set("max_jing", 3650);
        set("qi", 7650);
        set("jing", 3650);
        set("neili", 8500);
        set("max_neili", 8500);
        set("jiali", 250);
        set("level", 40);
        set("combat_exp", 6500000);

        set_skill("force", 650);
        set_skill("xuanming-shengong", 650);
        set_skill("dodge", 650);
        set_skill("lingxu-bu", 650);
        set_skill("strike", 650);
        set_skill("xuanming-zhang", 650);
        set_skill("parry", 650);
        set_skill("literate", 650);
        set_skill("martial-cognize", 650);

        map_skill("strike", "xuanming-zhang");
        map_skill("force",  "xuanming-shengong");
        map_skill("dodge",  "lingxu-bu");
        map_skill("parry",  "xuanming-zhang");

        prepare_skill("strike", "xuanming-zhang");

        create_family("玄冥谷", 1, "開山祖師");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.ying" :),
                (: perform_action, "strike.lang" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "鹿杖客"    :   "他是我愛徒。\n",
                "鶴筆翁"    :   "他是我師弟。\n",
        ]));

        set_temp("apply/attack", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 120);

        set("master_ob", 5);
        setup();

        carry_object("/clone/cloth/baipao")->wear();
}

void attempt_apprentice(object ob)
{
        tell_object(ob, "玄冥谷暫不開放。\n");
        return;

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<-35000 )
        {
                command("say 哼，我百損道人從不和正道中人交往。");
                return;
        }

        if (ob->query_skill("minggu-xinfa", 1) < 160)
        {
                command("say 你冥谷心法火候不足，還是跟我徒兒多練習練習吧！");
                return ;
        }

        if (ob->query_skill("strike", 1) < 160)
        {
                command("say 你基本掌法修為還不夠，以後如何學習我玄冥谷絕學玄冥神掌？");
                return ;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("say 你江湖經驗還不足，還是去多闖盪一下吧！");
                return;
        }

        command("nod");
        command("say 好，好，老夫今日就收下你。");
        command("haha");
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "如影相隨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuanming-zhang/ying",
                           "name"    : "如影相隨",
                           "sk1"     : "xuanming-zhang",
                           "lv1"     : 180,
                           "dodge"   : 150,
                           "free"    : 1,
                           // "gongxian": 650,
                           "shen"    : -38000, ]));
                break;

        case "只手遮天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuanming-zhang/zhe",
                           "name"    : "只手遮天",
                           "sk1"     : "xuanming-zhang",
                           "lv1"     :  130,
                           "force"   :  180,
                           "free"    :  1,
                           // "gongxian":  580,
                           "shen"    : -43000, ]));
                break;

        case "驚濤駭浪" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuanming-zhang/lang",
                           "name"    : "驚濤駭浪",
                           "sk1"     : "xuanming-zhang",
                           "lv1"     : 180,
                           "sk2"     : "xuanming-shengong",
                           "lv2"     : 180,
                           "neili"   : 3000,
                           "free"    : 1,
                           // "gongxian": 1200,
                           "shen"    : -68000, ]));
                break;

        default:
                return 0;
        }
}

void unconcious()
{
        die();
}

int recognize_apprentice(object ob, string skill)
{
        if (ob->query_skill(skill, 1) >= 600)
        {
                command("say 夠了！我就教你到這裡吧，武功還是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "xuanming-zhang")
                return 1;

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "strike")
                return 1;

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "xuanming-shengong")
                return 1;

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "force")
                return 1;

        if (skill == "xuanming-zhang")
        {
                message_vision("$N看了看$n，點點頭道：玄冥神掌也沒有什麼難學的。\n",
                               this_object(), ob);
                set_temp("can_learn/baisun/xuanming-zhang", 1, ob);
                return 1;
        }

        command("say 我只懂得一點玄冥神掌，你可不要為難我。");
        return -1;
}
