#include <ansi.h>
#include "jueqing.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("裘千尺", ({ "qiu qianchi", "qiu", "qianchi" }));
        set("nickname", HIG "鐵掌蓮花" NOR);
        set("long", @LONG
她就是鐵掌幫的幫主鐵掌水上漂裘千仞的妹妹，
只見她頭發散亂，面色蒼老，衣衫破爛。
LONG);

        set("gender", "女性");
        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
       
        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("combat_exp", 3000000);

        set_skill("force", 260);
        set_skill("tiezhang-xinfa", 260);
        set_skill("jueqing-xinfa", 260);
        set_skill("tianlei-shengong", 260);
        set_skill("dodge", 260);
        set_skill("jueqing-shenfa", 260);
        set_skill("dengping-dushui", 260);
        set_skill("strike", 260);
        set_skill("strike", 260);
        set_skill("jueqing-zhang", 260);
        set_skill("guhong-zhang", 260);
        set_skill("parry", 260);
        set_skill("tie-zhang", 260);
        set_skill("chuanxin-zhang", 260);
        set_skill("cuff", 260);
        set_skill("tiexian-quan", 260);
        set_skill("sword", 240);
        set_skill("jueqing-jian", 240);
        set_skill("unarmed", 240);
        set_skill("feilong-zhang", 240);
        set_skill("staff", 240);
        set_skill("literate", 160);
        set_skill("martial-cognize", 220);

        map_skill("force", "tianlei-shengong");
        map_skill("unarmed", "chuanxin-zhang");
        map_skill("strike", "tie-zhang");
        map_skill("cuff", "tiexian-quan");
        map_skill("parry", "tie-zhang");
        map_skill("dodge", "dengping-dushui");
        map_skill("staff", "feilong-zhangfa");

        prepare_skill("strike", "tie-zhang");

        create_family("絕情谷", 4, "谷主夫人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.juesha" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.ying" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        setup();

        carry_object("/d/gaibang/npc/obj/cloth")->wear();
}

void attempt_apprentice(object me)
{
        string purename, name, new_name;

        if (! permit_recruit(me))
                return;

        if( query("family/master_name", me) == "公孫止" )
        {
                command("sneer");
                command("say 我裘千尺可不收公孫止那惡賊的徒弟。");
                return;
        }

        if( query("shen", me)>-60000 )
        {
                command("heng");
                command("say 我裘千尺可不收心慈手軟的人做徒弟。");
                return;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("heng");
                command("say 你這點能力怎能繼承我的衣砵？");
                return;
        }

        if ((int)me->query_skill("force") < 140)
        {
                command("say 要學我的鐵掌絕技，內功非精純不可，你還是先多練練吧。");
                return;
        }

        if ((int)me->query_skill("strike", 1) < 80)
        {
                command("say 要學我的鐵掌絕技，需要精湛的掌法作基礎，我看你在那"
                        "上面下的工夫還不夠啊。");
                return;
        }

        command("say 不錯，不錯！");
        command("say 我就收下你了，希望你苦練鐵掌神功，將之發揚光大。");
        command("recruit "+query("id", me));

        if( query("move_party/絕情谷─鐵掌幫", me) && 
             query("surname", me) == "公孫" )
        {
                name=query("name", me);
                purename=query("purename", me);

                new_name = "裘" + purename;

                set("surname", "裘", me);
                set("name", new_name, me);
                delete("move_party/絕情谷─鐵掌幫", me);

                command("say 公孫止那老家伙不是個東西，你以後還是跟你娘親姓為好。");
                command("say 從今以後你就叫作" + new_name + "吧。");
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

        case "破甲推山" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tiexian-quan/jia",
                           "name"    : "破甲推山",
                           "sk1"     : "tiexian-quan",
                           "lv1"     : 60,
                           "force"   : 80,
                           "gongxian": 100,
                           "shen"    : -60000, ]));
                break;

        case "龍飛勢" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/feilong-zhang/fei",
                           "name"    : "龍飛勢",
                           "sk1"     : "feilong-zhang",
                           "lv1"     : 150,
                           "force"   : 120,
                           "gongxian": 300,
                           "shen"    : -60000, ]));
                break;

        case "穿心錐" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/chuanxin-zhang/zhui",
                           "name"    : "穿心錐",
                           "sk1"     : "chuanxin-zhang",
                           "lv1"     : 80,
                           "force"   : 140,
                           "gongxian": 220,
                           "shen"    : -70000 ]));
                break;

        case "無影掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/ying",
                           "name"    : "無影掌",
                           "sk1"     : "tie-zhang",
                           "msg1"    : "$N點了點頭，在$n耳邊輕聲嘀"
                                       "咕了幾句，忽然又拉開架勢，"
                                       "雙掌急速運轉，掌影虛虛實實"
                                       "，一掌毫無章理的拍出。招式"
                                       "精奇，直看得$n目瞪口呆。",
                           "lv1"     : 100,
                           "force"   : 160,
                           "gongxian": 400,
                           "shen"    : -85000, ]));
                break;

        case "掌心雷" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/lei",
                           "name"    : "掌心雷",
                           "msg1"    : "$N投以$n讚許的一笑，說道：“"
                                       "看好了！”隨即只見$N猛催內力"
                                       "，雙掌登時變得火紅，趁$n驚詫"
                                       "之際雙掌幻為一對掌刀凌空劈斬"
                                       "而出，只聽「喀嚓」一聲，一塊"
                                       "大石應聲而碎！",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 120,
                           "gongxian": 600,
                           "shen"    : -950000, ]));
                break;


        default:
                return 0;
        }
}

void unconcious()
{
        die();
}
