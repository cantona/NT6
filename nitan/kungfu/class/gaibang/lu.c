// This program is a part of NT MudLIB
// lu.c 魯有腳

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include "fight.h"

void create()
{
        set_name("魯有腳", ({ "lu youjiao", "lu", "youjiao" }));
        set("long", @LONG
魯有腳雖然武功算不得頂尖高手，可是在江湖
上卻頗有聲望。因為他在丐幫中有仁有義，行
事光明磊落，深得洪七公的器重。
LONG);
        set("nickname", HIG "掌棒龍頭" NOR);
        set("title", "丐幫九袋長老");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4500);
        set("max_jing", 3500);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 220);
        set("combat_exp", 2500000);
        set("level", 20);
        set("score", 500000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("unarmed", 240);
           set_skill("cuff", 240);
        set_skill("changquan", 240);
        set_skill("hand", 240);
        set_skill("shexing-diaoshou", 240);
        set_skill("strike", 240);
        set_skill("xiaoyaoyou", 240);
        set_skill("zhenjing-baili", 200);
        set_skill("qianlong-wuyong", 200);
        set_skill("hongjian-yulu", 200);
        set_skill("parry", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("fengmo-zhang", 240);
        set_skill("blade", 240);
        set_skill("liuhe-dao", 240);
        set_skill("jueming-tui", 240);
        set_skill("begging", 280);
        set_skill("checking", 280);
        set_skill("literate", 220);
        set_skill("martial-cognize", 240);

        set("no_teach", ([
                "dagou-bang"      : "打狗棒法向來只有繼位幫主能夠學習，要學去找幫主。",
                "zhenjing-baili"  : "這套掌法乃是洪老幫主所賜，我不能輕易傳授。",
                "qianlong-wuyong" : "這套掌法乃是洪老幫主所賜，我不能輕易傳授。",
                "hongjian-yulu"   : "這套掌法乃是洪老幫主所賜，我不能輕易傳授。",
        ]));

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("blade", "liuhe-dao");
        map_skill("strike", "xiaoyaoyou");
        map_skill("unarmed", "jueming-tui");
        map_skill("staff", "dagou-bang");
        map_skill("parry", "dagou-bang");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("strike", "xiaoyaoyou");

        create_family("丐幫", 18, "長老");

        set("coagents", ({
                ([ "startroom" : "/d/city/gbxiaowu",
                   "id"        : "hong qigong" ]),
        }));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.chuo" :),
                (: perform_action, "staff.feng" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "staff.tian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/jiaohuaji");
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<150000 )
        {
                command("say 你的江湖經驗不夠，還是先向各位長老學習吧。");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say 你身為丐幫弟子，竟然不做好事？");
                return;
        }

        if( query("family/beggarlvl", ob)<4 )
        {
                command("say 你在本幫的地位太低，還是先向各位長老學習吧。");
                return;
        }

        if (ob->query_skill("force") < 120)
        {
                command("say 你的內功火候還不夠，還是先向各位長老學習吧。");
                return;
        }
        command("nod");
        command("say 以後你就跟著我吧，可別給我生事。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
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

        case "纏身決" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shexing-diaoshou/chan",
                           "name"    : "纏身決",
                           "sk1"     : "shexing-diaoshou",
                           "lv1"     : 100,
                           "sk2"     : "hand",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 4000, ]));
                break;

        default:
                return 0;
        }
}
