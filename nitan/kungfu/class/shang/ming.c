#include <ansi.h>
#include "shang.h"

#define BAGUADAO    "/clone/lonely/baguadao"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_dao();

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed give_letter();


void create()
{
        object ob;
        set_name("商劍鳴", ({"shang jianming", "shang", "jianming"}));
        set("gender", "男性");
        set("title", "商家堡堡主");
        set("nickname", YEL "八卦刀" NOR);
        set("age", 45);
        set("long", @LONG
這人身着長衫，身材高大魁梧，留着短鬚，神
情嚴肅，模樣甚為威嚴。他就是山東大豪、商
家堡的現任堡主「八卦刀」商劍鳴，相傳他刀
掌雙絕，武功了得，在江湖上罕逢敵手。
LONG);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 3300);
        set("max_jing", 3300);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 180);
        set("combat_exp", 3800000);
        set("score", 10000);

        set_skill("force", 240);
        set_skill("nei-bagua", 240);
        set_skill("shangjia-neigong", 220);
        set_skill("parry", 220);
        set_skill("wai-bagua", 220);
        set_skill("dodge", 200);
        set_skill("bagua-bu", 200);
        set_skill("unarmed", 200);
        set_skill("tan-tui", 200);
        set_skill("strike", 240);
        set_skill("bagua-zhang", 240);
        set_skill("bazhen-zhang", 220);
        set_skill("cuff", 200);
        set_skill("bagua-quan", 200);
        set_skill("baisheng-quan", 200);
        set_skill("sword", 200);
        set_skill("quemen-jian", 200);
        set_skill("blade", 240);
        set_skill("bagua-dao", 240);
        set_skill("shangjia-dao", 220);
        set_skill("throwing", 200);
        set_skill("jinbiao-jue", 200);
        set_skill("literate", 240);
        set_skill("martial-cognize", 220);

        map_skill("unarmed", "tan-tui");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "nei-bagua");
        map_skill("strike", "bagua-zhang");
        map_skill("sword", "quemen-jian");
        map_skill("blade", "bagua-dao");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "jinbiao-jue");

        prepare_skill("cuff", "bagua-quan");
        prepare_skill("strike", "bagua-zhang");

        set("class", "fighter");

        create_family("商家堡", 3, "堡主");

        set("inquiry", ([
                "紫金八卦刀" : (: ask_dao :),
                "八卦震"     : (: ask_skill1 :),
                "混沌初開"   : (: ask_skill2 :),
                "金蓮幻生"   : (: ask_skill3 :),
                "神卦天印"   : (: ask_skill4 :),
                "寒芒暴卷"   : (: ask_skill5 :),
                "劈天神芒"   : (: ask_skill6 :),
                "殺龍無悔"   : (: ask_skill7 :),
                "天刀八勢"   : (: give_letter :),
                "胡一刀"     : "哦？聽説此人刀法甚是了得，可惜我沒見過他。",
                "苗人鳳"     : "哼，這賊鳥廝居然敢號稱天下無敵，改天一定要去會會。"
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "blade.sha" :),
                (: perform_action, "strike.ding" :),
                (: perform_action, "cuff.gua" :),
                (: perform_action, "parry.zhen" :),
                (: perform_action, "throwing.huan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();
/*
        if (clonep())
        {
                ob = find_object(BAGUADAO);
                if (! ob) ob = load_object(BAGUADAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/gangdao");
                        ob->move(this_object());
                        ob->wield();
                }
        }
*/
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->name(1) == "商劍鳴")
        {
                command("say 他奶奶的，怎麼你也取這個名字？");
                return;
        }

        if (ob->name(1) == "商老太")
        {
                command("say 我操！你取這個名字是什麼意思？");
                return;
        }

        if (ob->name(1) == "商寶震")
        {
                command("say 你給俺換起一個別的名字不行？");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say 你現在江湖經驗太淺，還是先讓你娘教你吧。");
                return;
        }

        if( query("shen", ob)>-30000 )
        {
                command("sneer");
                command("say 你倒是學起假仁假義來了。");
                return;
        }

        if (ob->query_skill("shangjia-neigong", 1) < 100)
        {
                command("hmm");
                command("say 你連本門最基本的內功都沒修好，怎麼學習上乘武學。");
                return;
        }

        command("nod2");
        command("say 念在你如此有心，今日我便收你為徒。");
        command("say 日後俺這商家堡的立威揚名，就全靠你了。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "fighter" )
                set("class", "fighter", ob);
        return;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/wai-bagua/zhen", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("wai-bagua", 1) < 1)
                return "你連外八卦都沒學，談什麼絕招？";

        if( query("gongxian", me)<100 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-5000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("force") < 100)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("wai-bagua", 1) < 60)
                return "你的外八卦還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "微微一笑，當下也不答話，只是伸出右手，輕輕放"
                       "在\n$N" HIY "胸口。正當$N" HIY "疑惑間，卻見$n" HIY "掌勁"
                       "輕吐，$N" HIY "頓時全身\n一震，如遭電擊，各處經脈無不痠麻"
                       "，不禁大驚失色。\n" NOR, me, this_object());

        command("say 明白了麼？");
        tell_object(me, HIC "你學會了「八卦震」。\n" NOR);

        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/wai-bagua/zhen", 1, me);
        addn("gongxian", -100, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/baisheng-quan/kai", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("baisheng-quan", 1) < 1)
                return "你連百勝神拳都沒學，談什麼絕招？";

        if( query("gongxian", me)<300 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-20000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("force") < 140)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("baisheng-quan", 1) < 100)
                return "你的百勝神拳還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，沉聲道：“看好了！”隨即"
                       "便拉開架\n勢，演示拳招。霎時只見$n" HIY "身子驀的橫移，向左"
                       "轉成為\n弓箭步，兩臂向後成鈎手，“呼”的一聲倒揮出來，平舉"
                       "反\n擊向$N" HIY "而去，招數甚為精妙。\n" NOR, me,
                       this_object());

        command("sneer");
        command("say 馬老兒能夠創出這招，也算得上個人物。");
        command("say 這招並不複雜，稍加練習變成。");
        tell_object(me, HIC "你學會了「混沌初開」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("baisheng-quan"))
                me->improve_skill("baisheng-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/baisheng-quan/kai", 1, me);
        addn("gongxian", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/jinbiao-jue/huan", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("jinbiao-jue", 1) < 1)
                return "你連金鏢訣都沒學，談什麼絕招？";

        if( query("gongxian", me)<300 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-15000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("force") < 140)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("jinbiao-jue", 1) < 100)
                return "你的金鏢訣還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "將$N" HIY "招至跟前，輕聲在耳旁祕密説了些"
                       "什麼。隨後又\n伸出右手，十指箕張，一伸一縮，煞是巧妙。"
                       "看樣子是一種\n很特別的暗器法門。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 剛才我所説的你可都記牢了？剩下的就是靠自己多加練習。");
        tell_object(me, HIC "你學會了「金蓮幻生」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("jinbiao-jue"))
                me->improve_skill("jinbiao-jue", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinbiao-jue/huan", 1, me);
        addn("gongxian", -300, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/bazhen-zhang/yin", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("bazhen-zhang", 1) < 1)
                return "你連八陣八卦掌都沒學，談什麼絕招？";

        if( query("gongxian", me)<500 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-20000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("force") < 180)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("bazhen-zhang", 1) < 130)
                return "你的八陣八卦掌還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "笑了笑，對$N" HIY "點頭示意讚許，當下凝神沉"
                       "履，積聚全\n身功力於一掌，攜着雷霆之勢奮力向$N" HIY "面前"
                       "的一座青銅香爐\n拍落，頓時只聽轟然一聲悶響，香爐內的香灰"
                       "被$n" HIY "的掌\n力激盪得四處飛揚，塵煙瀰漫，待得煙消雲散"
                       "，$N" HIY "這才發現\n那座青銅香爐上豁然嵌着一雙掌印。\n"
                       NOR, me, this_object());
        command("ke");
        command("nod");
        command("say 這八陣八卦掌絕妙非凡，可要勤加練習。");
        tell_object(me, HIC "你學會了「神卦天印」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("bazhen-zhang"))
                me->improve_skill("bazhen-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bazhen-zhang/yin", 1, me);
        addn("gongxian", -500, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/shangjia-dao/juan", me) )
                return "我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("shangjia-dao", 1) < 1)
                return "你連商家刀法都沒學，談什麼絕招？";

        if( query("gongxian", me)<80 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-1000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("shangjia-dao", 1) < 50)
                return "你的商家刀法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 80)
                return "嗯，你的內功火候尚需提高，練好了再來找我吧。";

        message_vision(HIY "$n" HIY "笑了笑，伸手將$N" HIY "招到身前，低聲在$N" HIY
                       "耳旁嘀咕了半\n天。然後又拔出腰刀翻轉數下，斜撩而出。似乎是"
                       "一種頗為\n獨特的刀訣。\n" NOR, me, this_object());
        command("nod");
        command("say 這招很簡單，稍加練習便行。");
        tell_object(me, HIC "你學會了「寒芒暴卷」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("shangjia-dao"))
                me->improve_skill("shangjia-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shangjia-dao/juan", 1, me);
        addn("gongxian", -80, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-dao/mang", me) )
                return "我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("bagua-dao", 1) < 1)
                return "你連八卦刀法都沒學，談什麼絕招？";

        if (me->query_skill("wai-bagua", 1) < 1)
                return "你連外八卦神功都沒學，談什麼絕招？";

        if( query("gongxian", me)<1000 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-50000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("bagua-dao", 1) < 140)
                return "你的八卦刀法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("wai-bagua", 1) < 140)
                return "你的外八卦神功還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 200)
                return "嗯，你的內功火候尚需提高，練好了再來找我吧。";

        message_vision(HIY "$n" HIY "哈哈一笑，在$N" HIY "耳旁輕聲嘀咕了幾句，"
                       "隨即又伸手作\n刀，按照八卦四方之位比劃演示。$N" HIY "在"
                       "一旁沉默不語，直到\n演示結束，突然眼睛一亮，似乎在武學"
                       "上又有了新的突破。\n" NOR,
                       me, this_object());
        command("smile");
        command("say 這便是刀芒的要訣，你自己下來勤加練習吧。");
        tell_object(me, HIC "你學會了「劈天神芒」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("bagua-dao"))
                me->improve_skill("bagua-dao", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bagua-dao/mang", 1, me);
        addn("gongxian", -1000, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-dao/sha", me) )
                return "唉…你自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("bagua-dao", 1) < 1)
                return "你連八卦刀法都沒學，談什麼絕招？";

        if( query("gongxian", me)<1800 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-80000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("bagua-dao", 1) < 180)
                return "你的八卦刀法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 250)
                return "嗯，你的內功火候尚需提高，練好了再來找我吧。";

        message_vision(HIY "$n" HIY "凝神了$N" HIY "半天，長歎一聲，説道：“這一"
                       "招「殺龍無\n悔」本是我創來對付苗人鳳所用，但既然你的刀法"
                       "已達此境\n界，今日我就傳你這招。”説完，便伸手將$N" HIY
                       "招至身旁，低\n聲在$P" HIY "耳畔細説良久。\n" NOR, me,
                       this_object());
        command("sigh");
        command("say 這一招的訣竅就是義無返顧，奮力一擊。");
        command("say 要訣我都教你了，自己下去練吧。");
        tell_object(me, HIC "你學會了「殺龍無悔」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("bagua-dao"))
                me->improve_skill("bagua-dao", 1500000);
        if (me->can_improve_skill("bagua-dao"))
                me->improve_skill("bagua-dao", 1500000);
        if (me->can_improve_skill("bagua-dao"))
                me->improve_skill("bagua-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bagua-dao/sha", 1, me);
        addn("gongxian", -1800, me);

        return 1;
}

mixed ask_dao()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "商家堡" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你身為我的弟子，反而學起假仁假義來了"
                                       "，居然還有臉問我要寶刀？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "説道"
                                       "：“什麼東西，居然敢在我面前放肆！”\n"
                                       NOR, this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "商家堡" )
                return "哪裏來的野種，居然敢窺視我的寶刀？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才配用這八卦刀，你別拿去丟臉。";

        if( query("shen", me)>-50000 )
                return "像你這樣的心慈手軟之輩，這刀你不用也罷。";

        if (me->query_skill("bagua-dao", 1) < 150)
                return "你連八卦刀法都沒學好，就算寶刀在手也是白搭。";

        ob = find_object(BAGUADAO);
        if (! ob) ob = load_object(BAGUADAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？我的八卦刀現在不是你拿着在用嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我的八卦刀現在不在我手中。";

                if( query("family/family_name", owner) == "商家堡" )
                        return "紫金八卦刀現在是你兄弟"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "我的紫金八卦刀現在落在"+query("name", owner)+
                               "手中，你去把它搶回來吧！";
        }

        ob->move(this_object());

        ob = new("/clone/weapon/gangdao");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "冷笑一聲，道：“我這柄紫金八卦刀"
                       "你就拿去，在江湖上多揚揚商家堡的威風！”\n" NOR,
                       this_object(), me);
        command("givebaguadaoto"+query("id", me));
        return 1;
}

mixed give_letter()
{
        object letter, me;


        me = this_player();

        if( query("can_perform/bagua-dao/tian", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("bagua-dao", 1) < 1)
                return "你連八卦刀法都沒學，談什麼絕招？";

        if (me->query_skill("wai-bagua", 1) < 1)
                return "你連外八卦神功都沒學，談什麼絕招？";

        if (me->query_skill("nei-bagua", 1) < 1)
                return "你連內八卦神功都沒學，談什麼絕招？";

        if( query("gongxian", me)<2200 )
                return "你在鏢局內碌碌無為，這一招我暫時還不能傳你。";

        if (me->query_skill("bagua-dao", 1) < 200)
                return "你的八卦刀法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("wai-bagua", 1) < 200)
                return "你的外八卦神功還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("nei-bagua", 1) < 200)
                return "你的內八卦神功還練得不到家，自己下去練練再來吧！";

        if( query("max_neili", me)<3200 )
                return "你的內力修為不足，施展不出這招，等你內力有所攀升後再來找我吧。";

        if (present("sjm letter", me))
                return "快到鎮遠鏢局找我師傅去吧！";

        command("nod");
        command("say 嗯，看你在武學方面還有所造詣，而且多年來對商家堡做出了不少貢獻…");
        command("haha");
        command("say 現在我就休書一封，你送到鎮遠鏢局總鏢頭王維揚處，他自會傳你絕技！");

        "/clone/special/sjmletter"->move(me);
        write(HIC "你得到一封書信！\n" NOR);
        addn("gongxian", -2200, me);
        return "快去鎮遠鏢局找我師傅吧！";

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
