#include <ansi.h>
#include "henshan.h"

inherit NPC;
inherit F_MASTER;
   inherit F_QUESTER; 

void create()
{
        set_name("魯連榮", ({ "lu lianrong", "lu", "lianrong" }));
        set("gender", "男性" );
        set("nickname", HIY "金眼雕" NOR);
        set("class", "swordman");
        set("attitude", "peaceful");

        set("age", 45);
        set("str", 28);
        set("con", 26);
        set("int", 29);
        set("dex", 28);
        set("max_qi", 2800);
        set("max_jing", 1800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 800000);

        set_skill("force", 140);
        set_skill("henshan-xinfa", 140);
        set_skill("zhenyue-jue", 100);
        set_skill("dodge", 140);
        set_skill("henshan-shenfa", 140);
        set_skill("cuff", 140);
        set_skill("henshan-quan", 140);
        set_skill("sword", 160);
        set_skill("henshan-jian", 160);
        set_skill("tianzhu-jian", 160);
        set_skill("zigai-jian", 140);
        set_skill("strike", 140);
        set_skill("biluo-zhang", 140);
        set_skill("parry", 140);
        set_skill("literate", 140);
        set_skill("martial-cognize", 120);

        map_skill("strike", "biluo-zhang");
        map_skill("cuff", "henshan-quan");
        map_skill("sword", "tianzhu-jian");
        map_skill("force", "henshan-xinfa");
        map_skill("dodge", "henshan-shenfa");
        map_skill("parry", "henshan-jian");

        prepare_skill("cuff", "henshan-quan");
        prepare_skill("strike", "biluo-zhang");

        set("no_teach/zhenyue-jue", "這門內功我也是剛練不久，生疏得緊。");

        create_family("衡山派", 14, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.huan" :),
                (: perform_action, "cuff.riyue" :),
                (: perform_action, "strike.lian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob",3);
        setup();
        carry_object(WEAPON_DIR+"sword/xijian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<5000 )
        {
                command("say 我衡山劍派乃是堂堂名門正派，對弟子要求嚴格。");
                command("say 你在這俠義與德行方面是否還做得不夠？");
                return;
        }

        if( query("combat_exp", ob)<50000 )
        {
                command("say 你現在經驗尚淺，還是多在江湖上走走吧。");
                return;
        }

        if ((int)ob->query_skill("henshan-jian", 1) < 50)
        {
                command("say 我衡山乃五嶽劍派之一，最為重視劍法。");
                command("say 你的衡山劍法還不夠熟練，下去練練再來吧。");
                return;
        }

        if ((int)ob->query_skill("force") < 100)
        {
                command("say 我衡山劍派雖善用劍，但內功卻是御劍之本。");
                command("say 你是否還應該在內功心法上多下點功夫？");
                return;
        }

        command("say 好吧，我就收下你。以後一定要更加努力。");
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "幻劍式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/henshan-jian/huan",
                           "name"    : "幻劍式",
                           "sk1"     : "henshan-jian",
                           "msg1"    : "$N點了點頭，喝道：“看清楚了"
                                       "。”話音剛落，便見$N突將體內"
                                       "真氣運於劍身，身法陡然加快，"
                                       "手中長劍劍隨人動如夢如幻，竟"
                                       "似無數利刃一齊襲出一般，招式"
                                       "甚為巧妙。",
                           "lv1"     : 60,
                           "force"   : 80,
                           "gongxian": 50,
                           "shen"    : 2000, ]));
                break;

        case "煙雲鎖身" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianzhu-jian/suo",
                           "name"    : "煙雲鎖身",
                           "sk1"     : "tianzhu-jian",
                           "lv1"     : 120,
                           "force"   : 150,
                           "dodge"   : 150,
                           "gongxian": 300,
                           "shen"    : 20000, ]));
                break;
        default:
                return 0;
        }
}
