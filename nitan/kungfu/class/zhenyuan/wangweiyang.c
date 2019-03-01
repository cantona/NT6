#include <ansi.h>
#include "zhenyuan.h"

#define HOUBEI    "/clone/lonely/houbeidao"
#define LETTER    "/clone/special/sjmletter"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_dao();

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();

void create()
{
        object ob;
        set_name("王維揚", ({ "wang weiyang", "wang", "weiyang", "wei", "yang"}));
        set("nickname", HIY "威震河朔" NOR);
        set("title", "鎮遠鏢局總鏢頭");
          set("gender", "男性");
        set("long", @LONG
這位就是鎮遠鏢局的創始人，有“威震河朔”之
稱的王維揚。江湖上有句話叫：“寧碰閻王，莫
碰老王”，這個老王指的就是他。但見他紅光滿
面，隱隱中又透著紫氣，太陽穴微微凸起，便知
乃是八卦門中的鼎尖高手。由于年邁，他已經不
管理鏢局中事務了，一門心思放在提高自己的武
功修為上。
LONG );
          set("age", 68);
        set("class", "fighter");
        set("attitude", "peaceful");
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 5200);
        set("max_jing", 4000);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 200);
        set("combat_exp", 3500000);

          set_skill("force", 260);
          set_skill("nei-bagua", 260);
          set_skill("bagua-xinfa", 240);
          set_skill("parry", 260);
          set_skill("wai-bagua", 260);
          set_skill("dodge", 240);
          set_skill("bagua-bu", 240);
          set_skill("unarmed", 240);
          set_skill("youshen-zhang", 240);
          set_skill("strike", 240);
          set_skill("bagua-zhang", 240);
          set_skill("bazhen-zhang", 240);
          set_skill("cuff", 240);
          set_skill("bagua-quan", 240);
          set_skill("yanqing-quan", 240);
          set_skill("blade", 260);
          set_skill("bagua-dao", 260);
          set_skill("kuimang-dao", 240);
          set_skill("throwing", 240);
          set_skill("bagua-biao", 240);
          set_skill("literate", 220);
          set_skill("martial-cognize", 240);

        map_skill("unarmed", "youshen-zhang");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "nei-bagua");
        map_skill("strike", "bazhen-zhang");
        map_skill("blade", "bagua-dao");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "bagua-biao");

        prepare_skill("unarmed", "youshen-zhang");
        set("class", "fighter");

          create_family("八卦門", 1, "掌門");

        set("inquiry", ([
                "厚背紫金刀" : (: ask_dao :),
                "八卦震"     : (: ask_skill1 :),
                "神卦天印"   : (: ask_skill2 :),
                "乾坤一擲"   : (: ask_skill3 :),
                "翻卦連環掌" : (: ask_skill4 :),
                "劈天神芒"   : (: ask_skill5 :),
                "天刀八勢"   : (: ask_skill6 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "blade.tian" :),
                (: perform_action, "unarmed.fan" :),
                (: perform_action, "parry.zhen" :),
                (: perform_action, "throwing.zhi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

          setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        if (clonep())
        {
                ob = find_object(HOUBEI);
                if (! ob) ob = load_object(HOUBEI);
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

          carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));
}

int accept_fight(object me)
{
          command("say 這位" + RANK_D->query_respect(me) +
                "，你不是我的對手，我看較量還是免了吧！\n");
          return 0;
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if (me->query_int() < 35 && me->query_con() < 35)
        {
                command("hmm");
                command("say 你體質孱弱，為人又不機靈，我收下你有什麼用？");
                return;
        }

        if( query("combat_exp", me)<320000 )
        {
                command("say 你的江湖經驗太差了，我授徒可是件大事，等過段日子再說吧！");
                return;
        }

        if (me->query_skill("bagua-xinfa", 1) < 100)
        {
                command("say 你本門的內功修為太差了，再回去練練吧。");
                return;
        }

        command("haha");
          command("say 很好，希望你多加努力，好好學習本門武功，他日將八卦門發揚光大。");
        command("recruit "+query("id", me));

        if( query("class", me) != "fighter" )
                set("class", "fighter", me);
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/wai-bagua/zhen", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("wai-bagua", 1) < 1)
                return "你連外八卦都沒學，談什麼絕招？";

        if( query("gongxian", me)<100 )
                return "你在鏢局內碌碌無為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("wai-bagua", 1) < 60)
                return "你的外八卦還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "微微一笑，當下也不答話，只是伸出右手，輕輕放"
                       "在\n$N" HIY "胸口。正當$N" HIY "疑惑間，卻見$n" HIY "掌勁"
                       "輕吐，$N" HIY "頓時全身\n一震，如遭電擊，各處經脈無不酸麻"
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

        if( query("can_perform/bazhen-zhang/yin", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("bazhen-zhang", 1) < 1)
                return "你連八陣八卦掌都沒學，談什麼絕招？";

        if( query("gongxian", me)<500 )
                return "你在鏢局內碌碌無為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("bazhen-zhang", 1) < 130)
                return "你的八陣八卦掌還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "笑了笑，對$N" HIY "點頭示意讚許，當下凝神沉"
                       "履，積聚全\n身功力于一掌，攜著雷霆之勢奮力向$N" HIY "面前"
                       "的一座青銅香爐\n拍落，頓時只聽轟然一聲悶響，香爐內的香灰"
                       "被$n" HIY "的掌\n力激盪得四處飛揚，塵煙彌漫，待得煙消雲散"
                       "，$N" HIY "這才發現\n那座青銅香爐上豁然嵌著一雙掌印。\n"
                       NOR, me, this_object());

        command("ke");
        command("nod");
        command("say 這八陣八卦掌是我八卦門絕學，可要勤加練習。");
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

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-biao/zhi", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("bagua-biao", 1) < 1)
                return "你連八卦鏢訣都沒學，談什麼絕招？";

        if( query("gongxian", me)<800 )
                return "你在鏢局內碌碌無為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("bagua-biao", 1) < 120)
                return "你的八卦鏢訣還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "將$N" HIY "招至跟前，輕聲在耳旁秘密說了些"
                       "什麼。隨後又\n伸出右手，十指箕張，一伸一縮，煞是巧妙。"
                       "看樣子是一種\n很特別的暗器法門。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 剛才我所說的你可都記牢了？剩下的就是靠自己多加練習。");
        tell_object(me, HIC "你學會了「乾坤一擲」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("bagua-biao"))
                me->improve_skill("bagua-biao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bagua-biao/zhi", 1, me);
        addn("gongxian", -800, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/youshen-zhang/fan", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("youshen-zhang", 1) < 1)
                return "你連遊身八卦掌都沒學，談什麼絕招？";

        if( query("gongxian", me)<500 )
                return "你在鏢局內碌碌無為，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 160)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("youshen-zhang", 1) < 120)
                return "你的遊身八卦掌還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "大笑數聲，對$N" HIY "說道：“既然你遊身八卦"
                       "掌已有如此\n造詣，我今日便傳你這套掌法的精髓。”說完便只"
                       "見$n" HIY "\n腳踏八卦四方之位，身形在全場遊走不定，雙掌隨"
                       "後緊拍而\n出，頓時掌影將$N" HIY "四方各處團團籠罩，$N" HIY
                       "感到在這層層掌影\n之下，竟然連呼吸都不能暢通。\n" NOR, me,
                       this_object());

        command("haha");
        command("say 這招的要詣不過就是一個疾字，你慢慢體會吧。");
        tell_object(me, HIC "你學會了「翻卦連環掌」。\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("youshen-zhang"))
                me->improve_skill("youshen-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/youshen-zhang/fan", 1, me);
        addn("gongxian", -500, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-dao/mang", me) )
                return "我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("bagua-dao", 1) < 1)
                return "你連八卦刀法都沒學，談什麼絕招？";

        if (me->query_skill("wai-bagua", 1) < 1)
                return "你連外八卦神功都沒學，談什麼絕招？";

        if( query("gongxian", me)<1000 )
                return "你在鏢局內碌碌無為，這一招我暫時還不能傳你。";

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

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-dao/tian", me) )
                return "你不是已經學會了嗎？怎麼，又給忘記了？";

        if( query("family/family_name", me) != query("family/family_name" )
             && query("family/family_name", me) != "商家堡" )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if( query("family/family_name", me) == "商家堡" )
                return "你雖然是商家堡的弟子，但沒有你師傅同意我也不能傳你這招！";

        if (me->query_skill("bagua-dao", 1) < 1)
                return "你連八卦刀法都沒學，談什麼絕招？";

        if (me->query_skill("wai-bagua", 1) < 1)
                return "你連外八卦神功都沒學，談什麼絕招？";

        if (me->query_skill("nei-bagua", 1) < 1)
                return "你連內八卦神功都沒學，談什麼絕招？";

        if( query("gongxian", me)<2400 )
                return "你在鏢局內碌碌無為，這一招我暫時還不能傳你。";

        if (me->query_skill("bagua-dao", 1) < 200)
                return "你的八卦刀法還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("wai-bagua", 1) < 200)
                return "你的外八卦神功還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("nei-bagua", 1) < 200)
                return "你的內八卦神功還練得不到家，自己下去練練再來吧！";

        if( query("max_neili", me)<3200 )
                return "你的內力修為不足，施展不出這招，等你內力有所攀升後再來找我吧。";

        message_vision(HIY "$n" HIY "微笑著點了點頭，對$N" HIY "道：“你來我八卦"
                       "門修行也有\n好長陣子了，可知道何為「八卦」嗎？”$N" HIY
                       "想也不想，隨口\n答道：“八卦乃天居乾、地居坤、風居巽、雲"
                       "居震、飛龍居\n坎、武翼居兌、鳥翔居離、蜿盤居艮。”$n" HIY
                       "聽後頗為讚\n許，笑道：“你這是只知其一，不知其二。所謂「"
                       "八卦」的\n真諦乃是一個「陣」字。”$N" HIY "悶了好一會，"
                       "默默思考這一句\n話，突然雙目一亮，叫道：“師父，弟子終于"
                       "明白什麼是真\n正的「八卦」了！”$n" HIY "大笑道：“你只"
                       "要明白了這個道\n理，那麼這八勢刀法你就已經學會了。”\n" NOR,
                       me, this_object());

        command("haha");
        tell_object(me, HIC "你學會了「天刀八勢」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("nei-bagua"))
                me->improve_skill("nei-bagua", 1500000);
        if (me->can_improve_skill("nei-bagua"))
                me->improve_skill("nei-bagua", 1500000);
        if (me->can_improve_skill("nei-bagua"))
                me->improve_skill("nei-bagua", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
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
        set("can_perform/bagua-dao/tian", 1, me);
        addn("gongxian", -2400, me);

        return 1;
}

mixed ask_dao()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "八卦門" )
                return "厚背紫金八卦刀是我八卦門的至寶，你打聽它幹什麼？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才配用厚背紫金刀，你就忍了吧。";

        if (me->query_skill("bagua-dao", 1) < 120)
                return "你還是下去再練練你的八卦刀法吧。";

        ob = find_object(HOUBEI);
        if (! ob) ob = load_object(HOUBEI);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "咦？厚背紫金刀現在不正是你拿著嗎，怎麼還反過來問我？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我已經把厚背紫金刀借出去了。";

                if( query("family/family_name", owner) == "八卦門" )
                        return "厚背紫金刀在暫時是你同門師兄"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "本門的厚背紫金刀現在落在了"+query("name", owner)+
                               "手中，你要用就去把它奪回來吧！";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "微微笑道：“既然這樣，我這柄厚背紫金刀你就"
                       "拿去用吧，行走江湖時用它揚揚咱們的威風！”\n" NOR,
                       this_object(), me);
        command("givehoubeidaoto"+query("id", me));
        return 1;
}

int accept_object(object me, object ob)
{
        if (base_name(ob) != HOUBEI
            && base_name(ob) != LETTER)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if (base_name(ob) == LETTER)
        {
                if( query("can_perform/bagua-dao/tian", me) )
                {
                     command("shake");
                     command("shit");
                     return 1;
                }
                command("nod");
                command("haha");
                command("say 好，好！既然這樣，我就傳你這招「天刀八勢」！"); 
                message_sort(HIY "\n$n" HIY "微笑著點了點頭，對$N" HIY "道：“你"
                             "可知道何為「八卦」嗎？”$N" HIY "想也不想，隨口答道"
                             "：“八卦乃天居乾、地居坤、風居巽、雲居震、飛龍居坎、"
                             "武翼居兌、鳥翔居離、蜿盤居艮。”$n" HIY "聽後頗為讚許"
                             "，笑道：“你這是只知其一，不知其二。所謂「八卦」的真"
                             "諦乃是一個「陣」字。”$N" HIY "悶了好一會，默默思考這"
                             "一句話，突然雙目一亮，叫道：“師父，弟子終于明白什麼"
                             "是真正的「八卦」了！”$n" HIY "大笑道：“你只要明白"
                             "了這個道理，那麼這八勢刀法你就已經學會了。”\n" NOR,
                             me, this_object());

        command("haha");
        tell_object(me, HIC "你學會了「天刀八勢」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("nei-bagua"))
                me->improve_skill("nei-bagua", 1500000);
        if (me->can_improve_skill("nei-bagua"))
                me->improve_skill("nei-bagua", 1500000);
        if (me->can_improve_skill("nei-bagua"))
                me->improve_skill("nei-bagua", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
        if (me->can_improve_skill("wai-bagua"))
                me->improve_skill("wai-bagua", 1500000);
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
        set("can_perform/bagua-dao/tian", 1, me);

        return 1;

        }
        
        else
        {
            if( query("family/master_id", me) != query("id") )
                    command("say 多謝這位" + RANK_D->query_respect(me) + "將厚背紫金刀交回。");
            else
                    command("say 很好，很好！");
                    destruct(ob);
        }
        return 1;
}
