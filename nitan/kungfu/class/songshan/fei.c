#include <ansi.h>
#include "songshan.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_COAGENT;

void create()
{
        set_name("費彬", ({ "fei bing", "bing", "fei" }) );
        set("nickname", HIW "大嵩陽手" NOR);
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 45);
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 26);

        set("max_qi", 4500);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);
        set("shen_type", 1);
        set("combat_exp", 940000);

        set_skill("cuff", 200);
        set_skill("strike", 220);
        set_skill("sword", 220);
        set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("songshan-jian", 220);
        set_skill("lingyun-jian", 220);
        set_skill("chuanyue-jian", 220);
        set_skill("jiuqu-jian", 220);
        set_skill("songshan-xinfa", 200);
        set_skill("songyang-zhang", 200);
        set_skill("songshan-zhang", 200);
        set_skill("songshan-quan", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "songshan-xinfa");
        map_skill("sword", "chuanyue-jian");
        map_skill("parry", "chuanyue-jian");
        map_skill("strike", "songyang-zhang");
        map_skill("cuff", "songshan-quan");
        map_skill("dodge", "lingxu-bu");

        prepare_skill("strike", "songyang-zhang");

        create_family("嵩山派", 13, "護法");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hao" :),
                (: perform_action, "strike.ying" :),
                (: perform_action, "cuff.chui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 60);
        set_temp("apply/damage", 60);
        set_temp("apply/unarmed_damage", 60);
        set_temp("apply/armor", 120);

        set("master_ob", 4);
        setup();

        carry_object(WEAPON_DIR+"kuojian")->wield();
        carry_object(__DIR__"obj/yellow-cloth")->wear();
}


void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<30000 )
        {
                command("say 我嵩山劍派乃是堂堂名門正派，對弟子要求嚴格。");
                command("say 你在這俠義與德行方面是否還做得不夠？");
                return;
        }

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你現在經驗尚淺，還是多在江湖上走走吧。");
                return;
        }

        if ((int)ob->query_skill("songshan-jian", 1) < 120)
        {
                command("say 我嵩山劍派乃五嶽劍派之一，最為重視劍法。");
                command("say 你的嵩山劍法還不夠熟練，下去練練再來吧。");
                return;
        }

        if ((int)ob->query_skill("songshan-xinfa", 1) < 100)
        {
                command("say 我嵩山劍派雖善用劍，但內功卻是御劍之本。");
                command("say 你是否還應該在嵩山心法上多下點功夫？");
                return;
         }

        command("haha");
        command("say 孺子可教，孺子可教。今日我就收下你吧。");
        command("say 你以後定要勤練武，多行善，揚我嵩山派派雄風。");
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "無影掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/songyang-zhang/ying",
                           "name"    : "無影掌",
                           "sk1"     : "songyang-zhang",
                           "lv1"     : 80,
                           "force"   : 80,
                           "dodge"   : 80,
                           "gongxian": 300,
                           "shen"    : 32000, ]));
                break;

        case "劍氣沖霄" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lingyun-jian/xiao",
                           "name"    : "劍氣沖霄",
                           "sk1"     : "lingyun-jian",
                           "lv1"     : 100,
                           "force"   : 120,
                           "gongxian": 400,
                           "shen"    : 41000, ]));
                break;

        case "皓月穿空" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/chuanyue-jian/hao",
                           "name"    : "皓月穿空",
                           "sk1"     : "chuanyue-jian",
                           "lv1"     : 120,
                           "force"   : 120,
                           "gongxian": 520,
                           "shen"    : 52000, ]));
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
