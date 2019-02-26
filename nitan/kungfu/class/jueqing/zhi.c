#include <ansi.h>
#include "jueqing.h"

#define HEIJIAN "/clone/lonely/heijian"
#define JUCHI   "/clone/lonely/juchidao"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

void create()
{
        object ob1,ob2;
        set_name("公孫止", ({ "gongsun zhi", "gongsun", "zhi" }));
        set("nickname", HIR "陰陽刃" NOR);
        set("gender", "男性");
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("age", 40);
        set("str", 35);
        set("con", 35);
        set("int", 25);
        set("dex", 35);
        set("max_qi", 6000);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 3000000);

        set_skill("force", 240);
        set_skill("jueqing-xinfa", 240);
        set_skill("fenxin-jue", 240);
        set_skill("dodge", 240);
        set_skill("jueqing-shenfa", 240);
        set_skill("strike", 240);
        set_skill("jueqing-zhang", 240);
        set_skill("guhong-zhang", 240);
        set_skill("cuff", 240);
        set_skill("pokong-quan", 240);
        set_skill("medical", 240);
        set_skill("jueqing-yaoli", 240);
        set_skill("sword", 260);
        set_skill("yinyang-ren", 260);
        set_skill("zilei-jian", 260);
        set_skill("guxing-jian", 260);
        set_skill("blade", 260);
        set_skill("tianjue-dao", 260);
        set_skill("luoyun-dao", 260);
        set_skill("poguang-dao", 260);
        set_skill("parry", 240);
        set_skill("literate", 240);
        set_skill("medical", 240);
        set_skill("jueqing-yaoli", 240);
        set_skill("martial-cognize", 220);

        map_skill("strike", "jueqing-zhang");
        map_skill("sword", "yinyang-ren");
        map_skill("blade", "yinyang-ren");
        map_skill("force", "fenxin-jue");
        map_skill("dodge", "jueqing-shenfa");
        map_skill("parry", "yinyang-ren");
        map_skill("parry", "jueqing-yaoli");

        prepare_skill("strike", "jueqing-zhang");

        create_family("絕情谷", 4, "谷主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.huan" :),
                (: perform_action, "sword.heng" :),
                (: perform_action, "strike.hun" :),
                (: perform_action, "strike.wan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();

        if (clonep())
        {
                ob1 = find_object(HEIJIAN);
                if (! ob1) ob1 = load_object(HEIJIAN);
                if (! environment(ob1))
                {
                        ob1->move(this_object());
                        set_temp("handing", ob1);
                } else
                {
                        ob1 = new("/clone/weapon/changjian");
                        ob1->move(this_object());
                        set_temp("handing", ob1);
                }

                ob2 = find_object(JUCHI);
                if (! ob2) ob2 = load_object(JUCHI);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wield();
                }else
                {
                        ob2 = new("/clone/weapon/gangdao");
                        ob2->move(this_object());
                        ob2->wield();
                }
        }
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("family/master_name", ob) == "裘千尺" )
        {
                command("sneer");
                command("say 我公孫止可不收裘千尺那惡婦的徒弟。");
                return;
        }

        if( query("shen", ob)>-30000 )
        {
                command("say 我公孫止最看不慣你們這些正道人士。");
                command("say 你還是請回吧！");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say 你現在經驗尚淺，還是多在江湖上走走吧。");
                return;
        }

        if ((int)ob->query_skill("jueqing-xinfa", 1) < 120)
        {
                command("say 我絕情谷武功講究心神合一，最重視基本心法。");
                command("say 你的絕情心法還不夠熟練，下去練練再來吧。");
                return;
        }

        if ((int)ob->query_skill("dodge") < 180)
        {
                command("say 我絕情谷武功需配合靈動的身法。");
                command("say 你是否還應該在輕功修為上多下點功夫？");
                return;
        }

        command("nod");
        command("say 念你還是個可造之才，今日我就收下你吧。");
        command("recruit "+query("id", ob));
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

        case "落雷式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zilei-jian/luo",
                           "name"    : "落雷式",
                           "sk1"     : "zilei-jian",
                           "lv1"     : 100,
                           "force"   : 120,
                           "gongxian": 400,
                           "shen"    : -60000, ]));
                break;

        case "狂風式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zilei-jian/feng",
                           "name"    : "狂風式",
                           "sk1"     : "zilei-jian",
                           "lv1"     : 100,
                           "dodge"   : 140,
                           "gongxian": 400,
                           "shen"    : -45000, ]));
                break;

        case "破陽刀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poguang-dao/yang",
                           "name"    : "破陽刀",
                           "sk1"     : "poguang-dao",
                           "lv1"     : 100,
                           "force"   : 120,
                           "gongxian": 400,
                           "shen"    : -60000, ]));
                break;

        case "寒冰環" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poguang-dao/bing",
                           "name"    : "寒冰環",
                           "sk1"     : "poguang-dao",
                           "lv1"     : 100,
                           "force"   : 140,
                           "gongxian": 400,
                           "shen"    : -45000, ]));
                break;

        case "魂飛魄散" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jueqing-zhang/hun",
                           "name"    : "魂飛魄散",
                           "sk1"     : "jueqing-zhang",
                           "msg1"    : this_object()->name() + "點了"
                                       "點頭，説道：“好，我給你演示"
                                        "一遍，你看清楚了。”説完" +
                                       this_object()->name() + "運轉"
                                       "真氣，將內力注於掌風之中，雙"
                                       "掌猛然拍向虛空，掌風凌厲無比"
                                       "，氣勢凌人，直可驚天地，泣鬼"
                                       "神。",
                           "lv1"     : 120,
                           "force"   : 160,
                           "gongxian": 500,
                           "shen"    : -92000, ]));
                break;

        case "日月無華" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinyang-ren/hua",
                           "name"    : "日月無華",
                           "sk1"     : "yinyang-ren",
                           "lv1"     : 160,
                           "gongxian": 600,
                           "shen"    : -35000, ]));
                break;

        case "橫空出世" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinyang-ren/heng",
                           "name"    : "橫空出世",
                           "sk1"     : "yinyang-ren",
                           "lv1"     : 180,
                           "dodge"   : 180,
                           "force"   : 180,
                           "gongxian": 700,
                           "shen"    : -100000 ]));
                break;

        case "陰陽環" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinyang-ren/huan",
                           "name"    : "陰陽環",
                           "sk1"     : "yinyang-ren",
                           "lv1"     : 180,
                           "dodge"   : 200,
                           "gongxian": 600,
                           "shen"    : -120000, ]));
                break;

        case "黑劍" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : HEIJIAN,
                           "master"  : 1,
                           "sk1"     : "yinyang-ren",
                           "lv1"     : 150,
                           "shen"    : -46000, ]));
                break;

        case "黃金鋸齒刀" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : JUCHI,
                           "master"  : 1,
                           "sk1"     : "yinyang-ren",
                           "lv1"     : 180,
                           "shen"    : -50000, ]));
                break;
        default:
                return 0;
        }
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        return 0;
}

void unconcious()
{
        die();
}
