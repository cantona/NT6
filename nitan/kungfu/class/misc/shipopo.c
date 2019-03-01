#include <ansi.h>
//#include "lingxiao.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("史婆婆", ({"shi popo", "shi", "popo"}));
        set("long", "她是雪山派掌門人白自在的妻子，雖說現在人已顯\n"
                    "得蒼老，十年前提起“江湖一枝花”史小翠來，武\n"
                    "林中卻是無人不知。\n");
        set("title", "金烏派開山祖師");
        set("gender", "女性");
        set("age", 58);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 4200);
        set("max_jing", 3500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 200);
        set("combat_exp", 2000000);

        set("inquiry",([
                "赤燄暴長" : (: ask_skill1 :),
        ]));

        set_skill("force", 220);
        set_skill("xueshan-neigong", 220);
        set_skill("wuwang-shengong", 180);
        set_skill("dodge", 220);
        set_skill("taxue-wuhen", 220);
        set_skill("cuff", 220);
        set_skill("lingxiao-quan", 220);
        set_skill("strike", 220);
        set_skill("piaoxu-zhang", 220);
        set_skill("sword", 200);
        set_skill("hanmei-jian", 200);
        set_skill("yunhe-jian", 200);
        set_skill("xueshan-jian", 200);
        set_skill("blade", 240);
        set_skill("jinwu-blade", 240);
        set_skill("parry", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("blade", "jinwu-blade");
        map_skill("parry", "jinwu-blade");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 5, "掌門夫人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.chi" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();

        carry_object("/clone/weapon/chaidao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object me)
{
        //if (! permit_recruit(me))
                return;

        if( query("family/master_name", me) == "白自在" || 
           query("family/master_name", me) == "白萬劍" )
        {
                command("say 嘿，你既然拜了老鬼小鬼為師，還來找我這老婆子作甚？");
                return;
        }

        if( query("shen", me)<10000 )
        {
                command("say 我武功不傳不義之人，你走開。");
                return;
        }

        if( query("combat_exp", me)<200000 )
        {
                command("say 你現在江湖經驗太淺，還是多鍛煉鍛煉再來吧。");
                return;
        }

        if ((int)me->query_skill("xueshan-neigong", 1) < 100)
        {
                command("say 你本門的內功心法太差，修煉好了之後再來找我。");
                return;
        }

        command("haha");
        command("say 今日我就收下你，你須得勤練功，他日必能勝過那個老鬼。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/jinwu-blade/chi", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裡來的？給我滾開！";

        if (me->query_skill("jinwu-blade", 1) < 1)
                return "你連金烏刀法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<800 )
                return "你在雪山派中碌碌無為，教我怎能放心傳你絕技。";

        if (me->query_skill("force") < 150)
                return "你的內功修行太淺，練好了再來找我。";

        if (me->query_skill("jinwu-blade", 1) < 120)
                return "你的金烏刀法練成這樣，居然還好意思找我。";

        message_vision( HIY "$n" HIY "道：“你能有今日這個地步，也"
                       "算不錯。今日我\n傳你雪山劍法的破解之法，你"
                       "可記牢了。雪山派劍法有\n七十二招，我金烏派"
                       "武功處處勝他一籌，卻有七十三招。\n咱們七十"
                       "三招破他七十二招，最後一招瞧仔細了！”說\n"
                       "著拔出腰間柴刀從上而下直劈下來，又道：“你"
                       "使這招\n之時，須得躍起半空，和身直劈！”當"
                       "下又教將如何運\n勁，如何封死對方逃遁的空隙"
                       "等竅門慢慢傳給$N" HIY "，$N" HIY "凝\n思半"
                       "晌，依法施為，縱身躍起，半空中揮刀直劈，呼"
                       "的\n一聲，刀鋒離地尚有數尺，地下已是塵沙飛"
                       "揚，敗草落\n葉被刀風激得團團而舞，果然威力"
                       "驚人。\n" NOR, me, this_object());
        command("heng");
        command("say 這一招可盡破雪山劍法，你自己下去練吧。");
        tell_object(me, HIC "你學會了「赤燄暴長」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("jinwu-blade"))
                me->improve_skill("jinwu-blade", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinwu-blade/chi", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}
