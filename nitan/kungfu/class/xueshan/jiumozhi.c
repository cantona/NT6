// This program is a part of NT MudLIB
// /kungfu/class/xueshan/jiumozhi.c 鳩摩智

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "xueshan.h"

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("鳩摩智", ({ "jiumo zhi", "zhi" ,"ming wang"}));
        set("nickname", HIG "大輪明王" NOR);
        set("long",@LONG
他就是雪山寺的掌門，人稱大輪明王的鳩摩智。他對佛法有精深的研究。
身穿一件大紅袈裟，頭帶僧帽。
LONG
        );
        set("title","雪山寺掌門");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 32);
        set("int", 40);
        set("con", 31);
        set("dex", 31);

        set("max_qi", 5800);
        set("max_jing", 2900);
        set("neili", 7100);
        set("max_neili", 7100);
        set("jiali", 100);
        set("level", 40);
        set("combat_exp", 2500000);

        set_skill("force", 600);
        set_skill("xiaowuxiang", 600);
        set_skill("mizong-neigong", 600);
        set_skill("dodge", 600);
        set_skill("shenkong-xing", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("hammer", 600);
        set_skill("dali-chu", 600);
        set_skill("xiangmo-chu", 600);
        set_skill("lamaism", 600);
        set_skill("literate", 600);
        set_skill("strike", 600 );
        set_skill("huoyan-dao", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("hand", 600);
        set_skill("dashou-yin", 600);
        set_skill("martial-cognize", 600);
        set_skill("longxiang-gong", 600);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("strike","huoyan-dao");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hammer", "xiangmo-chu");

        prepare_skill("strike", "huoyan-dao");
        prepare_skill("hand", "dashou-yin");

        create_family("雪山寺", 1, "掌門");
        set("class", "bonze");

        set("inquiry", ([
                "絕招" : (: ask_me :),
                "絕技" : (: ask_me :),
                "焚身" : (: ask_me :),
                "天寰神炎" : (: ask_skill :),
        ]));

        set("master_ob", 5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/r-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",50);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/huoyan-dao/fen", me) )
                return "絕技你已經學會了，剩下的就要靠你自己多練習了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "既然不是我們雪山寺之人，有什麼好談的。";

        if (me->query_skill("huoyan-dao", 1) < 120)
                return "你的火焰刀法修為還不夠，等你練好了再説吧！";

        if( query("family/gongji", me)<300 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        message_vision(HIC "$n" HIC "右掌一豎，幾路無形刀氣襲擊向$N"
                       HIC "，$N" HIC "連忙伸手格擋，不禁發現$n"
                       HIC "的內力運用可謂是奧妙無窮！\n" NOR,
                       me, this_object());
        command("simle");
        tell_object(me, HIG "你通曉了焚身的奧妙。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huoyan-dao/fen", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "男性" )
        {
                command("say 修習密宗內功需要純陽之體。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "還是請回吧！");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say 我佛門的清規戒律甚多。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "還是請回吧！");
                return;
        }

        if( query("family/family_name", ob) != "雪山寺" )
        {
                command("say 這位" + RANK_D->query_respect(ob) +
                        "既非本寺弟子，還是請回吧！");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 150) {
                command("say 入我雪山寺，修習密宗心法是首要的。");
                command("say 這位" + RANK_D->query_respect(ob) +
                        "是否還應該多多鑽研本門的心法？");
                return;
        }

        command("recruit "+query("id", ob));
        set("title", HIY"法王"NOR, ob);
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if( query("can_perform/huoyan-dao/yan", me) )
                return "你又來幹什麼？自己下去多練。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我又不認識你，打聽這個幹什麼？";

        if (me->query_skill("huoyan-dao", 1) < 1)
                return "你連無上火焰刀都沒學，哪裏來絕招？";

        if( query("family/gongji", me)<400 )
                return "你為雪山寺效力不夠，這招暫時還不能傳你。";

        if( query("shen", me)>-3000 )
                return "你為人太過心軟，這招暫時還不能傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功修為不足，還學不了這一招。";

        if( query("max_neili", me)<800 )
                return "你的內力修為不足，還是修煉高點再來吧。";

        if (me->query_skill("huoyan-dao", 1) < 80)
                return "等你把火焰刀練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，喝道：“瞧仔"
                     "細了。”話音剛落，只見$n" HIY "高舉手中的剛刀，在"
                     "空中揮舞成盤，氣勢驚人！便在此時，那柄剛刀已攜帶"
                     "着震天撞擊之聲猛然擊落。直把$N" HIY "看得目瞪口呆"
                     "。\n\n" NOR, me, this_object());

        command("nod");
        command("say 看明白了就自己下去練吧。");
        tell_object(me, HIC "你學會了「天寰神炎」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huoyan-dao/yan", 1, me);
        addn("family/gongji", -400, me);

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

        case "修羅降世" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huoyan-dao/xiuluo",
                           "name"    : "修羅降世",
                           "sk1"     : "huoyan-dao",
                           "lv1"     : 100,
                           "sk2"     : "strike",
                           "lv2"     : 120,
                           "gongxian": 800, ]));
                break;

        case "紅蓮火" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huoyan-dao/honglian",
                           "name"    : "紅蓮火",
                           "sk1"     : "huoyan-dao",
                           "lv1"     : 150,
                           "sk2"     : "strike",
                           "lv2"     : 150,
                           "gongxian": 800, ]));
        case "十龍十象" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/longxiang-gong/longxiang", 
                           "name"    : "十龍十象", 
                           "sk1"     : "longxiang-gong", 
                           "lv1"     : 1000, 
                           "sk2"     : "force", 
                           "lv2"     : 1000,
                           "reborn"  : 1,
                           "gongxian": 3000, ])); 
                break; 
                break;
        default:
                return 0;
        }
}

