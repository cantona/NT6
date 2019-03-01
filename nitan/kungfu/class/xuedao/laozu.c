// This program is a part of NT MudLIB

#include <ansi.h>
#include "xuedao.h"

//#define XUEDAO    "/clone/unique/xuedao"
#define XUEDAO    "/clone/lonely/xhsblade"
#define JING      "/clone/book/xuedao-book"

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
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();

mixed ask_dao();
mixed ask_book();
mixed ask_midao();

void create()
{
        object ob;
        set_name("血刀老祖", ({ "xuedao laozu", "xuedao", "laozu", "xue", "lao" }));
        set("long", @LONG
這喇嘛身著黃袍，年紀極老，尖頭削耳，臉上都是
皺紋。他就是血刀門第四代掌門。
LONG);
        set("gender", "男性");
        set("age", 85);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 33);
        set("int", 31);
        set("con", 35);
        set("dex", 32);
        set("max_qi", 5500);
        set("max_jing", 4000);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 3500000);

        set_skill("force", 600);
        set_skill("mizong-neigong", 600);
        set_skill("xuehai-mogong", 600);
        set_skill("blade", 600);
        set_skill("xuedao-daofa", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("dodge", 600);
        set_skill("shenkong-xing", 600);
        set_skill("hand", 600);
        set_skill("dashou-yin", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("lamaism", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
/*
        set_skill("force", 480);
        set_skill("mizong-neigong", 480);
        set_skill("xuehai-mogong", 480);
        set_skill("blade", 480);
        set_skill("xuedao-daofa", 460);
        set_skill("sword", 440);
        set_skill("mingwang-jian", 440);
        set_skill("dodge", 460);
        set_skill("shenkong-xing", 460);
        set_skill("hand", 460);
        set_skill("dashou-yin", 460);
        set_skill("cuff", 460);
        set_skill("yujiamu-quan", 460);
        set_skill("parry", 460);
        set_skill("lamaism", 440);
        set_skill("literate", 460);
        set_skill("martial-cognize", 300);
*/

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ying" :),
                (: perform_action, "blade.chi" :),
                (: perform_action, "blade.xue" :),
                (: perform_action, "blade.shi" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
                (: exert_function, "resurrect" :),
                (: exert_function, "powerup" :),

        }) );

        create_family("血刀門", 4, "掌門");
        set("class", "bonze");

        set("inquiry", ([
                "血刀"      : (: ask_dao :),
                "血刀經"    : (: ask_book :),
                "密道"      : (: ask_midao :),
                "秘道"      : (: ask_midao :),
                // "浴血重生"  : (: ask_skill1 :),
                "金剛印"    : (: ask_skill2 :),
                "修羅降世"  : (: ask_skill3 :),
                "若悲"      : (: ask_skill4 :),
                "降魔"      : (: ask_skill5 :),
                "無影神刀"  : (: ask_skill6 :),
                "赤煉神刀"  : (: ask_skill7 :),
                "祭血神刀"  : (: ask_skill8 :),
                "噬血穹蒼"  : (: ask_skill9 :),
                // "冰河開封"  : "這一招你去讓勝諦教你好了。",
                // "流星火雨"  : "這一招你去讓寶象教你好了。",
                "血海無邊"  : "操！老子讓你去跟鐵匠接口，你來問我幹嘛？",
        ]));

        set("master_ob", 5);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        if (clonep())
        {
                ob = find_object(XUEDAO);
                if (! ob) ob = load_object(XUEDAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("clone/weapon/jiedao");
                        ob->move(this_object());
                        ob->wield();
                }
        }

        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        add_money("silver", 20);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) == "女性" )
        {
                command("say 老夫不收女徒弟，不過可以陪你玩玩。\n");
                return;
        }

        if( query("gender", ob) != "男性" )
        {
                command("say 我平身最看不慣的就是閹人，再不滾開我殺了你！\n");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                set_temp("pending/join_bonze", 1, ob);
                command("say 你不是出家人，我們血刀門是不會收留的。"
                        "如果你要出家，去找善勇。");
                return;
        }

        if( query("combat_exp", ob)<350000 )
        {
                command("say 你的實戰經驗也忒差了，回去好好給我練功去！");
                return;
        }

        if( query("shen", ob)>-50000 )
        {
                command("say 你是不是向著俠義道，連殺人都不會！\n");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 140)
        {
                command("say 雖說咋們平時燒殺搶掠，但總歸也算是佛門弟子。\n");
                command("say 待你的密宗佛法提高後再來找我吧。\n");
                return;
        }

        if ((int)ob->query_skill("mizong-neigong", 1) < 100 &&
            (int)ob->query_skill("xuehai-mogong", 1) < 100)
        {
                command("say 你這個廢物！怎麼練的？內功這麼差！\n");
                return;
        }

        if ((int)ob->query_skill("blade", 1) < 120)
        {
                command("say 你刀法這麼差，還有臉來見我？\n");
                return;
        }

        command("sneer");
        command("say 那你以後就跟著老夫好了。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/resurrect", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "你連血刀大法都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<500 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-60000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if( query("max_neili", me)<1000 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("xuedao-daofa", 1) < 120)
                return "等你把血刀大法練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "微微一笑，當下也不答話，只是伸出右手，輕輕放"
                       "在\n$N" HIY "胸口。正當$N" HIY "疑惑間，卻見$n" HIY "掌勁"
                       "輕吐，$N" HIY "頓時全身\n一震，如遭電擊，各處經脈無不舒暢"
                       "，說不出的受用。\n" NOR, me, this_object());

        command("sneer");
        command("say 明白了麼？");
        tell_object(me, HIC "你學會了「浴血重生」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/resurrect", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/dashou-yin/yin", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("dashou-yin", 1) < 1)
                return "你連大手印都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<200 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-15000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 140)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<1000 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("dashou-yin", 1) < 100)
                return "等你把大手印練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "冷笑一聲，上下打量了$N" HIY "一番，點了點頭"
                       "。當下凝神\n沉履，面容莊重，雙手攜著勁風奮力向$N" HIY "面前"
                       "的一座舍利佛塔\n拍落，頓時只聽轟然一聲悶響，佛塔內的香灰"
                       "被$n" HIY "的掌\n力激盪得四處飛揚，塵煙彌漫，待得煙消雲散"
                       "後，$N" HIY "這才發現\n那座舍利佛塔上豁然嵌著一雙掌印。\n"
                       NOR, me, this_object());

        command("nod");
        command("say 只要內功精純，這招並不難練。");
        tell_object(me, HIC "你學會了「金剛印」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("dashou-yin"))
                me->improve_skill("dashou-yin", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dashou-yin/yin", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/yujiamu-quan/jiang", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("yujiamu-quan", 1) < 1)
                return "你連金剛瑜迦母拳都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<300 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-18000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 150)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<1200 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("yujiamu-quan", 1) < 100)
                return "等你把金剛瑜迦母拳練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "略微點了點頭，深深呼入一口氣，縱步上前，嗔目"
                       "大\n喝，拳招迭出，疾如奔雷，霎時已向$N" HIY "攻出數拳，招"
                       "式甚為精\n妙。實乃$N" HIY "前所未聞。\n" NOR, me,
                       this_object());;

        command("haha");
        command("say 看清楚了？");
        tell_object(me, HIC "你學會了「修羅降世」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("yujiamu-quan"))
                me->improve_skill("yujiamu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yujiamu-quan/jiang", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/ruo", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "你連不動明王劍都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<100 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-10000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 140)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<1200 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("mingwang-jian", 1) < 100)
                return "等你把不動明王劍練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "冷笑一聲，也不答話，從$N" HIY "手中接過長劍"
                       "，手腕輕輕\n一抖，長劍頓時發出一陣低沉的輕鳴，鳴音入耳，"
                       "$N" HIY "只感到心\n頭一震，竟湧上一股莫名的悲哀。\n" NOR,
                       me, this_object());

        command("haha");
        command("say 道理很簡單，你自己下去練吧。");
        tell_object(me, HIC "你學會了「若悲」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/ruo", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/xiang", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "你連不動明王劍都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<400 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-15000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 180)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<1600 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("mingwang-jian", 1) < 140)
                return "等你把不動明王劍練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "對$N" HIY "微微一笑，隨即伸出右手，中食二指"
                       "並攏，捏作\n劍訣，“嗤”的一聲空點而出，霎時破空之聲驟響"
                       "，一股氣勁\n從指尖迸發，將$N" HIY "所穿戴的僧袍刺透出一個"
                       "小孔。\n" NOR, me, this_object());

        command("sneer");
        command("say 此招不外乎是以劍作媒，以氣傷人。");
        tell_object(me, HIC "你學會了「降魔」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/xiang", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/ying", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "你連血刀大法都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<300 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-60000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 160)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<1500 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("xuedao-daofa", 1) < 120)
                return "等你把血刀大法練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "獰笑一聲，對$N" HIY "說道：“乖徒兒，老夫這"
                       "就給你演示\n一遍，看好了！”$n" HIY "說完便抽出腰間血刀，"
                       "陡然一聲大\n喝，將手中的血刀舞動如輪，頓時刀鋒激起層層血"
                       "浪逼向$N" HIY "而\n去，直將看得$N" HIY "目瞪口呆。\n" NOR,
                       me, this_object());

        command("haha");
        command("say 這招的要訣就是一個快字，看懂了麼？");
        tell_object(me, HIC "你學會了「無影神刀」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/ying", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/chi", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "你連血刀大法都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<800 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-70000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 220)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<2400 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("xuedao-daofa", 1) < 160)
                return "等你把血刀大法練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "嘿嘿一笑，伸手將$N" HIY "招到身前，低聲在$N"
                       HIY "耳旁嘀咕了\n半天。隨後$n" HIY "又拔出腰間的血刀揮舞數"
                       "下，似乎是一種\n頗為詭異的刀訣。\n" NOR, me, this_object());

        command("haha");
        command("say 精要我都告訴你了，自己下去練吧。");
        tell_object(me, HIC "你學會了「赤煉神刀」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/chi", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/xue", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "你連血刀大法都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<1000 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-80000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 220)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<2400 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("xuedao-daofa", 1) < 160)
                return "等你把血刀大法練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，獰笑一聲，點了點頭。便伸手將"
                       "$N" HIY "招到身\n前，低聲在$N" HIY "耳旁嘀咕了半天。$N" HIY
                       "聽後臉色大變，似乎聽到了\n什麼劾人聽聞的事情，待$n" HIY "繼"
                       "續講解了一陣，$N" HIY "的表情\n才慢慢鬆弛了下來，隨即會心地"
                       "一笑，看來有所領悟。\n" NOR, me, this_object());

        command("grin");
        command("say 這招的要領就是義無返顧，拼死一攻，記住了嗎？");
        tell_object(me, HIC "你學會了「祭血神刀」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/xue", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/shi", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什麼人？我看你怎麼不象是我血刀門的弟子呢？";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "你連血刀大法都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<2000 )
                return "你幫老夫多做點事，老夫自然會傳你絕技。";

        if( query("shen", me)>-100000 )
                return "你這人是怎麼做的？連殺人都不會了？";

        if (me->query_skill("force") < 250)
                return "你的內功修為實在太差，修煉高了再來找老夫吧。";

        if( query("max_neili", me)<2600 )
                return "你的內力差成這樣，居然還好意思來找老夫？";

        if (me->query_skill("xuedao-daofa", 1) < 180)
                return "等你把血刀大法練熟了再來找老夫。";

        message_vision(HIY "$n" HIY "望著$N" HIY "幹笑了數聲，說道：“想不到居然那麼"
                       "快就有\n人能夠繼承我這一招，我血刀門真是後繼有人啊。今日我便"
                       "傳\n你這式「噬血穹蒼」絕技。”話音剛落，隨即只見$n" HIY "仰\n"
                       "天一聲狂哮，手中血刀一振，頓時迸發出漫天血光，騰起無邊\n殺意"
                       "。快刀連閃，赤芒暴展，竟似一個巨大的血球將$n" HIY "\n包裹在其"
                       "中，刀法之凌厲，實乃世所罕見。\n" NOR, me, this_object());

        command("haha");
        command("say 將赤煉、祭血兩招合一，便是新招。你自己下去練吧。");
        tell_object(me, HIC "你學會了「噬血穹蒼」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/shi", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_midao()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "血刀門" )
                return "你他奶奶的，嘀嘀咕咕到底要說什麼？";

        command("whisper"+query("id", me)+"你既然已經入我門來，以"
                "後若\n要去中原辦事，即可用我門血刀先輩們留下的密道，你"
                "可到山\n外雜物堆處進入(" NOR + HIY "enter mash" NOR + WHT
                ")，然後便能到達中原揚州。回來\n是找我血刀伏在中原的鐵匠"
                "，接口密語是" NOR + HIR "血海無邊" NOR + WHT "。\n");
        return "此秘密不可泄露于他人，否則天誅地滅！";
}

mixed ask_dao()
{
        object me;
        object ob;
        object owner;
int cost;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "血刀門" )
                        message_vision(CYN "$N" CYN "大怒，對$n" CYN "道：“你身"
                                       "為我血刀門弟子，反而學起假仁假義來了，居"
                                       "然還有臉問我要本門之寶？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "大怒，對$n" CYN "喝道：“你"
                                       "是什麼人？居然敢貪圖本門至寶，你再問看我"
                                       "不宰了你！”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "血刀門" )
                return "血刀是我血刀門至寶，你打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用血刀，你還是自己下去練練吧。";

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "你為我血刀門效力還不夠，等你擁有足夠的師門功績再來兌換血刀使用時間吧。";
        if( query("shen", me)>-50000 )
                return "你邪氣不重，使用不了血刀。";

        ob = find_object(XUEDAO);
        if (! ob) ob = load_object(XUEDAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "他奶奶的，本門的血刀現在不是你拿著在用嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，血刀現在不在我手中。";

                if( query("family/family_name", owner) == "血刀門" )
                        return "血刀現在暫時是你同門師兄"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "本門的血刀現在落在"+query("name", owner)+
                               "手中，你去把他做了，把血刀搶回來！";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "哈哈一笑，道：好，乖徒兒，這柄血刀你就"
                       "拿去，多殺幾個正派人士，揚揚咱們的威風！\n" NOR,
                       this_object(), me);
        command("give xuehun shendao to "+query("id", me));
addn("family/gongji", -cost, me); 
        ob->start_borrowing();
        return 1;
}

mixed ask_book()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "血刀門" )
                return "哪裡來的野種，竟敢打我血刀門的主意？";

        if( query("family/master_id", me) != query("id") )
                return "你又不是老夫的弟子，跟老夫羅嗦些什麼？";

        if( query("shen", me)>-50000 )
                return "你倒是學起假仁假義來了，讓老夫如何能相信你？";

        if( query("combat_exp", me)<300000 )
                return "你現在經驗太淺，這本血刀經你還看不懂。";

        if (me->query_skill("xuedao-daofa", 1) > 179)
                return "你的血刀大法火候已經很深了，血刀經對你起不了什麼作用。";

        ob = find_object(JING);
        if (! ob) ob = load_object(JING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我血刀門的寶經不就是你拿著在看嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…血刀經現在不在我手裡。";

                if( query("family/family_name", owner) == "血刀門" )
                        return "血刀經現在暫時被你同門的"+query("name", owner)+
                               "取去看了，你要看就去找他吧。";
                else
                        return "我血刀門的寶經現在落在了"+query("name", owner)+
                               "手中，你去把它奪回來吧！";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "點頭道：這本血刀經你就拿去看吧，可要仔細閱讀。\n" NOR,
                       this_object(), me);
        // command("give xuedao book to " + me->query("id"));
        ob->move(me, 1);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != XUEDAO)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 不錯，不錯！");
        else
                command("say 很好，很好！");
        destruct(ob);
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

        case "我必還之" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuedao-daofa/huan",
                           "name"    : "我必還之",
                           "sk1"     : "xuedao-daofa",
                           "lv1"     : 1000,
                           "sk2"     : "blade",
                           "lv2"     : 1000,
                           "reborn"  : 1, 
                           "gongxian": 8000, ]));
                break;
        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}
*/
