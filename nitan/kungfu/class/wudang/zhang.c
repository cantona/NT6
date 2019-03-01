// This program is a part of NITAN MudLIB
// zhang.c 張三豐

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
// inherit F_NOCLONE;
inherit F_QUESTER;

#include <ansi.h>
#include "wudang.h"

#define CANPIAN         "/kungfu/class/wudang/obj/canpian"
// #define ZHENWU_SWORD    "/clone/unique/zhenwu_jian"
#define ZHENWU_SWORD    "/clone/lonely/zhenwu"

mixed ask_jian();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill10();
mixed ask_skill11();
mixed ask_skill12();
mixed ask_medicine();
mixed ask_to_learn_jy();
int try_to_learn_jy();


void create()
{
        object ob;
        set_name("張三豐", ({ "zhang sanfeng", "zhang" }));
        set("nickname", "邋遢真人");
        set("long",
                "這就是武當派開山鼻祖、當今武林的泰山北鬥張三豐真人。\n"
                "但見他身穿一襲污穢的灰布道袍，身形高大異常，須發如銀，\n"
                "臉上紅潤光滑，笑眯眯的甚是可親，此外也無特異情狀。\n");
        set("gender", "男性");
        set("age", 100);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 14123);
        set("max_jing", 3173);
        set("wudang_book", 1);
        set("eff_jingli", 9000);
        set("max_jingli", 9000);
        set("neili", 12000);
        set("max_neili", 12000);
        set("jiali", 300);
        set("combat_exp", 6500000);
        set("score", 650000);

        set_skill("array", 600);
        set_skill("zhenwu-jianzhen", 600);
        set_skill("force", 600);
        set_skill("taiji-shengong", 600);
        set_skill("wudang-jiuyang", 600);
        set_skill("yinyun-ziqi", 600);
        set_skill("dodge", 600);
        set_skill("tiyunzong", 600);
        set_skill("cuff", 600);
        set_skill("taiji-quan", 600);
        set_skill("strike", 600);
        set_skill("wudang-zhang", 600);
        set_skill("hand", 600);
        set_skill("paiyun-shou", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("wudang-jian", 600);
        set_skill("blade", 600);
        set_skill("taiji-dao", 600);
        set_skill("taiji-jian", 600);
        set_skill("taoism", 600);
        set_skill("literate", 600);
        set_skill("wudang-yaoli", 600);
        set_skill("medical", 600);
        set_skill("liandan-shu", 600);
        set_skill("martial-cognize", 600);
        set_skill("tianwei-zhengqi", 600);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("hand", "paiyun-shou");
        map_skill("strike", "wudang-zhang");
        map_skill("blade", "taiji-dao");

        prepare_skill("cuff", "taiji-quan");

        create_family("武當派", 1, "開山祖師");
        set("class", "taoist");

        set("inquiry", ([
                "真武劍"     : (: ask_jian : ),
                "鶴嘴勁"     : (: ask_skill1 :),
                "震字訣"     : (: ask_skill2 :),
                "引字訣"     : (: ask_skill3 :),
                "擠字訣"     : (: ask_skill4 :),
                "粘字訣"     : (: ask_skill5 :),
                "太極圖"     : (: ask_skill6 :),
                "纏字訣"     : (: ask_skill7 :),
                "隨字訣"     : (: ask_skill8 :),
                "駕字訣"     : (: ask_skill9 :),
                "劍輪嵐轉"   : (: ask_skill10 :),
                "真武除邪"   : (: ask_skill11 :),
                "太極劍意"   : (: ask_skill12 :),
                "煉丹術"     : (: ask_medicine :),
                "制藥"       : (: ask_medicine :),
                "武當九陽"   : (: ask_to_learn_jy :),
                "三黃寶臘丹" : "等你學好了煉丹術，以後自己制吧。",
                "玉清散"     : "嗯...等你通曉了煉丹術的奧妙，自己慢慢制吧。",
                "繞指柔劍"   : "唉，你去問問你莫師兄把......",
        ]));

        set("no_teach", ([
                   "wudang-jiuyang" : (: try_to_learn_jy() :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.jia" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "sword.zhuan" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "cuff.tu" :),
                (: perform_action, "cuff.zhen" :),
                (: perform_action, "cuff.zhan" :),
                (: perform_action, "cuff.ji" :),
                (: perform_action, "cuff.yin" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set("master_ob", 5);
        setup();
        if (clonep())
        {
                ob = find_object(ZHENWU_SWORD);
                if (! ob) ob = load_object(ZHENWU_SWORD);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        carry_object("/d/wudang/obj/greyrobe")->wear();

        set("startroom", "/d/wudang/xiaoyuan");
        // check_clone();
}

void scan()
{
        ::scan();

        if (! query_temp("weapon"))
                map_skill("parry", "taiji-quan");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("yinyun-ziqi", 1) < 120)
        {
                command("say 我武當派乃內家武功，最重視內功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否還應該在氤氳紫氣上多下點功夫？");
                return;
        }

        if( query("shen", ob)<80000 )
        {
                command("say 學武之人，德義為先，功夫的高低倒還在其次，未練武，要先學做人。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if (ob->query_skill("taoism", 1) < 120)
        {
                command("say 我武當派武功全從道藏悟出。");
                command("say 你對道家心法的領悟還不夠。");
                command("say " + RANK_D->query_respect(ob) + "還是多研究研究道學心法吧。");
                return;
        }

        if (ob->query_int() < 32)
        {
                command("say 我武當派武功極需靠自己領悟。");
                command("say 要能達到爐火純青之境，體質什麼的倒是無關緊要，悟性卻是半點也馬虎不得。");
                command("say " + RANK_D->query_respect(ob) + "的悟性還大有潛力可挖，還是請回吧。");
                return;
        }

        command("smile");
        command("say 想不到老道在垂死之年，又覓得一個可塑之才，真是可喜可賀。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-shengong/dian", me) )
                return "我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-shengong", 1) < 1)
                return "你連太極神功都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<800 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<150000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-shengong", 1) < 100)
                return "你的太極神功修為太淺，修煉好了再來吧。";

        if( query("max_neili", me)<1500 )
                return "你的內力修為太淺，修煉高了再來吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，伸出一指，出手如風，陡然"
                     "點在$N" HIY "耳緣三分處，$N" HIY "頓時只覺$n" HIY
                     "內力的源源不絕，澎湃湧入，全身一陣酸麻，不禁大驚"
                     "失色。\n\n" NOR, me, this_object());

        command("say 你懂了嗎？");
        tell_object(me, HIC "你學會了「鶴嘴勁點龍躍竅」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("taiji-shengong"))
                me->improve_skill("taiji-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-shengong/dian", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/zhen", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你連太極拳都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<100000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太極拳修為太淺，修煉好了再來吧。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為太淺，修煉高了再來吧。";

        message_sort(HIY "\n$n" HIY"當不答話，緩緩站起身來，兩臂慢慢提"
                     "起至胸前，左臂半環，掌面對成陰掌，右掌翻過成陽掌"
                     "，至攬雀尾、單鞭、提手上勢、如封似閉、十字手、抱"
                     "虎歸山……一招一式演了下去。當$n" HIY "使到上步高"
                     "探馬，上步攬雀尾，單鞭而合太極，神定氣閒的站在當"
                     "地。最後$n" HIY "雙手合抱太極圈，這才向$N" HIY
                     "問道：“這套拳術中「虛靈頂勁、涵胸拔背、鬆腰垂臀"
                     "、沉肩墜肘」的訣竅，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 純以意行，最忌用力，形神合一，是這路拳法的要旨。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「震字訣」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/zhen", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/yin", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你連太極拳都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<100000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太極拳修為太淺，修煉好了再來吧。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為太淺，修煉高了再來吧。";

        message_sort(HIY "\n$n" HIY"當不答話，緩緩站起身來，兩臂慢慢提"
                     "起至胸前，左臂半環，掌面對成陰掌，右掌翻過成陽掌"
                     "，至攬雀尾、單鞭、提手上勢、如封似閉、十字手、抱"
                     "虎歸山……一招一式演了下去。當$n" HIY "使到上步高"
                     "探馬，上步攬雀尾，單鞭而合太極，神定氣閒的站在當"
                     "地。最後$n" HIY "雙手合抱太極圈，這才向$N" HIY
                     "問道：“這套拳術中「虛靈頂勁、涵胸拔背、鬆腰垂臀"
                     "、沉肩墜肘」的訣竅，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 用意不用力，太極圓轉，無使自斷絕。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「引字訣」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/yin", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/ji", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你連太極拳都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<120000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太極拳修為太淺，修煉好了再來吧。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為太淺，修煉高了再來吧。";

        message_sort(HIY "\n$n" HIY"當不答話，緩緩站起身來，兩臂慢慢提"
                     "起至胸前，左臂半環，掌面對成陰掌，右掌翻過成陽掌"
                     "，至攬雀尾、單鞭、提手上勢、如封似閉、十字手、抱"
                     "虎歸山……一招一式演了下去。當$n" HIY "使到上步高"
                     "探馬，上步攬雀尾，單鞭而合太極，神定氣閒的站在當"
                     "地。最後$n" HIY "雙手合抱太極圈，這才向$N" HIY
                     "問道：“這套拳術中「虛靈頂勁、涵胸拔背、鬆腰垂臀"
                     "、沉肩墜肘」的訣竅，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 當牢記借力而生，著力而發，反施其身。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「擠字訣」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/ji", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/zhan", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你連太極拳都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<500 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<140000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太極拳修為太淺，修煉好了再來吧。";

        if( query("max_neili", me)<1200 )
                return "你的內力修為太淺，修煉高了再來吧。";

        message_sort(HIY "\n$n" HIY"當不答話，緩緩站起身來，兩臂慢慢提"
                     "起至胸前，左臂半環，掌面對成陰掌，右掌翻過成陽掌"
                     "，至攬雀尾、單鞭、提手上勢、如封似閉、十字手、抱"
                     "虎歸山……一招一式演了下去。當$n" HIY "使到上步高"
                     "探馬，上步攬雀尾，單鞭而合太極，神定氣閒的站在當"
                     "地。最後$n" HIY "雙手合抱太極圈，這才向$N" HIY
                     "問道：“這套拳術中「虛靈頂勁、涵胸拔背、鬆腰垂臀"
                     "、沉肩墜肘」的訣竅，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 你只需懂得太極圖圓轉不斷、陰陽變化之意即可。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「粘字訣」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        set("can_perform/taiji-quan/zhan", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/tu", me) >= 10 )
                return "該學的你都已經學了，以後要善加利用！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你連太極拳都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<3000 )
                return "你為我武當派效力還不夠，這招我不忙傳你。";

        if( query("shen", me)<250000 )
                return "你行俠仗義的事情做得還不夠多，我不能放心傳你絕招！";

        if (me->query_skill("taiji-quan", 1) < 250)
                return "你的太極拳法還不到家，要多練練！";

        if (me->query_skill("taiji-shengong", 1) < 300)
                return "你的太極神功還不到家，好好修行吧！";

        if (me->query_skill("taoism", 1) < 300)
                return "你的道學心法研究的還不夠明白，要下功夫苦學才是！";

        if( query("max_jingli", me)<1000 )
                return "你的精力不濟，就算傳給你太極圖你也難以運用。";

        message_sort(HIY "\n$n" HIY "點點頭，雙手輕輕劃了一個圈子，地上"
                     "土霧無端吸起，又漸漸落下。\n" NOR, me,
                     this_object());

        command("say 你看懂了多少？");

        if( query("potential", me)<query("learned_points", me)+100 )
        {
                tell_object(me, "你看了半天，沒有研究出什麼新"
                      "的東西，看來是潛能還不夠！\n");
                return 1;
        }

        addn("learned_points", 100, me);

        if( addn("can_perform/taiji-quan/tu", 1, me)<10 )
        {
                message_vision(HIY "$N" HIY "迷迷茫茫的點了"
                               "點頭，深思良久。\n\n" NOR, me);
                tell_object(me, HIC "你對太極圖有了一點領悟。\n" NOR);
        } else
        {
                message_sort(HIY "$N" HIY "臉露笑容，喜道：我已經明白了"
                             "，所謂真與幻象其實並無分別啊！$n" HIY "哈"
                             "哈長笑道：明白就好，明白就好，以後勿得輕易"
                             "使用，你去吧。\n\n", me, this_object());

                tell_object(me, HIC "你學會了道家密技「太極圖」。\n" NOR);
                if (me->can_improve_skill("taoism"))
                        me->improve_skill("taoism", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("taiji-shengong"))
                        me->improve_skill("taiji-shengong", 1500000);
                if (me->can_improve_skill("cuff"))
                        me->improve_skill("cuff", 1500000);
                if (me->can_improve_skill("taiji-quan"))
                        me->improve_skill("taiji-quan", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                addn("family/gongji", -3000, me);
                set("can_perform/taiji-quan/tu", 10, me);
        }
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/chan", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<80000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-jian", 1) < 80)
                return "你的太極劍法還不到家，要多練練！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作劍，開"
                     "始慢慢的演示劍招。從起手勢一直到五十三式「指南針」"
                     "，雙手同時畫圓，復成第五十四式「持劍歸原」。直待一"
                     "套劍法演示完畢，$n" HIY "這才向$N" HIY "問到：“這"
                     "太極劍招中的劍意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 你只需記住劍意無定，綿綿不絕便成。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「纏字訣」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/chan", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/sui", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<80000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-jian", 1) < 60)
                return "你的太極劍法還不到家，要多練練！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作劍，開"
                     "始慢慢的演示劍招。從起手勢一直到五十三式「指南針」"
                     "，雙手同時畫圓，復成第五十四式「持劍歸原」。直待一"
                     "套劍法演示完畢，$n" HIY "這才向$N" HIY "問到：“這"
                     "太極劍招中的劍意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 講究從心而發，從心而收，便能圓轉如意。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「隨字訣」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/sui", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/jia", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<600 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<100000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-jian", 1) < 150)
                return "你的太極劍法還不到家，要多練練！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作劍，開"
                     "始慢慢的演示劍招。從起手勢一直到五十三式「指南針」"
                     "，雙手同時畫圓，復成第五十四式「持劍歸原」。直待一"
                     "套劍法演示完畢，$n" HIY "這才向$N" HIY "問到：“這"
                     "太極劍招中的劍意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 借力打力，四兩撥千斤，是之為太極。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「駕字訣」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/jia", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/zhuan", me) )
                return "你自己慢慢體會吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<800 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<120000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-jian", 1) < 160)
                return "你的太極劍法還不到家，要多練練！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作劍，開"
                     "始慢慢的演示劍招。從起手勢一直到五十三式「指南針」"
                     "，雙手同時畫圓，復成第五十四式「持劍歸原」。"
                     "太極劍招中的劍意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 心無拘囿，以意馭劍。");
        command("say 道理便是如此，下去後慢慢體會吧。");
        tell_object(me, HIC "你學會了「劍輪嵐轉」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/zhuan", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill11()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/zhenwu", me) )
        return "自己好好多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<2000 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<120000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("taiji-jian", 1) < 180)
                return "你的太極劍法還不到家，要多練練！";

        message_sort(HIY "\n$n" HIY "微微頷首，隨手揀起一根樹枝向$N" HIY
                     HIY "掃來，$N" HIY "見來招平淡無奇，心中頗為疑惑，"
                     "只是隨手一擋。忽然只見$n" HIY "劍勢大變，氣度非凡"
                     "，變化無窮，$N" HIY "大吃一驚，慌亂不迭。\n\n" NOR,
                     me, this_object());

        command("say 你可明白了？");
        tell_object(me, HIC "你學會了「真武除邪」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/zhenwu", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill12()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/jian", me) )
                return "自己好好多練習吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if( !query("reborn/times", me) )
                return notify_fail("你還沒有經歷轉世重生的考驗，無法領悟此招真諦。\n");
                
        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<5000 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。（需要5000點門派貢獻）";

        if( query("shen", me)<500000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！（需要正氣50萬）";

        if (me->query_skill("taiji-jian", 1) < 1000)
                return "你的太極劍法還不到家，要多練練！";

        if (me->query_skill("tianwei-zhengqi", 1) < 200)
                return "你的門派技能天威正氣還沒有修煉到家，要多練練！";
        
        message_sort(HIY "\n$n" HIY "身形一轉，手中之劍輕靈而出，猶如碧波盪漾，蜿蜒"
                              "而出，形態飄逸瀟洒之極，頗具$HIG$太□$HIY$之意……\n\n$N" 
                              HIY "接著道：這招的關鍵就是要領悟太極真意，從而將太極劍"
                              "威力發揮到極至。\n\n" NOR, me, this_object());

        command("haha");
        command("say 你可明白了？");        
        tell_object(me, HIC "你學會了「太□□意」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        if (me->can_improve_skill("martial-cognize"))             
                me->improve_skill("martial-cognize", 1500000);
                
        set("can_perform/taiji-jian/jian", 1, me);
        addn("family/gongji", -5000, me);

        return 1;
}

mixed ask_jian()
{
        int cost;
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "武當派" )
                        message_vision(CYN "$N" CYN "大怒，對$n" CYN "道：“你身為武當弟子，"
                                       "反而誤入魔道，還不快快醒轉？”\n" NOR,
                                       this_object(), me);
                else
                message_vision(CYN "$N" CYN "大怒，對$n" CYN "喝道：“好一個邪魔外"
                               "道，居然敢窺測真武劍？”\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "武當派" )
                return "真武劍是我們武當鎮派之寶，你打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用真武劍，你還是請回吧。";

        if( query("shen", me)<60000 )
                return "你行俠仗義的事情做得不夠，我不能把真武劍交給你。";

        if( query("family/first", me) ) cost = 250;
        else cost = 500;
        if( query("family/gongji", me) < cost )
                return "你為我武當派效力還不夠，等你擁有足夠的師門功績再來兌換真武劍使用時間吧。";

        ob = find_object(ZHENWU_SWORD);
        if (! ob) ob = load_object(ZHENWU_SWORD);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "真武劍不是在你的手中麼，怎麼反而來找我呢？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "我已經把真武劍已經借出去了。";

                if( query("family/master_id", owner) == query("id") )
                        return "真武劍現在在"+query("name", owner)+
                               "手中，你要想用就去找他吧。";
                else
                        return "真武劍現在落在"+query("name", owner)+
                               "手中，你去把他找回來吧。";
        }

        ob->move(this_object());
        ob->start_borrowing();
        message_vision(CYN "$N" CYN "點點頭道：“好，你用這真武劍要多作一些行"
                       "俠仗義的事情！”\n" NOR, this_object(), me);
        command("give zhenwu jian to "+query("id", me)); 
        addn("family/gongji", -cost, me);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != ZHENWU_SWORD)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多謝這位" + RANK_D->query_respect(me) + "將真武劍交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

mixed ask_medicine()
{
        object me;
        object ob;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
        {
                command("say 你是什麼人，打聽我的醫書有何目的？");
                return 1;
        }

        if ((int)me->query_skill("liandan-shu", 1) < 100)
        {
                command("say 你對煉丹術的了解太淺，等你學得再"
                        "好一些我才能把秘本傳與你。");
                return 1;
        }

        if (query("wudang_book") < 1)
        {
                command("say 真是可惜，你來晚了，書我已經借出去了。");
                return 1;
        }

        addn("wudang_book", -1);
        ob = new("/clone/book/wudang");
        message_vision("$n翻出一本泛黃的薄冊子遞給$N，叮囑"
                       "道：“唔，就是這本，好好看。”\n",
                       me, this_object());
        ob->move(me, 1);
        return 1;
}

/*
mixed ask_to_learn_jy()
{
        object *obs, obj, player = this_player();

        if( query("family/master_id", player) != "zhangsanfeng" )
        {
                return "太極神功是我武當派鎮派之寶。\n";
        }
        switch (random(10))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
                return "先師覺遠大師傳授經文，我所學不全，至今雖閉關數次，"+
                       "苦苦鑽研，仍只能想通得三四成。\n";
        case 5:
        case 6:
        case 7:
        case 8:
                return "先師覺遠大師學得《九陽真經》，圓寂之前背誦經文，郭襄女俠、"+
                       "少林派無色大師和我三人各自記得一部分，\n" +
                       "因而武當、峨嵋、少林三派武功大進，數十年來分庭抗禮，名震武林。\n";
        case 9:
                if (player->query_skill("taiji-shengong", 1) < 200)
                {
                        return "你的功力尚淺，好好學全了武當太極功再說吧。\n";
                }

                obj = 0;
                obs = filter_array(children(CANPIAN), (: clonep :));
                if (sizeof(obs) > 0) obj = obs[0];

                if (objectp(obj) && objectp(environment(obj)) &&
                    userp(environment(obj)))
                {
                        return "九陽神功殘篇被你師兄弟借走了，你去問他們吧\n";
                }
                if (! objectp(obj)) obj = new(CANPIAN);
                obj->move(player);
                message_vision("$N給$n一部九陽神功殘篇。\n", this_object(), player);
                command("rumor"+query("name", this_player())+"弄到了一部"NOR+YEL"九陽神功殘篇"HIM"。"NOR);
                return "我將心中記得的一些九陽神功筆錄在此，\n"+
                       "你可找一位少林派高手與之共同參悟(canwu)，也好讓這功夫不至于失傳。\n";
        }
        return 0;
}
*/

mixed ask_to_learn_jy()
{
        object ob;
        object me;
        me = this_player();

        if( query("can_learn/jiuyang-shengong/wudang", me) )
                return "老道已經答應傳授你武當九陽功了，你怎麼還那麼羅嗦？";

        if( !query("can_learn/jiuyang-shengong/kunlun", me) )
                return "昔日《九陽真經》在我師父覺遠大師手中丟失，現在也不知道流落何方。";

        if( !query("can_learn/jiuyang-shengong/shaolin", me) )
                return "唉，如果當時能夠追回《九陽真經》，覺遠大師也不至于落難。";

        message_vision(CYN "\n張三豐仔細打量了$N" CYN "好一陣，目光陡然一亮。\n\n" NOR, me);

        command("say 你不就是當年還送經書予覺遠大師之人嗎？");
        command("say 所謂‘大恩不言謝’，這九陽神功老道倒是通曉一點，現已化為武當九陽功。");
        command("say 如果閣下不嫌棄，老道倒是可以將這套九陽功傳授于你。");

        tell_object(me, HIC "張三豐同意傳授你「武當九陽功」。\n" NOR);

        if (me->can_improve_skill("martial-cognize"))
                improve_skill("martial-cognize", 1500000);

        set("can_learn/jiuyang-shengong/wudang", 1, me);
        return 1;
}

int try_to_learn_jy()
{
        object me = this_player();

        if( !query("can_learn/jiuyang-shengong/wudang", me) )
        {
                if( query("family/master_id", me) != query("id") )
                {
                        command("say 武當九陽神功乃是九陽神功的分支，我少"
                                "年時得師父覺遠大師所授。");
                        command("say 但閣下與貧道素不相識，怎談得上“指點"
                                "”二字？");
                        return -1;
                } else
                {
                        command("say 武當九陽神功乃是九陽神功的分支，我少"
                                "年時得師父覺遠大師所授。");
                        command("say 雖然這武功在我手裡有所改動，但它還是"
                                "少林的武功，就算是我的弟子也不傳授。");
                        return -1;
                }
        }

        if (me->query_skill("wudang-jiuyang") > 400)
        {
                command("say 你的武當九陽功力已頗為深厚了，以後你就自己研究吧。");
                return -1;
        }

        if( query("shen", me)<0 )
        {
                command("say 老道倒是有心傳你九陽功，可是你中邪魔外道如此之深。");
                command("say 等你改過自新後再來找老道我吧。");
                return -1;
        }
        return 0;
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/jiuyang-shengong/wudang", me) )
        {
                if( query("family/master_id", me) != query("id") )
                {
                        command("say 武當九陽神功乃是九陽神功的分支，我少"
                                "年時得師父覺遠大師所授。");
                        command("say 但閣下與貧道素不相識，怎談得上“指點"
                                "”二字？");
                        return -1;
                } else
                {
                        command("say 武當九陽神功乃是九陽神功的分支，我少"
                                "年時得師父覺遠大師所授。");
                        command("say 雖然這武功在我手裡有所改動，但它還是"
                                "少林的武功，就算是我的弟子也不傳授。");
                        return -1;
                }
        }

        if (skill != "wudang-jiuyang")
        {
                command("say 武學雜而不精也是無用，你還是專心學習武當九陽功吧。");
                return -1;
        }
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

        case "縱字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tiyunzong/zong",
                           "name"    : "縱字訣",
                           "sk1"     : "tiyunzong",
                           "lv1"     : 150,
                           "sk2"     : "dodge",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 24000, ]));
                break;

        case "連字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-jian/lian",
                           "name"    : "連字訣",
                           "sk1"     : "taiji-jian",
                           "lv1"     : 120,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 120,
                           "gongxian": 800,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;
        case "按字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-quan/an",
                           "name"    : "按字訣",
                           "sk1"     : "taiji-quan",
                           "lv1"     : 200,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 200,
                           "gongxian": 800,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;

/*
        case "太極劍意" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-jian/jian",
                           "name"    : "太極劍意",
                           "sk1"     : "taiji-jian",
                           "lv1"     : 1000,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 1000,
                           "gongxian": 3000,
                           "neili"   : 2000,
                           "reborn"  : 1,
                           "shen"    : 28000, ]));
                break;
*/

        default:
                return 0;
        }
}
