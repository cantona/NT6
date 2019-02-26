#include <ansi.h>
#include "zhenyuan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("王劍英", ({ "wang jianying", "wang", "jianying" }));
        set("long", @LONG
他是鎮遠鏢局總鏢頭王維揚的大兒子，看上去紅
光滿面，氣宇軒昂，神態自若，便知他內力深厚，
除了他父親，儼然便是當世八卦門第一高手，八
卦門掌門的繼承人。
LONG );
        set("title", "當世八卦門第一高手");
          set("gender", "男性");
          set("age", 48);
        set("class", "fighter");
        set("attitude", "peaceful");
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 3200);
        set("max_jing", 3200);
        set("neili", 3600);
        set("max_neili", 3600);
        set("jiali", 150);
        set("combat_exp", 2500000);

          set_skill("parry", 160);
          set_skill("wai-bagua", 160);
          set_skill("force", 180);
          set_skill("nei-bagua", 180);
          set_skill("bagua-xinfa", 160);
          set_skill("dodge", 160);
          set_skill("bagua-bu", 160);
          set_skill("blade", 180);
          set_skill("bagua-dao", 180);
          set_skill("kuimang-dao", 160);
          set_skill("strike", 160);
          set_skill("bagua-zhang", 160);
          set_skill("bazhen-zhang", 160);
          set_skill("cuff", 160);
          set_skill("bagua-quan", 160);
          set_skill("throwing", 160);
          set_skill("bagua-biao", 160);
          set_skill("literate", 140);
          set_skill("martial-cognize", 160);

        set("no_teach", ([
                "nei-bagua" : "內八卦神功必須由我父親親自傳授。",
                "bagua-dao" : "八卦刀法向來便是由我父親親自教授。",
        ]));

        map_skill("blade", "bagua-dao");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "nei-bagua");
        map_skill("strike", "bagua-zhang");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "bagua-biao");

        prepare_skill("cuff", "bagua-quan");
        prepare_skill("strike", "bagua-zhang");

          create_family("八卦門", 2, "高手");

        set("inquiry", ([
                "掌中夾鏢" : (: ask_skill1 :),
                "鏢中現掌" : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "cuff.gua" :),
                (: perform_action, "strike.ding" :),
                (: perform_action, "strike.jia" :),
                (: perform_action, "parry.zhen" :),
                (: perform_action, "throwing.zhi" :),
                (: perform_action, "throwing.xian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

          setup();

        carry_object("/clone/weapon/gangdao")->wield();
          carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));

}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("combat_exp", me)<100000 )
            {
                      command("say 你的江湖經驗太差了，還是在鏢局裏再摸爬滾打一段時間吧！");
                      return;
            }

        if (me->query_skill("bagua-xinfa", 1) < 80)
        {
                command("say 你本門的內功修為太差，還是練練再説吧。");
                return;
        }

          command("nod");
          command("say 既然如此，我就收下你。");
        command("recruit "+query("id", me));
        if( query("class", me) != "fighter" )
                set("class", "fighter", me);
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-zhang/jia", me) )
                return "該説的我都説完了，還有什麼不明白就自己下去練！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("bagua-zhang", 1) < 1)
                return "你連八卦掌都沒學，談什麼絕招？";

        if (me->query_skill("bagua-biao", 1) < 1)
                return "你連八卦鏢都沒學，談什麼絕招？";

        if( query("gongxian", me)<400 )
                return "你為鏢局出力不夠，這招我暫時不忙傳你。";

        if (me->query_skill("bagua-zhang", 1) < 120)
                return "你的八卦掌還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("bagua-biao", 1) < 120)
                return "你的八卦鏢還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 150)
                return "嗯，你的鏢掌都已經嫻熟了，但是切記內功火候是基礎，這可半點馬虎不得。";

        message_vision(HIY "$n" HIY "點了點頭，伸手將$N" HIY "招到身邊，在耳旁嘀嘀"
                       "咕咕了半\n天，還時不時伸出手比劃兩下。$N" HIY "一邊聽一邊不"
                       "住的點頭稱\n是，似乎對$n" HIY "的教導大有感悟。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 該説的我都説了，你自己下去練習吧。");
        tell_object(me, HIC "你學會了「掌中夾鏢」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("bagua-zhang"))
                me->improve_skill("bagua-zhang", 1500000);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("bagua-biao"))
                me->improve_skill("bagua-biao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bagua-zhang/jia", 1, me);
        addn("gongxian", -400, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-biao/xian", me) )
                return "嗯？這招不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本鏢局素無來往，何出此言？";

        if (me->query_skill("bagua-zhang", 1) < 1)
                return "你連八卦掌都沒學，談什麼絕招？";

        if (me->query_skill("bagua-biao", 1) < 1)
                return "你連八卦鏢都沒學，談什麼絕招？";

        if( query("gongxian", me)<400 )
                return "你為鏢局出力不夠，這招我暫時不忙傳你。";

        if (me->query_skill("bagua-zhang", 1) < 120)
                return "你的八卦掌還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("bagua-biao", 1) < 120)
                return "你的八卦鏢還練得不到家，自己下去練練再來吧！";

        if (me->query_skill("force") < 200)
                return "嗯，你的鏢掌都已經嫻熟了，但是切記內功火候是基礎，這可半點馬虎不得。";

        message_vision(HIY "$n" HIY "看了$N" HIY "半天，讚許的點了點頭，對$N" HIY
                       "説道：“既然你\n如此有心，我就給你演示一遍，你可看仔細了！"
                       "”聽得話音\n剛落，頓時從$n" HIY "袖底竄出一道金光，直奔$N"
                       HIY "而去，$N" HIY "見\n狀立即飛身躲避，可剎那間只見$n" HIY
                       "身形一晃，一雙手掌\n已搭在$N" HIY "胸前。$N" HIY "頓時呆立"
                       "當場，半響都説不出話來。\n" NOR, me, this_object());

        command("haha");
        command("say 這招教給你了，但切記我們身在天子腳下，千萬別去招惹官府。");
        tell_object(me, HIC "你學會了「鏢中現掌」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("bagua-zhang"))
                me->improve_skill("bagua-zhang", 1500000);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("bagua-biao"))
                me->improve_skill("bagua-biao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/bagua-biao/xian", 1, me);
        addn("gongxian", -400, me);

        return 1;
}
