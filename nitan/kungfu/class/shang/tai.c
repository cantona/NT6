#include <ansi.h>
#include "shang.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();

mixed  try_to_learn_waibagua();

void create()
{
        set_name("商老太", ({"shang laotai", "shang", "laotai"}));
        set("gender", "女性");
        set("title", "商家堡堡主夫人");
        set("age", 41);
        set("long", @LONG
這是一位身材高大的婦人，表情嚴肅，令人起
敬。她便是「八卦刀」商劍鳴的夫人，她少女
時便跟隨丈夫走南闖北，不愧為女中豪傑。
LONG);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3600);
        set("max_qi", 3600);
        set("jing", 2800);
        set("max_jing", 2800);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 160);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 160);
        set_skill("shangjia-neigong", 160);
        set_skill("parry", 160);
        set_skill("wai-bagua", 160);
        set_skill("dodge", 160);
        set_skill("bagua-bu", 160);
        set_skill("unarmed", 140);
        set_skill("tan-tui", 140);
        set_skill("strike", 160);
        set_skill("bagua-zhang", 160);
        set_skill("cuff", 160);
        set_skill("bagua-quan", 160);
        set_skill("sword", 140);
        set_skill("quemen-jian", 140);
        set_skill("blade", 180);
        set_skill("bagua-dao", 180);
        set_skill("shangjia-dao", 160);
        set_skill("throwing", 160);
        set_skill("jinbiao-jue", 160);
        set_skill("literate", 200);
        set_skill("martial-cognize", 160);

        map_skill("unarmed", "tan-tui");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "shangjia-neigong");
        map_skill("strike", "bagua-zhang");
        map_skill("sword", "quemen-jian");
        map_skill("blade", "bagua-dao");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "jinbiao-jue");

        prepare_skill("cuff", "bagua-quan");
        prepare_skill("strike", "bagua-zhang");

        set("no_teach", ([
                "bagua-dao" : "八卦刀需由我夫君親自傳授。",
                "wai-bagua" : (: try_to_learn_waibagua :),
        ]));

        set("class", "fighter");

        create_family("商家堡", 3, "堡主夫人");

        set("inquiry", ([
                "劈卦拳"     : (: ask_skill1 :),
                "背心釘"     : (: ask_skill2 :),
                "犀牛望月"   : (: ask_skill3 :),
                "天殘劍訣"   : (: ask_skill4 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "strike.ding" :),
                (: perform_action, "cuff.gua" :),
                (: perform_action, "parry.zhen" :),
                (: perform_action, "throwing.huan" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->name(1) == "商劍鳴")
        {
                command("say 你取我丈夫的名字做甚？");
                return;
        }

        if (ob->name(1) == "商老太")
        {
                command("say 你取這個名字是什麼意思？");
                return;
        }

        if (ob->name(1) == "商寶震")
        {
                command("say 你給俺換起一個別的名字不行？");
                return;
        }

        if( query("family/master_name", ob) == "商劍鳴" )
        {
                command("say 既然你已經跟隨我夫君學藝，就應努力上進，幹嘛又來找我？");
                return;
        }

        command("say 今日我便代夫君收你為徒，望你日後在我商家堡有所作為。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "fighter" )
                set("class", "fighter", ob);
        return;
}

mixed try_to_learn_waibagua()
{
        object ob = this_player();

        if( query("can_learn/shanglaotai/wai-bagua", ob) )
                return 0;

        if( query("combat_exp", ob)>100000 )
        {
                command("say 看來你武功已有了一定火候，我就替夫君傳你外八卦神功。");
                set("can_learn/shanglaotai/wai-bagua", 1, ob);
                return 0;
        }

        return "你此時功力太淺，還是先學一些入門功夫吧。";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/bagua-quan/gua", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("bagua-quan", 1) < 1)
                return "你連八卦拳法都沒學，還談什麼絕招可言？";

        if( query("gongxian", me)<100 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-10000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("force") < 100)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("bagua-quan", 1) < 70)
                return "你的八卦拳法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，說道：“我給你演示一遍"
                       "，可要瞧清\n楚了。”$n" HIY "話音剛落，突然身體一側，雙掌"
                       "頓時向下沉\n去，接著卻又向上一翻，朝著$N" HIY "的雙肩斜斜"
                       "地劈去，招數甚\n為精妙，頓時將$N" HIY "攻了個措手不及。\n"
                       NOR, me, this_object());

        command("heng");
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
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("bagua-zhang", 1) < 1)
                return "你連八卦掌法都沒學，還談什麼絕招可言？";

        if( query("gongxian", me)<150 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-20000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

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

        if( query("can_perform/tan-tui/wang", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("tan-tui", 1) < 1)
                return "你連十二路潭腿都沒學，談什麼絕招？";

        if( query("gongxian", me)<350 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-25000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("force") < 150)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("tan-tui", 1) < 120)
                return "你的十二路潭腿還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "哼了一聲，沉聲道：“潭腿本身威力並不強，但卻被"
                       "\n喻為武林四大家之一，倒也有它的獨到之處。”說完便隨即\n起身"
                       "而立，左腿連變數中方位，“砰”的一聲陡然踢出，頓\n時將$N" HIY
                       "面前的那張木幾踢得粉碎。\n" NOR, me, this_object());

        command("say 明白了麼？");
        tell_object(me, HIC "你學會了「犀牛望月轉回還」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("tan-tui"))
                me->improve_skill("tan-tui", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tan-tui/wang", 1, me);
        addn("gongxian", -350, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/quemen-jian/can", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "與我商家堡素無來往，何出此言？";

        if (me->query_skill("quemen-jian", 1) < 1)
                return "你連缺門劍法都沒學，談什麼絕招？";

        if( query("gongxian", me)<60 )
                return "你在我商家堡內碌碌無為，這一招我暫時還不能傳你。";

        if( query("shen", me)>-5000 )
                return "哼！你這樣的心慈手軟之徒，就算學了這招又有何用？";

        if (me->query_skill("force") < 120)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("quemen-jian", 1) < 80)
                return "你的缺門劍法還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "冷笑一聲，也不答話，當即從$N" HIY "手中接過長"
                       "劍，慢慢\n的演示劍招，$N" HIY "見招式輕盈靈動，變幻無方，甚"
                       "為奇異。實\n乃前所謂聞，頓時大有所悟。\n" NOR, me,
                       this_object());

        command("say 這招乃是以奇制勝，我演示的你可都記清了？");
        tell_object(me, HIC "你學會了「天殘劍訣」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("quemen-jian"))
                me->improve_skill("quemen-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/quemen-jian/can", 1, me);
        addn("gongxian", -60, me);

        return 1;
}
