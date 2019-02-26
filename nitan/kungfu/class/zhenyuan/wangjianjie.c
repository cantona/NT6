#include <ansi.h>
#include "zhenyuan.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

void create()
{
        set_name("王劍傑", ({ "wang jianjie", "wang", "jianjie" }));
        set("long", @LONG
他是鎮遠鏢局總鏢頭王維揚的第二個兒子，子承
父業，練得一身八卦門的好武功。現在鏢局裏的
各種事務由他總管，看上去他精明老練，穩重務
實，不怒自威。
LONG );
        set("title", "八卦門第二代高手");
          set("gender", "男性");
          set("age", 45);
        set("class", "fighter");
        set("attitude", "peaceful");
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 3500);
        set("max_jing", 3500);
        set("neili", 3200);
        set("max_neili", 3200);
        set("jiali", 130);
        set("combat_exp", 1500000);

        set_skill("parry", 160);
        set_skill("wai-bagua", 160);
        set_skill("force", 160);
        set_skill("nei-bagua", 160);
        set_skill("bagua-xinfa", 140);
        set_skill("dodge", 140);
        set_skill("bagua-bu", 140);
        set_skill("blade", 160);
        set_skill("bagua-dao", 160);
        set_skill("kuimang-dao", 160);
        set_skill("strike", 160);
        set_skill("bagua-zhang", 140);
        set_skill("bazhen-zhang", 160);
        set_skill("cuff", 140);
        set_skill("bagua-quan", 140);
        set_skill("throwing", 140);
        set_skill("bagua-biao", 140);
        set_skill("literate", 160);
          set_skill("martial-cognize", 140);

        set("no_teach", ([
                "wai-bagua" : "這個…外八卦神功…你還是找我爹或是我哥教你好了。",
                "nei-bagua" : "我爹説過了，內八卦神功不能隨便傳授，你直接找我爹好了。",
                "bagua-dao" : "八卦刀法向來便是由我父親親自教授。",
        ]));

        map_skill("blade", "bagua-dao");
        map_skill("unarmed", "bazhen-zhang");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "nei-bagua");
        map_skill("strike", "bagua-zhang");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "bagua-biao");

        prepare_skill("strike", "bazhen-zhang");

        set("inquiry", ([
                "劈卦拳"   : (: ask_skill1 :),
                "背心釘"   : (: ask_skill2 :),
                "蝰蟒盤身" : (: ask_skill3 :),
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/beijing/shufang",
                   "id"        : "wang weiyang" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷喝道："
                                "我不管你是怎麼進來的，但是請你馬"
                                "上離開，否則休怪我無情！" NOR,
                "refuse_carry": CYN "$N" CYN "對着$n" CYN "劍眉一"
                                "豎，喝道：你背上背的是什麼？給我"
                                "放下來！" NOR,
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "strike.yin" :),
                (: perform_action, "parry.zhen" :),
                (: perform_action, "throwing.zhi" :),
                (: perform_action, "throwing.xian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

          create_family("八卦門", 2, "高手");

          setup();

          carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("combat_exp", me)<20000 )
            {
                      command("say 你的江湖經驗太差了，還是在鏢局裏再摸爬滾打一段時間吧！");
                      return;
            }

          command("nod");
          command("say 既然如此，我就收下你。你平時也要多為鏢局出力。");
        command("recruit "+query("id", me));
        if( query("class", me) != "fighter" )
                set("class", "fighter", me);
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-quan/gua", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("bagua-quan", 1) < 1)
                return "你連八卦拳法都沒學，還談什麼絕招可言？";

        if( query("gongxian", me)<100 )
                return "你為鏢局出力不夠，這招我暫時不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("bagua-quan", 1) < 70)
                return "你的八卦拳法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，説道：“我給你演示一遍"
                       "，可要瞧清\n楚了。”$n" HIY "話音剛落，突然身體一側，雙掌"
                       "頓時向下沉\n去，接着卻又向上一翻，朝着$N" HIY "的雙肩斜斜"
                       "地劈去，招數甚\n為精妙，頓時將$N" HIY "攻了個措手不及。\n"
                       NOR, me, this_object());

        command("haha");
        command("say 你看明白了多少？");
        tell_object(me, HIC "你學會了「劈卦拳」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("bagua-quan"))
                me->improve_skill("bagua-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bagua-quan/gua", 1, me);
        addn("gongxian", -100, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-zhang/ding", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("bagua-zhang", 1) < 1)
                return "你連八卦掌法都沒學，還談什麼絕招可言？";

        if( query("gongxian", me)<150 )
                return "你為鏢局出力不夠，這招我暫時不忙傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("bagua-zhang", 1) < 80)
                return "你的八卦掌法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "眉頭微微一皺，上下打量了$N" HIY "一翻，這才伸"
                       "手將$N" HIY "招\n至身旁，在耳邊輕聲講解了半天，時不時還探出"
                       "右手比劃幾\n下招式，$N" HIY "聽後冷笑一聲，似乎有所領悟。\n"
                       NOR, me, this_object());

        command("nod");
        command("say 這招可以攻敵不備，你自己下去練吧。");
        tell_object(me, HIC "你學會了「背心釘」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("bagua-zhang"))
                me->improve_skill("bagua-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bagua-zhang/ding", 1, me);
        addn("gongxian", -150, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/kuimang-dao/pan", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("kuimang-dao", 1) < 1)
                return "你連蝰蟒刀法都沒學，還談什麼絕招可言？";

        if( query("gongxian", me)<50 )
                return "你為鏢局出力不夠，這招我暫時不忙傳你。";

        if (me->query_skill("force") < 60)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("kuimang-dao", 1) < 40)
                return "你的蝰蟒刀法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "笑了笑，伸手將$N" HIY "招到身前，低聲在$N" HIY
                       "耳旁嘀咕了半\n天。然後又拔出腰刀翻轉數下，斜撩而出。似乎是"
                       "一種頗為\n獨特的刀訣。\n" NOR, me, this_object());

        command("nod");
        command("say 這招很簡單，稍加練習便行。");
        tell_object(me, HIC "你學會了「蝰蟒盤身」。\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("kuimang-dao"))
                me->improve_skill("kuimang-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/kuimang-dao/pan", 1, me);
        addn("gongxian", -50, me);

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
