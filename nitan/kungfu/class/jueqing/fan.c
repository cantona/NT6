#include <ansi.h>
#include "jueqing.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("樊一翁", ({ "fan yiweng", "fan", "yiweng" }));
        set("gender", "男性");
        set("shen_type", 0);
        set("age", 60);
        set("str", 38);
        set("con", 28);
        set("int", 20);
        set("dex", 26);
        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 200);
        set("combat_exp", 2200000);

        set_skill("force", 180);
        set_skill("jueqing-xinfa", 180);   
        set_skill("dodge", 180);
        set_skill("jueqing-shenfa", 180);
        set_skill("staff", 180);
        set_skill("poshui-zhang", 180);
        set_skill("strike", 180);
        set_skill("cuff", 160);
        set_skill("guhong-zhang", 180);
        set_skill("pokong-quan", 160);
        set_skill("jueqing-zhang", 160);
        set_skill("sword", 160);
        set_skill("jueqing-jian", 160);
        set_skill("guxing-jian", 160);
        set_skill("blade", 160);
        set_skill("tianjue-dao", 160);
        set_skill("luoyun-dao", 160);
        set_skill("parry", 180);
        set_skill("literate", 160);
        set_skill("martial-cognize", 160);
        
        map_skill("staff",  "poshui-zhang");
        map_skill("sword",  "guxing-jian");
        map_skill("strike", "guhong-zhang");
        map_skill("force",  "jueqing-xinfa");
        map_skill("blade",  "luoyun-dao");
        map_skill("dodge",  "jueqing-shenfa");
        map_skill("parry",  "poshui-zhang");

        prepare_skill("strike", "jueqing-zhang");
             
        create_family("絕情谷", 5, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.tai" :),
                (: perform_action, "strike.qian" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/attack", 60);
        set_temp("apply/damage", 60);
        set_temp("apply/unarmed_damage", 60);
        set_temp("apply/armor", 60);

        set("coagents", ({
                ([ "startroom" : "/d/jueqing/zizhuxuan",
                   "id"        : "gongsun zhi" ]),
        }));

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>0 )
        {
                command("say 我絕情谷向來不和你們這些正道人士交往。");
                command("say 你還是請回吧！");
                return;
        }


        command("nod");
        command("say 今日我就暫且收下你，日後定須刻苦練武。");
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "流水無情" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jueqing-jian/liu",
                           "name"    : "流水無情",
                           "sk1"     : "jueqing-jian",
                           "lv1"     : 60,
                           "force"   : 60,
                           "gongxian": 80,
                           "shen"    : -4000, ]));
                break;

        case "天絕鎖" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianjue-dao/suo",
                           "name"    : "天絕鎖",
                           "sk1"     : "tianjue-dao",
                           "lv1"     :  40,
                           "gongxian":  100,
                           "shen"    : -4000, ]));
                break;

        case "破碎虛空" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pokong-quan/kong",
                           "name"    : "破碎虛空",
                           "sk1"     : "pokong-quan",
                           "lv1"     : 50,
                           "force"   : 70,
                           "gongxian": 100,
                           "shen"    : -4000, ]));
                break;

        case "萬念懼灰" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jueqing-zhang/wan",
                           "name"    : "萬念懼灰",
                           "msg1"    : this_object()->name() + "點了"
                                       "點頭，忽然一聲長嘯，聲音震耳"
                                       "欲聾，悲痛欲絕，頓感萬念俱灰"
                                       "，猛然間雙掌瘋狂般的拍向長空"
                                       "，看似雜亂無章，但內中卻隱藏"
                                       "無限殺機。你看得心中不由地讚"
                                       "嘆。",
                           "sk1"     : "jueqing-zhang",
                           "lv1"     : 100,
                           "dodge"   : 80,
                           "gongxian": 120,
                           "shen"    : -8000, ]));
                break;

        case "九星連珠" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/guxing-jian/lian",
                           "name"    : "九星連珠",
                           "sk1"     : "guxing-jian",
                           "lv1"     :  80,
                           "force"   :  60,
                           "gongxian": 180,
                           "shen"    : -12000, ]));
                break;

        case "天刀落雲式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/luoyun-dao/tian",
                           "name"    : "天刀落雲式",
                           "sk1"     : "luoyun-dao",
                           "lv1"     :  80,
                           "force"   :  60,
                           "gongxian": 180,
                           "shen"    : -12000, ]));
                break;

        case "千山孤鴻影" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/guhong-zhang/qian",
                           "name"    : "千山孤鴻影",
                           "msg1"    : this_object()->name() + "略微點"
                                       "了點頭，說道：“你可看清楚了。"
                                       "”說罷雙掌陡然連續拍出，剛中帶"
                                       "柔，雙掌帶風，已你籠罩在掌風之"
                                       "中，你呆立當場卻也不敢妄動。",
                           "sk1"     : "guhong-zhang",
                           "lv1"     : 80,
                           "force"   : 100,
                           "gongxian": 220,
                           "shen"    : -12000 ]));
                break;

        case "泰山壓頂" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poshui-zhang/tai",
                           "name"    : "泰山壓頂",
                           "sk1"     : "poshui-zhang",
                           "lv1"     : 120,
                           "force"   : 160,
                           "gongxian": 300,
                           "shen"    : -18000, ]));
                break;

        default:
                return 0;
        }
}

void unconcious()
{
        die();
}
