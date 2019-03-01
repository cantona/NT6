#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

void create()
{
        set_name("上官雲", ({ "shangguan yun", "shangguan", "yun"}));
        set("title", "日月神教白虎堂長老");
        set("nickname", WHT "雕俠" NOR);
        set("long", @LONG
這是日月神教白虎堂長老上官雲。在教中人稱
雕俠，為人極其耿直，武功又高強。
LONG);
        set("gender", "男性" );
        set("class", "scholar");
        set("age", 39);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 36);
        set("int", 36);
        set("con", 36);
        set("dex", 36);
        set("max_qi", 5200);
        set("max_jing", 3400);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 160);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 240);
        set_skill("tianhuan-shenjue", 240);
        set_skill("riyue-xinfa", 220);
        set_skill("dodge", 220);
        set_skill("juechen-shenfa", 240);
        set_skill("feiyan-zoubi", 220);
        set_skill("blade", 240);
        set_skill("danding-dao", 240);
        set_skill("shiying-lianhuan", 240);
        set_skill("strike", 180);
        set_skill("qingmang-zhang", 180);
        set_skill("parry", 220);
        set_skill("cuff", 200);
        set_skill("zhenyu-quan", 200);
        set_skill("claw", 200);
        set_skill("poyue-zhao", 200);
        set_skill("martial-cognize", 220);
        set_skill("literate", 140);

        map_skill("dodge", "juechen-shenfa");
        map_skill("force", "tianhuan-shenjue");
        map_skill("blade", "shiying-lianhuan");
        map_skill("parry", "shiying-lianhuan");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");
        map_skill("strike", "qingmang-zhang");

        prepare_skill("claw", "poyue-zhao");
        prepare_skill("cuff", "zhenyu-quan");

        create_family("日月神教", 13, "白虎堂長老");

        set("inquiry", ([
                "無痕殺" : (: ask_skill1 :),
                "斷脈破岳" : (: ask_skill2 :),
                "百鬼慟哭" : (: ask_skill3 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.sha" :),
                (: perform_action, "cuff.tong" :),
                (: perform_action, "claw.duan" :),
                (: exert_function, "recover" :),
        }) );
        set("master_ob",3);
        setup();

        carry_object("/d/heimuya/npc/obj/jinpao")->wear();
        carry_object("clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-30000 )
        {
                command("killair");
                command("say 老子最討厭偽君子，再不滾開我斃了你！");
                return;
        }

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你現在江湖經驗太淺，應該多走動走動。");
                return;
        }

        if (ob->query_skill("blade", 1) < 80)
        {
                command("hmm");
                command("say 俺是用刀的，你我習武的路線不對，難以教授。");
                return;
        }

        if (ob->query_skill("tianhuan-shenjue", 1) < 80
           && ob->query_skill("riyue-xinfa", 1) < 80)
        {
                command("hmm");
                command("say 你連本門最基本的內功都沒修好，怎麼學習上乘武學。");
                return;
        }

        command("haha");
        command("say 看你有心為神教出力，今日我就成全你。");
        command("say 日月神教一統江湖的千秋大業，就全靠你們了。");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/shiying-lianhuan/sha", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("shiying-lianhuan", 1) < 1)
                return "你連弒鷹九連環都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<600 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-40000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 200)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("shiying-lianhuan", 1) < 150)
                return "你的弒鷹九連環還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "笑了笑，伸手將$N" HIY "招到身前，低"
                     "聲在$N" HIY "耳旁嘀咕了半天。然後又拔出腰刀翻轉數下"
                     "，斜撩而出。似乎是一種頗為獨特的刀訣。\n\n" NOR, me,
                     this_object()); 

        command("nod2");
        command("say 看懂了嗎？看懂了就自己下去練吧。");
        tell_object(me, HIC "你學會了「無痕殺」。\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("shiying-lianhuan"))
                me->improve_skill("shiying-lianhuan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shiying-lianhuan/sha", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/poyue-zhao/duan", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("poyue-zhao", 1) < 1)
                return "你連破岳神爪都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<100 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-10000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 100)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("poyue-zhao", 1) < 80)
                return "你的破岳神爪還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "望著$N" HIY "讚許的點了點頭，笑道："
                     "“不錯，不錯。老夫念你平時練功努力，今日就傳你此招"
                     "，可瞧好了。”說完便只見$n" HIY "身形一展，雙爪疾攻"
                     "而上，霎時間爪影層層疊疊，虛實難辯，招數甚為巧妙。"
                     "\n\n" NOR, me, this_object()); 

        command("nod");
        command("say 這招的招式並不復雜，你下去後需勤加練習。");
        tell_object(me, HIC "你學會了「斷脈破岳」。\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("poyue-zhao"))
                me->improve_skill("poyue-zhao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/poyue-zhao/duan", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/zhenyu-quan/tong", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("zhenyu-quan", 1) < 1)
                return "你連鎮獄拳法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<150 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-12000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 120)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("zhenyu-quan", 1) < 80)
                return "你的鎮獄拳法還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "微微一笑，招手示意$N" HIY "到他跟前"
                     "，然後俯身在$N" HIY "耳邊輕聲嘀嘀咕咕了半天，$N" HIY
                     "直聽得眉開眼笑，一邊聽一邊不住地點頭。\n\n" NOR, me,
                     this_object()); 

        command("nod");
        command("say 對付那些正派人士，一上來就要像這樣痛下殺手。");
        tell_object(me, HIC "你學會了「百鬼慟哭」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("zhenyu-quan"))
                me->improve_skill("zhenyu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhenyu-quan/tong", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}
