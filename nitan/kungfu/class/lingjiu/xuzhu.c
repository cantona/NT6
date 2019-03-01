// This program is a part of NT MudLIB

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();

void create()
{
        set_name("虛竹子", ({ "xuzhu zi", "xuzhu", "xu", "zhu", "zi" }));
        set("long", @LONG
這便是縹緲峰靈鷲宮掌門，道號虛竹子。他看
起來約莫二十五六歲，長得濃眉大眼，大大的
鼻子扁平下塌，容貌頗為醜陋。身穿一件華貴
雅致的長袍，倒使他更顯幾分精神。
LONG );
        set("title", "縹緲峰靈鷲宮掌門");
        set("gender", "男性");
        set("age", 26);
        set("nickname", HIM "夢郎" NOR);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 35);
        set("int", 15);
        set("con", 35);
        set("dex", 35);

        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 3500000);

        set_skill("force", 600);
        set_skill("xiaowuxiang", 600);
        set_skill("hunyuan-yiqi", 600);
        set_skill("beiming-shengong", 600);
        set_skill("bahuang-gong", 600);
        set_skill("dodge", 600);
        set_skill("yueying-wubu", 600);
        set_skill("shaolin-shenfa", 600);
        set_skill("parry", 600);
        set_skill("hand", 600);
        set_skill("zhemei-shou", 600);
        set_skill("strike", 600);
        // set_skill("piaomiao-zhang", 440);
        set_skill("liuyang-zhang", 600);
        set_skill("cuff", 600);
        set_skill("luohan-quan", 600);
        set_skill("sword", 600);
        set_skill("tianyu-qijian", 600);
        set_skill("throwing", 600);
        set_skill("buddhism", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        set("no_teach", ([
                "hunyuan-yiqi"    : "…這…這東西我都沒學好。",
                // "xiaowuxiang"      : "唉……這是師尊注如我體內的，教我怎麼教給你？",
                "beiming-shengong" : "唉……這是師尊注如我體內的，教我怎麼教給你？",
                "shaolin-shenfa"   : "…這個…嗯…我還是教你本門的輕功好了。",
        ]));

        map_skill("force", "bahuang-gong");
        map_skill("dodge", "yueying-wubu");
        map_skill("strike", "liuyang-zhang");
        map_skill("hand", "zhemei-shou");
        map_skill("cuff", "luohan-quan");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");
        map_skill("throwing", "liuyang-zhang");

        prepare_skill("hand", "zhemei-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("靈鷲宮", 2, "弟子");

        set("inquiry", ([
                "閃劍訣" : (: ask_skill1 :),
                "幻劍訣" : (: ask_skill2 :),
                "聚劍訣" : (: ask_skill3 :),
                "折梅式" : (: ask_skill4 :),
                "海淵式" : (: ask_skill5 :),
                "生死符" : (: ask_skill6 :),
                "寰陽式" : (: ask_skill7 :),
                "破神訣" : (: ask_skill8 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhe" :),
                (: perform_action, "hand.hai" :),
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.zhong" :),
                (: perform_action, "strike.po" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object("/d/lingjiu/obj/changpao")->wear();
        add_money("silver", 50);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 這位施主…不…是這位閣下眼中似乎邪氣太重。");
                command("say 你做點善事之後再來找我吧。");
                return;
        }

        if ((int)ob->query_skill("xiaowuxiang", 1) < 100)
        {
                command("say 這個…這小無相功…應該算是本門修煉內功的基礎。");
                command("say 現在嘛…嗯…你還是回去練練吧。");
                return;
        }

        if( query("max_neili", ob)<1200 )
        {
                command("say 這靈鷲宮和少林寺都一樣，武功好不好全看內力。");
                command("say 小僧勸…不…是在下勸你還是再回去練練吧。");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say 你這個…你經驗不足，還是去鍛煉一下再說吧。");
                return;
        }

        command("nod");
        command("say 今日小僧…在下就收下你，以後你要多做好事。");
        command("say 另外，以後若遇到了少林寺的大師，可千萬不能和他們為難。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "dancer" )
                set("class", "dancer", ob);
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/tianyu-qijian/shan", me) )
                return "我…我好象…我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("tianyu-qijian", 1) < 1)
                return "你…這個…你好象連天羽奇劍都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<100 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if (me->query_skill("force") < 100)
                return "…嗯…你的內功火候不足，學不成這招。";

        if (me->query_skill("tianyu-qijian", 1) < 60)
                return "…嗯…你的天羽奇劍還…還得多下功夫練練。";

        message_vision(HIY "$n" HIY "點了點頭，從懷中輕輕取出了一本"
                       "劍譜，指著其中的一段對\n$N" HIY "結節不納的"
                       "細說良久，$N" HIY "一邊聽一邊點頭。\n" NOR,
                       me, this_object());


        command("nod");
        command("say 這招的變化很煩瑣，需要多多練習。");
        tell_object(me, HIC "你學會了「閃劍訣」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("tianyu-qijian"))
                me->improve_skill("tianyu-qijian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tianyu-qijian/shan", 1, me);
        addn("family/gongji", -100, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/tianyu-qijian/huan", me) )
                return "我…我好象…我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("tianyu-qijian", 1) < 1)
                return "你…這個…你好象連天羽奇劍都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<300 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if (me->query_skill("force") < 160)
                return "…嗯…你的內功火候不足，學不成這招。";

        if (me->query_skill("tianyu-qijian", 1) < 120)
                return "…嗯…你的天羽奇劍還…還得多下功夫練練。";

        message_vision(HIY "$n" HIY "笑了笑，當即從$N" HIY "手中接過"
                       "長劍，慢慢的演示劍招，$N" HIY "見招\n式優美華"
                       "麗，輕盈靈動，實乃前所謂聞，頓時大有所悟。\n"
                       NOR, me, this_object());

        command("nod");
        command("say  …嗯…你自己下去練吧。");
        tell_object(me, HIC "你學會了「幻劍訣」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("tianyu-qijian"))
                me->improve_skill("tianyu-qijian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tianyu-qijian/huan", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/tianyu-qijian/ju", me) )
                return "你…你這個…這招你不是已經學會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("tianyu-qijian", 1) < 1)
                return "你…這個…你好象連天羽奇劍都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<400 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if (me->query_skill("force") < 180)
                return "…嗯…你的內功火候不足，學不成這招。";

        if (me->query_skill("tianyu-qijian", 1) < 130)
                return "…嗯…你的天羽奇劍還…還得多下功夫練練。";

        message_vision(HIY "$n" HIY "點了點頭，從$N" HIY "手中接過"
                       "長劍，手腕輕輕一抖，長劍便化作\n一道彩虹，"
                       "劍光劍花聚為一線，光華眩目，籠罩著$N" HIY
                       "四周。\n" NOR, me, this_object());

        command("nod");
        command("say 能講的我都講給你聽了，這個…這剩下的就靠你自己了。");
        tell_object(me, HIC "你學會了「聚劍訣」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("tianyu-qijian"))
                me->improve_skill("tianyu-qijian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tianyu-qijian/ju", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/zhe", me) )
                return "你…這個…這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你…這個…你好象連逍遙折梅手都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<300 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if (me->query_skill("force") < 120)
                return "…嗯…你的內功火候不足，學不成這招。";

        if (me->query_skill("zhemei-shou", 1) < 80)
                return "…嗯…你的逍遙折梅手還…還得多下功夫練練。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微微一笑。當下"
                       "一聲清嘯，合逍遙折梅手諸多變\n化為一式，隨手"
                       "輕輕揮出，招數虛虛實實，煞是精妙。直看得$N"
                       HIY "眼\n花繚亂，目瞪口呆。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 招式你都看過了，這…剩下的就靠你自己了。");
        tell_object(me, HIC "你學會了「折梅式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/zhe", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hai", me) )
                return "你…這個…這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你…這個…你好象連逍遙折梅手都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<800 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if (me->query_skill("force") < 200)
                return "…嗯…你的內功火候不足，學不成這招。";

        if (me->query_skill("zhemei-shou", 1) < 130)
                return "…嗯…你的逍遙折梅手還…還得多下功夫練練。";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，當下也不答"
                       "話，單手輕輕一揮而出，手出如\n風，單掌頓時變"
                       "化出漫天掌影，虛虛實實，重重疊疊，霎那間已罩"
                       "\n住$N" HIY "周身穴道，$n" HIY "那掌影卻只是"
                       "一沾而過，未傷$N" HIY "半毫。招數\n之巧妙，當"
                       "真只能用“無可比擬”四字形容。\n" NOR, me,
                       this_object());

        command("nod2");
        command("say 此招便如海之浩瀚，淵之深絕，可要勤加練習。");
        tell_object(me, HIC "你學會了「海淵式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hai", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/zhong", me) )
                return "你…這個…這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你…這個…你好象連天山六陽掌都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<600 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if (me->query_skill("force") < 200)
                return "…嗯…你的內功火候不足，學不成這招。";

        if (me->query_skill("liuyang-zhang", 1) < 150)
                return "…嗯…你的天山六陽掌還…還得多下功夫練練。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微作遲疑，但接"
                       "著點了點頭，將$N" HIY "招至身邊，在\n耳旁低聲"
                       "細說良久，$N" HIY "聽後會心的一笑，看來大有所"
                       "悟。\n" NOR, me, this_object());

        command("buddhi");
        command("say 這…這招厲害得緊，平時可不能胡亂使用。");
        tell_object(me, HIC "你學會了「生死符」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/zhong", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/huan", me) )
                return "你…這個…這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你…這個…你好象連天山六陽掌都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<1000 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if (me->query_skill("force") < 200)
                return "…嗯…你的內功火候不足，學不成這招。";

        if (me->query_skill("liuyang-zhang", 1) < 130)
                return "…嗯…你的天山六陽掌還…還得多下功夫練練。";

        message_vision(HIY "$n" HIY "微微一笑，慢悠悠伸出一掌，正搭"
                       "在$N" HIY "的左肩之上，$N" HIY "稍作\n詫異，"
                       "霎時只覺$n" HIY "內力源源不絕的洶湧而入，異"
                       "種真氣注滿體\n內，全身竟似快要炸裂開來，不禁"
                       "花容失色。\n" NOR, me, this_object());

        command("say 你懂了嗎？");
        tell_object(me, HIC "你學會了「寰陽式」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/huan", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/po", me) )
                return "你…你自己下去練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那個…你好象不是我靈鷲宮的人吧？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你…這個…你好象連天山六陽掌都沒學吧，不學哪來絕招？";

        if( query("family/gongji", me)<2200 )
                return "…這個…你既然投入了我們靈鷲宮門下，還是…多多少少幫著做點事吧。";

        if ((int)me->query_skill("bahuang-gong", 1) < 220)
                return "…嗯…你的八荒六合唯我獨尊功火候不足，學不成這招。";

        if (me->query_skill("liuyang-zhang", 1) < 220)
                return "…嗯…你的天山六陽掌還…還得多下功夫練練。";

        if( query("max_neili", me)<3500 )
                return "你的內力修為不夠，運用這招…嗯…還比較困難。";

        message_vision(HIY "$n" HIY "對$N" HIY "微微一笑，模樣頗為讚"
                       "許，說道：“我在這裡給你演示\n一遍，能否領悟"
                       "就全靠你的悟性了。”話音剛落，只見$n" HIY "催"
                       "動\n內勁，身形急轉，體內真氣迸發，長袍隨之鼓"
                       "脹。陡然之間，呼的\n一掌猛然拍落，頓時風聲四"
                       "起，塵沙彌漫。待得良久，方才煙消雲\n散，$N"
                       HIY "到這時才發現$n" HIY "身前青石磚地已被他震"
                       "開了一條長達四\n丈，寬約七尺的裂縫，掌法之玄"
                       "奇，當真驚天地，泣鬼神。\n" NOR, me,
                       this_object());

        command("buddhi");
        command("say 這招乃是我從石壁上習得，想必是童姥生前所創。");
        command("say ……唉…這招的威力太過強盛，切末胡亂使用。");
        tell_object(me, HIC "你學會了「破神訣」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("bahuang-gong"))
                me->improve_skill("bahuang-gong", 1500000);
        if (me->can_improve_skill("bahuang-gong"))
                me->improve_skill("bahuang-gong", 1500000);
        if (me->can_improve_skill("bahuang-gong"))
                me->improve_skill("bahuang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/po", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

/*
void unconcious()
{
        die();
}
*/
