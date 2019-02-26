// This program is a part of NT MudLIB
// da-mo.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "shaolin.h"

mixed ask_qingxin();
mixed ask_luan();
mixed ask_shang();
mixed ask_zhe();

void create()
{
        set_name("達摩老祖", ({
                "da mo",
                "da",
                "mo",
        }));
        set("long",
                "他是一位捲髮絡腮須的天竺老僧，身穿一襲邋遢金絲繡紅袈裟。\n"
                "但卻滿面紅光，目藴慈笑，眼現智珠，一派得道高僧氣勢。\n"
                "他就是少林派開山鼻祖、當今武林的隱世高僧達摩祖師。\n"
        );

        set("title", HIR"少林開山祖師"NOR);
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 300);
        set("shen_type", 1);

        set("str", 40);
        set("int", 50);
        set("con", 45);
        set("dex", 40);

        set("max_qi", 8000);
        set("max_jing", 4000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 50);
        set("level", 60);
        set("combat_exp", 10000000);

        set_skill("buddhism", 600);
        set_skill("literate", 600);
        set_skill("sanscrit", 600);
        set_skill("martial-cognize", 500);

        set_skill("blade", 600);
        set_skill("claw", 600);
        set_skill("club", 600);
        set_skill("cuff", 600);
        set_skill("dodge", 600);
        set_skill("finger", 600);
        set_skill("force", 600);
        set_skill("hand", 600);
        set_skill("parry", 600);
        set_skill("staff", 600);
        set_skill("strike", 600);
        set_skill("sword", 600);
        set_skill("whip", 600);
        set_skill("unarmed", 600);
        set_skill("medical", 600);
        set_skill("shaolin-yishu", 600);

        set_skill("banruo-zhang", 600);
        set_skill("shenzhang-bada", 600);
        set_skill("xumishan-zhang", 600);
        set_skill("cibei-dao", 600);
        set_skill("damo-jian", 600);
        set_skill("lunhui-jian", 600);
        set_skill("fengyun-shou", 600);
        set_skill("fumo-jian", 600);
        set_skill("hunyuan-yiqi", 600);
        set_skill("shaolin-xinfa", 600);
        set_skill("jingang-quan", 600);
        set_skill("longzhua-gong", 600);
        set_skill("luohan-quan", 600);
        set_skill("nianhua-zhi", 600);
        set_skill("xiuluo-zhi", 600);
        set_skill("yipai-liangsan", 600);
        set_skill("duoluoye-zhi", 600);
        set_skill("jingang-zhi", 600);
        set_skill("wuxiang-zhi", 600);
        set_skill("pudu-zhang", 600);
        set_skill("qianye-shou", 600);
        set_skill("sanhua-zhang", 600);
        set_skill("riyue-bian", 600);
        set_skill("shaolin-shenfa", 600);
        set_skill("weituo-gun", 600);
        set_skill("wuchang-zhang", 600);
        set_skill("xiuluo-dao", 600);
        set_skill("ranmu-daofa", 600);
        set_skill("yingzhua-gong", 600);
        set_skill("yijinjing", 600);
        set_skill("yizhi-chan", 600);
        set_skill("zui-gun", 600);
        set_skill("zui-quan", 600);
        set_skill("lunhui", 600);

        map_skill("blade", "cibei-dao");
        map_skill("claw", "longzhua-gong");
        map_skill("club", "wuchang-zhang");
        map_skill("cuff", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("force", "yijinjing");
        map_skill("hand", "fengyun-shou");
        map_skill("parry", "nianhua-zhi");
        map_skill("staff", "weituo-gun");
        map_skill("strike", "sanhua-zhang");
        map_skill("sword", "fumo-jian");
        map_skill("whip", "riyue-bian");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        set("inquiry", ([
                "絕招"   : "你想學什麼絕招？",
                "絕技"   : "你想學什麼絕技？",
                "達摩清心劍": (: ask_qingxin :),
                "清心劍"    : (: ask_qingxin :),
                "達摩亂氣劍": (: ask_luan :),
                "亂氣劍"    : (: ask_luan :),
                "達摩傷神劍": (: ask_shang :),
                "傷神劍"    : (: ask_shang :),
                "達摩折元劍": (: ask_zhe :),
                "折元劍"    : (: ask_zhe :),
        ]));

        create_family("少林派", 1, "開山祖師");

        set_temp("apply/attack", 300);
        set_temp("apply/defense", 300);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);

        set("master_ob",5);
        setup();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        object me;
        mapping ob_fam, my_fam;
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        me = this_object();
        my_fam=query("family", me);

        name=query("name", ob);

        if( !(ob_fam=query("family", ob)) || 
            ob_fam["family_name"] != "少林派")
        {
                command("say " + RANK_D->query_respect(ob) +
                        "與本派素無來往，不知此話從何談起？");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say " + RANK_D->query_respect(ob) +
                        "是俗家弟子，不能在寺內學藝。");
                return;
        }

        if ((int)ob_fam["generation"] != 36)
        {
                command("say " + RANK_D->query_respect(ob) +
                        "，貧僧哪裏敢當 !");
                return;
        }

        if ((int)ob->query_int() < 35)
        {
                command("say " + RANK_D->query_respect(ob) + "悟性仍有不足，"
                        "需要進一步鍛鍊才能領悟更高深的佛法。");
        }

        if( query("WPK", ob)>3 )
        {
                command("sigh");
                command("say " + RANK_D->query_respect(ob) + "殺戮心太重，"
                        "不適合繼續學習武功。");
                return;
        }

        if ((int)ob->query_skill("buddhism", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "禪宗心法"
                        "領悟得不夠，不妨先多加鑽研。");
                return;
        }

        if ((int)ob->query_skill("dodge", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "基本輕功"
                        "火候尚有欠缺，不妨先苦心修煉。");
                return;
        }

        if ((int)ob->query_skill("force", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "基本內功"
                        "火候尚有欠缺，不妨先苦心修煉。");
                return;
        }

        if ((int)ob->query_skill("parry", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "基本招架"
                        "火候尚有欠缺，不妨先苦心修煉。");
                return;
        }

        if( query("combat_exp", ob)<1000000 )
        {
                command("say " + RANK_D->query_respect(ob) + "實戰經驗"
                        "還頗有欠缺，不如先苦心修煉。");
                return;
        }

        command("char 老衲又得一可塑之才，真是大暢老懷 !");
        name=query("name", ob);
        new_name = "渡" + name[2..3];
        NAME_D->remove_name(query("name", ob),query("id", ob));
        set("name", new_name, ob);
        NAME_D->map_name(query("name", ob),query("id", ob));

        command("say 從今以後你的法名叫做" + new_name + "。");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_luan()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/luan", me) )
                return "自己好好多練習吧，牢記慈悲為懷，勿得亂用！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "並非我們少林弟子，何出此言？";

        if (! me->is_apprentice_of(this_object()))
                return "此招非我弟子不能傳，還望這位" +
                       RANK_D->query_respect(me) + "見諒。";

        if( query("shen", me)<120000 )
                return "此招用於降妖除魔，你既然不擅於此道，又何必學它？";

        if (me->query_skill("damo-jian", 1) < 200)
                return "你的達魔劍法還不到家，無法領會其中奧妙！";

        if( query("family/gongji", me)<600 )
                return "你為我少林派效力還不夠，這招我先不忙傳你。";

        message_vision(HIY "$n" HIY "看看$N" HIY
                       "，道：“好吧，你且聽仔細了！”説罷在$N"
                       HIY "耳邊輕聲説了些什麼。\n" NOR,
                       me, this_object());
        command("say 記住，除非降妖除魔萬不得已，勿要輕易使用。");
        tell_object(me, HIG "你學會了達魔亂氣劍。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 160000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1600000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/luan", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_qingxin()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/qingxin", me) )
                return "自己好好多練習吧，牢記慈悲為懷，勿得亂用！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "並非我們少林弟子，何出此言？";

        if (! me->is_apprentice_of(this_object()))
                return "此招非我弟子不能傳，還望這位" +
                       RANK_D->query_respect(me) + "見諒。";

        if( query("shen", me)<120000 )
                return "此招用於降妖除魔，你既然不擅於此道，又何必學它？";

        if (me->query_skill("damo-jian", 1) < 200)
                return "你的達魔劍法還不到家，無法領會其中奧妙！";

        if( query("family/gongji", me)<600 )
                return "你為我少林派效力還不夠，這招我先不忙傳你。";

        message_vision(HIY "$n" HIY "看看$N" HIY
                       "，道：“好吧，你且聽仔細了！”説罷在$N"
                       HIY "耳邊輕聲説了些什麼。\n" NOR,
                       me, this_object());
        command("say 記住，除非降妖除魔萬不得已，勿要輕易使用。");
        tell_object(me, HIG "你學會了達魔清心劍。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/qingxin", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_shang()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/shang", me) )
                return "自己好好多練習吧，牢記慈悲為懷，勿得亂用！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "並非我們少林弟子，何出此言？";

        if (! me->is_apprentice_of(this_object()))
                return "此招非我弟子不能傳，還望這位" +
                       RANK_D->query_respect(me) + "見諒。";

        if( query("shen", me)<120000 )
                return "此招用於降妖除魔，你既然不擅於此道，又何必學它？";

        if (me->query_skill("damo-jian", 1) < 200)
                return "你的達魔劍法還不到家，無法領會其中奧妙！";

        if( query("family/gongji", me)<600 )
                return "你為我少林派效力還不夠，這招我先不忙傳你。";

        message_vision(HIY "$n" HIY "看看$N" HIY
                       "，道：“好吧，你且聽仔細了！”説罷在$N"
                       HIY "耳邊輕聲説了些什麼。\n" NOR,
                       me, this_object());
        command("say 記住，除非降妖除魔萬不得已，勿要輕易使用。");
        tell_object(me, HIG "你學會了達魔傷神劍。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 160000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/shang", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_zhe()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/zhe", me) )
                return "自己好好多練習吧，牢記慈悲為懷，勿得亂用！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "並非我們少林弟子，何出此言？";

        if (! me->is_apprentice_of(this_object()))
                return "此招非我弟子不能傳，還望這位" +
                       RANK_D->query_respect(me) + "見諒。";

        if( query("shen", me)<120000 )
                return "此招用於降妖除魔，你既然不擅於此道，又何必學它？";

        if (me->query_skill("damo-jian", 1) < 200)
                return "你的達魔劍法還不到家，無法領會其中奧妙！";

        if( query("family/gongji", me)<600 )
                return "你為我少林派效力還不夠，這招我先不忙傳你。";

        message_vision(HIY "$n" HIY "看看$N" HIY
                       "，道：“好吧，你且聽仔細了！”説罷在$N"
                       HIY "耳邊輕聲説了些什麼。\n" NOR,
                       me, this_object());
        command("say 記住，除非降妖除魔萬不得已，勿要輕易使用。");
        tell_object(me, HIG "你學會了達魔折元劍。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 160000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/zhe", 1, me);
        addn("family/gongji", -600, me);
        return 1;
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

        case "達摩三絕劍" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/damo-jian/sanjue",
                           "name"    : "達摩三絕劍",
                           "sk1"     : "damo-jian",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 600, ]));
                break;

        case "燃木真焰" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/ranmu-daofa/zhenyan",
                           "name"    : "燃木真焰",
                           "sk1"     : "ranmu-daofa",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 600, ]));
                break;

        case "火麒蝕月" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/ranmu-daofa/huo",
                           "name"    : "火麒蝕月",
                           "sk1"     : "ranmu-daofa",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 600, ]));
                break;
        case "金剛伏魔決" :
               return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/jingang-zhi/fumo",
                             "name"    : "金剛伏魔決",
                             "sk1"     : "jingang-zhi",
                             "lv1"     : 120,
                             "sk2"     : "force",
                             "lv2"     : 120,
                             "sk3"     : "buddhism",
                             "lv3"     : 200,
                             "gongxian": 600, ]));
                  break;
        case "一指點三脈" :
               return MASTER_D->teach_pfm(me, this_object(),
                            ([ "perform" : "can_perform/jingang-zhi/san",
                               "name"    : "一指點三脈",
                               "sk1"     : "jingang-zhi",
                               "lv1"     : 120,
                               "sk2"     : "force",
                               "lv2"     : 120,
                               "sk3"     : "buddhism",
                               "lv3"     : 200,
                               "gongxian": 600, ]));
                    break;
        case "九陽真氣" :
                             return MASTER_D->teach_pfm(me, this_object(),
                              ([ "perform" : "can_exert/yijinjing/jiuyang",
                                 "name"    : "九陽真氣",
                                 "sk1"     : "yijinjing",
                                 "lv1"     : 120,
                                 "sk2"     : "force",
                                 "lv2"     : 120,
                                 "sk3"     : "buddhism",
                                 "lv3"     : 200,
                                 "gongxian": 600, ]));
                      break;
        case "佛光普照" :
                             return MASTER_D->teach_pfm(me, this_object(),
                              ([ "perform" : "can_exert/yijinjing/buddha",
                                 "name"    : "佛光普照",
                                 "sk1"     : "yijinjing",
                                 "lv1"     : 1000,
                                 "sk2"     : "force",
                                 "lv2"     : 1000,
                                 "sk3"     : "buddhism",
                                 "lv3"     : 1000,
                                 "reborn"  : 1,
                                 "gongxian": 3000, ]));
                      break;
        case "神劍指穴" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/lunhui-jian/zhi", 
                           "name"    : "神劍指穴", 
                           "sk1"     : "lunhui-jian", 
                           "lv1"     : 160, 
                           "force"   : 300, 
                           "gongxian": 550, 
                           "neili": 2000, 
                           "shen"    : 30000, ])); 
                break; 
        case "我入地獄" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/lunhui-jian/ru", 
                           "name"    : "我入地獄", 
                           "sk1"     : "lunhui-jian", 
                           "lv1"     : 200, 
                           "neili"   : 4000, 
                           "force"   : 300, 
                           "gongxian": 1000, 
                           "shen"    : 100000, ])); 
                break; 
        case "六道輪迴" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/lunhui-jian/lun", 
                           "name"    : "六道輪迴", 
                           "sk1"     : "lunhui-jian", 
                           "lv1"     : 240, 
                           "neili"   : 5000, 
                           "force"   : 350, 
                           "gongxian": 1500, 
                           "shen"    : 100000, ])); 
                break; 
         

        default:
                return 0;
        }
}
