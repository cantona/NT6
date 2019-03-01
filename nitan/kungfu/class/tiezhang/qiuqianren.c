#include <ansi.h>
#include "tiezhang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;
int ask_qiubai();
void create()
{
        set_name("裘千仞", ({ "qiu qianren", "qiu", "qianren", "ren"}));
        set("nickname", WHT "鐵掌水上漂" NOR);
        set("long", "他就是威震川湘的鐵掌幫的幫主鐵掌水上漂裘千仞。\n"
                    "他頭須皆白，身穿黃葛短衫，右手揮著一把大蒲扇。\n" );

        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);
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
        set("combat_exp", 4000000);
        set("score", 40000);

        set_skill("force", 600);
        set_skill("tiezhang-xinfa", 600);
        set_skill("tianlei-shengong", 600);
        set_skill("dodge", 600);
        set_skill("dengping-dushui", 600);
        set_skill("strike", 600);
        set_skill("parry", 600);
        set_skill("tie-zhang", 600);
        set_skill("chuanxin-zhang", 600);
        set_skill("cuff", 600);
        set_skill("tiexian-quan", 600);
        set_skill("unarmed", 600);
        set_skill("feilong-zhang", 600);
        set_skill("staff", 600);
        set_skill("blade", 600);
        set_skill("tianlei-dao", 600);
        set_skill("club", 600);
        set_skill("zhongping-qiang", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "tianlei-shengong");
        map_skill("unarmed", "chuanxin-zhang");
        map_skill("strike", "tie-zhang");
        map_skill("cuff", "tiexian-quan");
        map_skill("parry", "tie-zhang");
        map_skill("dodge", "dengping-dushui");
        map_skill("staff", "feilong-zhang");

        prepare_skill("strike", "tie-zhang");

        create_family("鐵掌幫", 14, "幫主");

        set("inquiry", ([
                "絕招"    : "你要問什麼絕招？",
                "絕技"    : "你要問什麼絕技？",
                "鐵掌掌譜": "這本秘籍不在我手裡，想必已經失落很久了。",
                "上官劍南" : (: ask_qiubai :),
                "裘千丈"  : "哼，大哥老是打著我的名號到處招搖撞騙，總有一天我要……",
                "裘千尺"  : "三妹下嫁到絕情谷去了，你問這個有什麼事嗎？",
                "絕情谷"  : "絕情谷公孫止那家伙不是個東西，你問這個幹嘛？",
                "華山論劍": "哼，去年的華山論劍要不是因為我在閉觀，哪裡輪得上王重陽那牛鼻子。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.juesha" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.yin" :),
                (: perform_action, "cuff.kai" :),
                (: perform_action, "unarmed.zhui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        setup();

        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

void attempt_apprentice(object me)
{
        string purename, name, new_name;

        if (! permit_recruit(me))
                return;

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "絕情谷" && 
             query("family/master_name", me) == "裘千尺" )
        {
                command("nod");
                command("say 原來是三妹的後裔，這樣也好，我們本來就是一家人。且讓"
                "我先看看你的能力。\n");
                set("move_party/絕情谷─鐵掌幫", 1, me);
        }

        if( query("shen", me)>-60000 )
        {
                command("heng");
                command("say 我裘千仞可不收心慈手軟的人做徒弟。");
                return;
        }

        if( query("combat_exp", me)<800000 )
        {
                command("heng");
                command("say 你這點能力怎能繼承我的衣砵？");
                return;
        }

        if ((int)me->query_skill("force") < 260)
        {
                command("say 要學我的鐵掌絕技，內功非精純不可，你還是先多練練吧。");
                return;
        }

        if ((int)me->query_skill("strike", 1) < 180)
        {
                command("say 要學我的鐵掌絕技，需要精湛的掌法作基礎，我看你在那上"
                        "面下的工夫還不夠啊。");
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

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/tie-zhang/juesha", me) )
                return "這招我已經教過你了，還是自己下去多多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本幫素無瓜葛，何出此言？";

        if (me->query_skill("tie-zhang", 1) < 1)
                return "你連鐵掌掌法都沒學，何談此言？";

        if( query("shen", me)>-100000 )
                return "心慈手軟的人永遠幹不了大事，這招你不學也罷！";

        if (me->query_skill("tie-zhang", 1) < 200)
                return "你的鐵掌掌法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("tianlei-shengong", 1) < 180)
                return "這一招需求強大的天雷真氣做基礎，看來你所下的功夫還不夠啊！";

        if( query("gongxian", me)<660 )
                return "你的門派貢獻不夠，這招我不能傳你！";

        message_vision(HIY "$n" HIY "默默注視了$N" HIY "良"
                       "久，說道：“既然如此，今日我便傳你"
                       "這招！我只演示一遍，你可要看仔細了"
                       "！”\n\n" NOR + HIR "$n" HIR "說完"
                       "一聲怒喝，體內所積存數十載的天雷真"
                       "氣澎湃而發，衣衫鼓動，雙臂陡然暴\n"
                       "長數尺。只聽四周破空之聲驟然響之，"
                       "$n" HIR "雙掌幻出漫天掌影，舖天蓋"
                       "地向四面八方\n雲湧而出，當真氣勢磅"
                       "礡，無與倫比！\n" NOR,
                       me, this_object());
        command("nod");
        command("say 這招「九穹絕剎掌」是我鐵掌幫最為精深的招式，你明白了多少？");
        command("say 這其中的奧妙還需要你自己下來勤加練習方能吸收，自己下去多多練習吧。");
        tell_object(me, HIC "你學會了「九穹絕剎掌」這一招。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 960000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 960000);
        if (me->can_improve_skill("tie-zhang"))
                me->improve_skill("tie-zhang", 960000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 960000);
        if (me->can_improve_skill("tianlei-shengong"))
                me->improve_skill("tianlei-shengong", 960000);
        set("can_perform/tie-zhang/juesha", 1, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/feilong-zhangfa/fei", me) )
                return "這招我已經教過你了，還是自己下去多多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本幫素無瓜葛，何出此言？";

        if (me->query_skill("feilong-zhangfa", 1) < 1)
                return "你連飛龍杖法都沒學，何談此言？";

        if( query("shen", me)>-10000 )
                return "嘿嘿嘿，你這樣心慈手軟能幹成什麼事？這招你不學也罷！";

        if (me->query_skill("feilong-zhangfa", 1) < 150)
                return "你的飛龍杖法還練得不到家，自己下去練練再來吧！";

        if( query("gongxian", me)<160 )
                return "你的門派貢獻不夠，這招我不能傳你！";

        message_vision(HIY "$n" HIY "微微點了點頭，對$N" HIY
                       "說道：“看好了！”隨即順手抄起一根鋼"
                       "杖，注力入腕，「颼」的\n一聲擲出，剎"
                       "那只見一道銀光飛逝而過，同時只聽「撲"
                       "哧」一聲碎響，鋼杖已沒入$N" HIY "身"
                       "後的柱\n子數尺之深。\n" NOR, me, this_object());
        command("nod");
        command("say 這招「龍飛勢」並不復雜，下來後自己多加練習就行了！");
        tell_object(me, HIC "你學會了「龍飛勢」這一招。\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 960000);
        if (me->can_improve_skill("feilong-zhangfa"))
                me->improve_skill("feilong-zhangfa", 960000);
        set("can_perform/feilong-zhangfa/fei", 1, me);
        return 1;
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

        case "掌心雷" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/lei",
                           "name"    : "掌心雷",
                           "msg1"    : HIY "$N" HIY "投以讚許的"
                                       "一笑，說道：“看好了！”"
                                       "隨即只見$N" HIY "猛催內"
                                       "力，雙掌登時變得火紅，你"
                                       "正驚詫之際$N" HIY "雙掌幻"
                                       "為一對掌刀凌空劈\n斬而出"
                                       "，只聽「喀嚓」一聲，大廳"
                                       "內一張青石桌應聲而碎！",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 160,
                           "force"   : 240,
                           "neili"   : 2200,
                           "gongxian": 600,
                           "shen"    : -65000, ]));
                break;

        case "九穹絕剎掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/juesha",
                           "name"    : "九穹絕剎掌",
                           "msg1"    : HIY "$N" HIY "默默注視了你"
                                       "良久，說道：“既然如此，今"
                                       "日我便傳你這招！我只演示一"
                                       "遍，你可要看仔細了！”說完"
                                       "一聲怒喝，體內所積存數十載"
                                       "的天雷真氣澎湃而發，衣衫鼓"
                                       "動，雙臂陡然暴長數尺。只聽"
                                       "四周破空之聲驟然響之，$N" HIY
                                       "雙掌幻出漫天掌影，舖天蓋地向"
                                       "四面八方雲湧而出，當真氣勢磅"
                                       "礡，無與倫比！",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 200,
                           "force"   : 300,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : -85000, ]));
                break;

        case "龍影掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/long",
                           "name"    : "龍影掌",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 100,
                           "force"   : 80,
                           "neili"   : 1300,
                           "gongxian": 300,
                           "shen"    : -60000, ]));
                break;

        case "五指刀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/dao",
                           "name"    : "五指刀",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 180,
                           "force"   : 280,
                           "neili"   : 2500,
                           "gongxian": 700,
                           "shen"    : -90000, ]));
                break;

        case "陰陽磨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/yin",
                           "name"    : "陰陽磨",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 220,
                           "force"   : 300,
                           "neili"   : 3500,
                           "gongxian": 900,
                           "shen"    : -95000, ]));
                break;

        case "春雷炸空" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianlei-dao/zha",
                           "name"    : "春雷炸空",
                           "sk1"     : "tianlei-dao",
                           "lv1"     : 150,
                           "force"   : 140,
                           "neili"   : 1500,
                           "gongxian": 600,
                           "shen"    : -75000, ]));
                break;

        case "五雷連閃" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianlei-dao/shan",
                           "name"    : "五雷連閃",
                           "sk1"     : "tianlei-dao",
                           "lv1"     : 150,
                           "force"   : 150,
                           "neili"   : 1500,
                           "gongxian": 600,
                           "shen"    : -75000, ]));
                break;
/*
        case "鎮岳尚方" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : ZHENYUE,
                           "master"  : 1,
                           "sk1"     : "henshan-jian",
                           "lv1"     : 120,
                           "shen"    : 50000, ]));
                break;
*/
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
int ask_qiubai()
{
        say("他是我師父。我在十三歲那年曾救過他，之後他感恩圖報，將全\n"
            "身武功傾囊相受。可惜十年前，他在湖北遭人圍攻而死！唉！\n");
        return 1;
}

void unconcious()
{
        die();
}