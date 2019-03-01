#include <ansi.h>
#include "duan.h"

#define MAIJING "/clone/lonely/book/jingluoxue1"
#define MAIJING2 "/clone/lonely/book/jingluoxue2"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_maijing1();
mixed ask_maijing2();

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();

void create()
{
        set_name("段正明", ({ "duan zhengming", "duan", "zhengming" }));
        set("title", "大理國國王" );
        set("nickname", HIY "保定帝" NOR);
        set("long", "他就是大理國的國王，繼承這近三百年的基業。\n");
        set("gender", "男性");
        set("age", 49);
        set("class", "royal");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 32);
        set("int", 35);
        set("con", 32);
        set("dex", 29);

        set("max_qi", 6000);
        set("max_jing", 4000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("combat_exp", 3000000);
        set("score", 60000);

        set_skill("force", 650);
        set_skill("duanshi-xinfa", 650);
        set_skill("kurong-changong", 600);
        set_skill("dodge", 600);
        set_skill("tiannan-bu", 600);
        set_skill("cuff", 600);
        set_skill("jinyu-quan", 600);
        set_skill("strike", 600);
        set_skill("wuluo-zhang", 600);
        set_skill("sword", 600);
        set_skill("staff", 600);
        set_skill("duanjia-jian", 600);
        set_skill("finger", 650);
        set_skill("qiantian-zhi", 600);
        set_skill("sun-finger", 650);
        set_skill("parry", 600);
        set_skill("jingluo-xue", 650);
        set_skill("buddhism", 600);
        set_skill("literate", 600);
        set_skill("qimai-liuzhuan", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        create_family("段氏皇族", 15, "傳人");

        set("inquiry", ([
                "五絕連環"   : (: ask_skill1 :),
                "起死回生"   : (: ask_skill2 :),
                "神指點穴"   : (: ask_skill3 :),
                "一指乾坤"   : (: ask_skill4 :),
                // "五絕劍"     : (: ask_skill5 :),
                // "王叔和脈經" : (: ask_maijing1 :),
                // "玉顴神脈經" : (: ask_maijing2 :),
                "陽關三疊"   : "唉…說來慚愧，這一招連我自己都還未領悟透徹。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "finger.die" :),
                (: perform_action, "sword.jing" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<50000 )
        {
                command("say 你江湖上的名聲不怎麼樣，這樣的人如何能夠治好"
                        "國家？");
                return;
        }


        if (ob->query_skill("duanshi-xinfa", 1) < 100)
        {
                command("say 你先好好學習我們段家的心法，以後我再指點你。");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say 你實戰經驗太低，應好好在江湖上歷煉，不要失了"
                        "段氏的面子。\n");
                return;
        }

        command("say 好，我收下你了，武技固然重要，也不要忘記讀書治國。");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/lian", me) )
                return "你不是已經學會了麼？還有什麼疑問？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我們段家的傳人，這話是什麼意思？";

        if (me->query_skill("duanjia-jian", 1) < 1)
                return "你連段家劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在族裡碌碌無為，叫我如何信得過你？";

        if( query("shen", me)<0 )
                return "算了吧，傳你絕招只怕你又去作惡！";

        if (me->query_skill("force") < 120)
                return "你的內功的修為不夠，練高了再來吧。";

        if (me->query_skill("duanjia-jian", 1) < 120)
                return "你的段家劍法還不行，練練再說吧！";

        message_sort(HIY "\n$n" HIY "點了點頭，喝道：“看好了！”忽然欺上前"
                     "來，以手為劍，接連攻出數招，招式精奇無比，$N" HIY "大"
                     "吃一驚，只能後退。\n\n" NOR, me, this_object());

        command("nod");
        command("say 你看清楚了麼？以後要行俠仗義，莫要胡作非為！");
        tell_object(me, HIC "你學會了「五絕連環」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("duanjia-jian"))
                me->improve_skill("duanjia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/duanjia-jian/lian", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/sun-finger/heal", me) )
                return "你不是已經學會了麼？還有什麼疑問？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我們段家的傳人，這話是什麼意思？";

        if (me->query_skill("sun-finger", 1) < 1)
                return "你連一陽指訣都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<800 )
                return "你在族裡碌碌無為，叫我如何信得過你？";

        if (me->query_skill("force") < 150)
                return "你內功的修為還不夠，練高了再來吧。";

        if( query("max_neili", me)<1500 )
                return "你的內力修為還不夠，練高點再來吧。";

        /*
        if (me->query_skill("jingluo-xue", 1) < 100)
                return "你對經絡學的了解還不透徹，研究透了再來找我吧。";
        */

        if (me->query_skill("sun-finger", 1) < 100)
                return "你的一陽指訣功力還不夠，練高了再說吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，伸出一指，出手如風，瞬間"
                     "拂過$N" HIY "胸前諸多大穴，$N" HIY "頓時只覺$n" HIY
                     "內力源源不絕的湧入，全身一陣酸麻，不禁大驚失色。\n"
                     "\n" NOR, me, this_object());

        command("smile");
        command("say 招式便是如此，你懂了嗎？");
        command("say 此招療傷效果雖是天下無雙，但對自身的損害卻是太大。");
        tell_object(me, HIC "你學會了「起死回生」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sun-finger/heal", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/sun-finger/dian", me) )
                return "你不是已經學會了麼？還有什麼疑問？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我們段家的傳人，這話是什麼意思？";

        if (me->query_skill("sun-finger", 1) < 1)
                return "你連一陽指訣都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在族裡碌碌無為，叫我如何信得過你？";

        if( query("shen", me)<20000 )
                return "你俠義正事做得不夠，這招我暫時還不能傳你！";

        if (me->query_skill("force") < 160)
                return "你內功的修為還不夠，練高了再來吧。";

        if( query("max_neili", me)<1800 )
                return "你的內力修為還不夠，練高點再來吧。";

        /*
        if (me->query_skill("jingluo-xue", 1) < 120)
                return "你對經絡學的了解還不透徹，研究透了再來找我吧。";
        */

        if (me->query_skill("sun-finger", 1) < 120)
                return "你的一陽指訣功力還不夠，練高了再說吧。";

        message_sort(HIY "\n$n" HIY "略微點了點頭，說道：“看好了！”說罷$n"
                     HIY "凝聚一陽指訣功力，陡然點出一指，變化多端，巧逼$N"
                     HIY "諸處大穴，招式煞為精妙。\n\n" NOR, me, this_object());

        command("haha");
        command("say 招式便是如此，你自己下去練吧。");
        tell_object(me, HIC "你學會了「神指點穴」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sun-finger/dian", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/sun-finger/qian", me) )
                return "你不是已經學會了麼？還有什麼疑問？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我們段家的傳人，這話是什麼意思？";

        if (me->query_skill("sun-finger", 1) < 1)
                return "你連一陽指訣都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1000 )
                return "你在族裡碌碌無為，叫我如何信得過你？";

        if( query("shen", me)<30000 )
                return "你俠義正事做得不夠，這招我暫時還不能傳你！";

        if (me->query_skill("force") < 120)
                return "你內功的修為還不夠，練高了再來吧。";

        if( query("max_neili", me)<2400 )
                return "你的內力修為還不夠，練高點再來吧。";

        /*
        if (me->query_skill("jingluo-xue", 1) < 160)
                return "你對經絡學的了解還不透徹，研究透了再來找我吧。";
        */

        if (me->query_skill("sun-finger", 1) < 120)
                return "你的一陽指訣功力還不夠，練高了再說吧。";

        message_sort(HIY "\n$n" HIY "凝視了$N" HIY "好一會兒，隨即點了點"
                     "頭，將$N" HIY "招至身邊，在耳旁低聲細說良久，$N" HIY
                     "聽後會心的一笑，看來對$n" HIY "的教導大有所悟。\n\n"
                     NOR, me, this_object());

        command("nod");
        command("say 此招殺傷略重，平時一定要慎用。");
        tell_object(me, HIC "你學會了「一指乾坤」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sun-finger/qian", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/jue", me) )
                return "你不是已經學會了五絕劍麼？還有什麼疑問麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我們段家的傳人，這是什麼意思？";

        if( query("shen", me)<0 )
                return "算了吧，傳你絕招只怕你又去作惡！";

        if (me->query_skill("duanjia-jian", 1) < 100)
                return "你的段家劍法還不行，練練再說吧！";

        message_vision(HIC "$n" HIC "點點頭，忽然欺上前來，以"
                       "手為劍連出幾招，招式精奇無比，$N"
                       HIC "大吃一驚，只能後退。\n" NOR,
                       me, this_object());
        command("smile");
        command("say 你看清楚了麼？以後多要行俠仗義，莫要胡作非為！");
        tell_object(me, HIG "你學會了段家五絕劍。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        set("can_perform/duanjia-jian/jue", 1, me);
        return 1;
}

mixed ask_maijing1()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "段氏皇族" )
                return "你又不是我們段家的傳人，這話是什麼意思？";

        if( query("family/master_id", me) != query("id") )
                return "…嗯…等你成為我的弟子後再說吧。";

        if( query("shen", me)<10000 )
                return "你俠義正事做得不夠，這脈經我不能給你。";

        if( query("combat_exp", me)<10000 )
                return "你現在經驗太淺，不用忙著去閱讀脈經。";

        if (me->query_skill("jingluo-xue", 1) > 149)
                return "你對經絡學的了解已經很透徹，遠勝脈經中所述。";

        ob = find_object(MAIJING);
        if (! ob) ob = load_object(MAIJING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我那本王叔和脈經不就是你拿著在看嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…脈經現在不在我手裡。";

                if( query("family/family_name", owner) == "段氏皇族" )
                        return "那書現在暫時是你兄弟"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                        return "我那本脈經現在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 這本脈經你就拿去看吧，可要認真研讀。");
         command("give mai jing to "+query("id", me));
        return 1;
}

mixed ask_maijing2()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "段氏皇族" )
                return "你又不是我們段家的傳人，這話是什麼意思？";

        if( query("family/master_id", me) != query("id") )
                return "…嗯…等你成為我的弟子後再說吧。";

        if( query("shen", me)<80000 )
                return "你俠義正事做得不夠，這脈經我不能給你。";

        if( query("combat_exp", me)<300000 )
                return "你現在經驗太淺，不用忙著去閱讀脈經。";

        if (me->query_skill("jingluo-xue", 1) > 199)
                return "你對經絡學的了解已經很透徹，遠勝脈經中所述。";

        ob = find_object(MAIJING2);
        if (! ob) ob = load_object(MAIJING2);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我那本玉顴神脈經不就是你拿著在看嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…脈經現在不在我手裡。";

                if( query("family/family_name", owner) == "段氏皇族" )
                        return "那書現在暫時是你兄弟"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                        return "我那本脈經現在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 這本脈經你就拿去看吧，可要認真研讀。");
         command("give yuquan jing to "+query("id", me));
        return 1;
}
