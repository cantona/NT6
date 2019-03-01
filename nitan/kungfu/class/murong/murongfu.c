// This program is a part of NT MudLIB
// murongfu.c 慕容復

#include <ansi.h>
#include "murong.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;
inherit F_COAGENT;

string ask_dan1();

void create()
{
        set_name("慕容復", ({ "murong fu", "murong", "fu" }));
        set("long", @LONG
他是姑蘇慕容的傳人，是慕容博之子，所謂南慕容、北喬峰。
此人正是和喬峰齊名的慕容家高手。他容貌俊雅，風度過人，
的確非尋常人可比。
LONG );
        set("titile", "姑蘇慕容");
        set("gender", "男性");
        set("age", 25);
        set("shen_type",-1);
        set("attitude", "peaceful");

        set("str", 27);
        set("int", 29);
        set("con", 31);
        set("dex", 28);
        set("per", 28);

        set("qi", 4100);
        set("max_qi", 4100);
        set("jing", 2100);
        set("max_jing", 2100);
        set("neili", 4900);
        set("max_neili", 4900);
        set("jiali", 80);
        set("level", 30);
        set("combat_exp", 1750000);

        set_skill("force", 180);
        set_skill("literate", 140);
        set_skill("cuff", 180);
        set_skill("sword", 180);
        set_skill("blade", 180);
        set_skill("dodge", 180);
        set_skill("strike", 180);
        set_skill("parry", 200);

        set_skill("shenyuan-gong", 180);
        set_skill("zihui-xinfa", 200);
        set_skill("xingyi-zhang", 300);
        set_skill("douzhuan-xingyi", 200);
        set_skill("beidou-xianzong", 180);
        set_skill("qixing-quan", 180);
        set_skill("murong-jianfa", 180);
        set_skill("murong-daofa", 180);
        set_skill("martial-cognize", 140);

        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("strike", "xingyi-zhang");
        map_skill("blade", "murong-daofa");
        map_skill("sword", "murong-jianfa");

        prepare_skill("cuff", "qixing-quan");

        set("inquiry",
        ([
                "name"       : "我就是以彼之道，還施彼身的姑蘇慕容復。\n",
                "here"       : "這裡是大名鼎鼎的燕子塢，難道你沒有聽說過？\n",
                "rumors"     : "家父突染惡疾，我連他老人家最後一面都沒見到，此事頂有蹊蹺！\n",
                "姑媽"       : "我的姑媽住在曼佗羅山莊，那裡有聞名天下的娘繯玉洞。\n",
                "王語嫣"    : "語嫣是我表妹，我一直把她當小妹妹看待。\n",
                "南慕容"    : "“南慕容北喬峰”，那是江湖上的朋友抬愛了！\n",
                "慕容復"    : "那是賤名。請教尊駕是？\n",
                "鄧百川"    : "你問鄧大哥啊？他在他青風莊上呢。\n",
                "公冶乾"    : "公冶二哥把信鴿傳書一編碼，就沒幾個人讀得懂了。\n",
                "包不同"    : "包三哥最愛抬槓了，你見了他還是閉嘴的好。\n",
                "風波惡"    : "風四哥最是豪爽了，他從不與人計較什麼。\n",
                // "還施水閣"   : (: ask_ge :),
                // "王語嫣"     : (: ask_wang :),
                // "歸元丹"     : (: ask_dan :),
                "玉露清新散" : (: ask_dan1 :),
                // "武學修養"   : (: ask_learn :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "parry.yi" :),
                (: perform_action, "blade.feng" :),
                (: perform_action, "cuff.zhai" :),
        }));

        create_family("慕容世家", 16, "傳人");

        set("coagents", ({
                ([ "startroom" : "/d/yanziwu/canheju",
                   "id"        : "murong bo" ]),
        }));

        set("master_ob",3);
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 200);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>0 )
        {
                command("say 我慕容世家向來不和你們這些所謂正道人士交往。");
                command("say 你還是請回吧！");
                return;
        }


        command("nod");
        command("say 今日我就暫且收下你，日後定須刻苦練武，光復大燕。");
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

        case "摘星式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qixing-quan/zhai",
                           "name"    : "摘星式",
                           "sk1"     : "qixing-quan",
                           "lv1"     : 40,
                           "gongxian": 140,
                           "shen"    : -4000, ]));
                break;

        case "劍轉七星" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-jianfa/xing",
                           "name"    : "劍轉七星",
                           "sk1"     : "murong-jianfa",
                           "lv1"     :  40,
                           "gongxian":  200,
                           "shen"    : -6000, ]));
                break;

        case "白虹貫日" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-jianfa/hong",
                           "name"    : "白虹貫日",
                           "sk1"     : "murong-jianfa",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;

        case "日月同輝" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xingyi-zhang/riyue",
                           "name"    : "日月同輝",
                           "sk1"     : "xingyi-zhang",
                           "lv1"     :  40,
                           "gongxian":  200,
                           "shen"    : -6000, ]));
                break;

        case "星光點點" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xingyi-zhang/xing",
                           "name"    : "星光點點",
                           "sk1"     : "xingyi-zhang",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;

        case "刀影掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-daofa/ying",
                           "name"    : "刀影掌",
                           "sk1"     : "murong-daofa",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
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

string ask_dan1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "姑蘇慕容" )
                return RANK_D->query_respect(this_player()) +
                "與本派素無來往，不知此話從何談起？";
        if (query("san_count") < 1)
                return "你來晚了，本派的玉露清新散不在此處。";
        addn("san_count", -1);
        ob = new("/clone/medicine/nostrum/yulusan");
        ob->move(this_player());
        return "好吧，這玉露清新散你拿去吧。";
}
