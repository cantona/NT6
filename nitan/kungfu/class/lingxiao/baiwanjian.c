#include <ansi.h>
#include "lingxiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();

void create()
{
        object ob;
        set_name("白萬劍", ({"bai wanjian", "bai", "wanjian"}));
        set("nickname", HIW "氣寒西北" NOR);
        set("long", "白萬劍是雪山派掌門人威德先生白自在的長子，他\n"
                    "們師兄弟均以“萬”字排行，他名字居然叫到白萬\n"
                    "劍，足見劍法之高。\n");
        set("gender", "男性");
        set("age", 34);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 3800);
        set("max_jing", 3000);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 180);
        set("combat_exp", 1000000);

        set("inquiry",([
                "冷劍決"   : (: ask_skill1 :),
                "凌霄總訣" : (: ask_skill2 :),
                "飛絮飄零" : (: ask_skill3 :),
                "鶴衝九霄" : (: ask_skill4 :),
                "風迴雪舞" : (: ask_skill5 :),
                "雪花六出" : (: ask_skill6 :),
        ]));

        set_skill("force", 200);
        set_skill("xueshan-neigong", 200);
        set_skill("dodge", 200);
        set_skill("taxue-wuhen", 200);
        set_skill("cuff", 180);
        set_skill("lingxiao-quan", 180);
        set_skill("strike", 180);
        set_skill("piaoxu-zhang", 180);
        set_skill("sword", 220);
        set_skill("hanmei-jian", 220);
        set_skill("yunhe-jian", 220);
        set_skill("xueshan-jian", 220);
        set_skill("parry", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 150);

        map_skill("force", "xueshan-neigong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "yunhe-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 6, "掌門弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.chu" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();

        if (clonep())
        {
                ob=new(WEAPON_DIR"treasure/baihong-jian");
                if ( ob->violate_unique())
                 {
                         destruct(ob);
                         ob=new(WEAPON_DIR"changjian");
                 }
                 ob->move(this_object());
                 ob->wield();
        }
        carry_object("/clone/money/gold");
        carry_object(CLOTH_DIR+"bai")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<3000 )
        {
                command("say 學武須先正身，試問德行這一項，你做得夠嗎？");
                return;
        }

        if( query("combat_exp", me)<150000 )
        {
                command("say 你現在江湖經驗太淺，還是多鍛鍊鍛鍊再來吧。");
                return;
        }

        if ((int)me->query_skill("xueshan-neigong", 1) < 80)
        {
                command("say 你本門的內功心法太差，修煉好了之後再來找我。");
                return;
        }

        if ((int)me->query_skill("sword", 1) < 80)
        {
                command("say 你的劍法根基實在是太差，下去多練練再來。");
                return;
        }

        command("say 很好，很好。");
        command("say 念在你有心，今日我便收你為徒，希望日後能有一翻作為。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/hanmei-jian/leng", me) )
                return "自己下去練，別在這裏跟我羅嗦個沒完！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下從何而來，這樣打聽我雪山派絕招是什麼意思？";

        if (me->query_skill("hanmei-jian", 1) < 1)
                return "你連寒梅劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<50 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 50)
                return "你的內功修行實在太差，下去練練再來！";

        if (me->query_skill("hanmei-jian", 1) < 40)
                return "虧你寒梅劍法練成這樣，也好意思來找我。";

        message_vision(HIY "$n" HIY "略微點了點頭，將$N" HIY "招至"
                        "跟前。輕聲在$N" HIY "耳畔細説\n良久，時不"
                        "時還伸手演化劍招，$N" HIY "一邊聽一邊點頭"
                        "。\n" NOR, me, this_object());
        command("nod");
        command("say 這招很簡單，你下去照我説的練習便成。");
        tell_object(me, HIC "你學會了「冷劍決」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("hanmei-jian"))
                me->improve_skill("hanmei-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hanmei-jian/leng", 1, me);
        addn("family/gongji", -50, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/lingxiao-quan/jue", me) )
                return "自己下去練，別老跟我糾纏不休！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下無故打聽我雪山派的絕招是什麼意思？";

        if (me->query_skill("lingxiao-quan", 1) < 1)
                return "你連凌霄拳法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<100 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功修行實在太差，下去練練再來！";

        if (me->query_skill("lingxiao-quan", 1) < 60)
                return "虧你凌霄拳法練成這樣，也好意思來找我。";

        message_vision(HIY "$n" HIY "打量了$N" HIY "一翻，然後微微一"
                       "笑，示以讚許。又將$N" HIY "\n招至跟前，輕聲在"
                       "$N" HIY "耳畔細説良久，時不時還伸手比出幾\n式"
                       "拳法中的精妙之處，$N" HIY "一邊聽一邊點頭。\n"
                       NOR, me, this_object());
        command("nod");
        command("say 這招並不難，只需切記‘御力而發’四字即可。");
        tell_object(me, HIC "你學會了「凌宵總訣」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("lingxiao-quan"))
                me->improve_skill("lingxiao-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingxiao-quan/jue", 1, me);
        addn("family/gongji", -100, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/piaoxu-zhang/piao", me) )
                return "自己下去練，別在這裏跟我羅嗦個沒完！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下無故打聽我雪山派的絕招是什麼意思？";

        if (me->query_skill("piaoxu-zhang", 1) < 1)
                return "你連飄絮掌法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<150 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功修行實在太差，下去練練再來！";

        if (me->query_skill("piaoxu-zhang", 1) < 80)
                return "虧你飄絮掌法練成這樣，也好意思來找我。";

        message_vision(HIY "$n" HIY "略微點了點頭，説道：“我給你演示"
                      "一遍，可得瞧\n仔細了！”隨即一聲清嘯，雙掌紛飛"
                      "貫出，掌影重重疊疊\n虛實難辨，全全籠罩$N" HIY
                      "全身。\n" NOR, me, this_object());
        command("nod");
        command("say 剛才我所演示的全是這招的精華，你下去照着練就行了。");
        tell_object(me, HIC "你學會了「飛絮飄零」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("piaoxu-zhang"))
                me->improve_skill("piaoxu-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/piaoxu-zhang/piao", 1, me);
        addn("family/gongji", -150, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/yunhe-jian/chong", me) )
                return "自己下去練，別老跟我糾纏不休！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下這樣打聽我雪山派絕招是什麼意思？";

        if (me->query_skill("yunhe-jian", 1) < 1)
                return "你連雲鶴七劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功修行實在太差，下去練練再來！";

        if (me->query_skill("yunhe-jian", 1) < 100)
                return "虧你雲鶴七劍練成這樣，也好意思來找我。";

        message_vision(HIY "$n" HIY "點了點頭，隨手從身後的書架上取"
                       "出一本劍經，指\n着其中一段對$N" HIY "細説了"
                       "良久，$N" HIY "一邊聽一邊點頭。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 這招很簡單，你下去照我説的練習便成。");
        tell_object(me, HIC "你學會了「鶴衝九霄」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yunhe-jian"))
                me->improve_skill("yunhe-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yunhe-jian/chong", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/xueshan-jian/hui", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裏來的？快給我快快滾開！";

        if (me->query_skill("xueshan-jian", 1) < 1)
                return "你連雪山劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<500 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("xueshan-jian", 1) < 30)
                return "你雪山劍法尚未修煉得精深，沒法用這招。";

        message_vision(HIY "$n" HIY "微微一笑，點了點頭。説着便在$N" HIY
                        "耳邊輕聲述説劍\n訣精要，一邊説還一邊比劃着些什"
                       "麼。過了良久，只見$N" HIY "\n會心的一笑，似乎有"
                       "了什麼新的感悟。\n" NOR, me, this_object());
        command("smile");
        command("say 這一招看似複雜，實卻簡潔，稍加練習便成。");
        tell_object(me, HIC "你學會了「風迴雪舞」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("xueshan-jian"))
                me->improve_skill("xueshan-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xueshan-jian/hui", 1, me);
        addn("family/gongji", -500, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/xueshan-jian/chu", me) )
                return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪裏來的？快給我快快滾開！";

        if (me->query_skill("xueshan-jian", 1) < 1)
                return "你連雪山劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1000 )
                return "哼，你在本派中無所作為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功修行太淺，用不了這一招！";

        if (me->query_skill("xueshan-jian", 1) < 140)
                return "你雪山劍法尚未修煉得精深，沒法用這招。";

        message_vision(HIY "$n" HIY "微微一笑，對$N" HIY "讚道：“想"
                       "不到今日你能有如此造\n詣，我這就傳你這招。”"
                        "説完$n" HIY "拔出配劍，單手握住\n劍訣，頓時"
                       "只見長劍抖動，虛中有實，實中有虛，劍尖劍\n鋒"
                        "齊用，凌厲刺出。$N" HIY "只覺眼前劍光一閃而"
                       "過，隨即木屑\n紛飛，面前的紅漆門柱上竟豁然印"
                       "出六道劍痕，便宛如盛\n開的梅花一般，精雕細琢"
                       "也不過如此。\n" NOR, me, this_object());
        command("haha");
        command("say 這一招便是雪花六出，你下去後需得勤加練習。");
        tell_object(me, HIC "你學會了「雪花六出」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("xueshan-jian"))
                me->improve_skill("xueshan-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xueshan-jian/chu", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
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
