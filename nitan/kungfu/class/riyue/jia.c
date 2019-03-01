#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("賈布", ({ "jia bu", "jia", "bu"}));
        set("title", "日月神教青龍堂長老");
        set("nickname", YEL "金面使者" NOR);
        set("long", @LONG
這是日月神教青龍堂長老賈布。只見他蠟黃瘦
臉，兩邊太陽穴高高鼓起，變如藏了一枚枚核
桃似的，表情甚是嚴肅。
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
        
        set("max_qi", 4800);
        set("max_jing", 3500);
        set("neili", 5600);
        set("max_neili", 5600);
        set("jiali", 180);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 220);
        set_skill("riyue-xinfa", 220);
        set_skill("tianhuan-shenjue", 220);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("juechen-shenfa", 240);
        set_skill("dagger", 240);
        set_skill("jifeng-cixuefa", 240);
        set_skill("canghong-bifa", 240);
        set_skill("claw", 200);
        set_skill("da-qinna", 180);
        set_skill("xiao-qinna", 180);
        set_skill("strike", 200);
        set_skill("qingmang-zhang", 200);
        set_skill("parry", 240);
        set_skill("martial-cognize", 180);
        set_skill("literate", 220);

        map_skill("dodge", "juechen-shenfa");
        map_skill("force", "tianhuan-shenjue");
        map_skill("dagger", "canghong-bifa");
        map_skill("claw", "da-qinna");
        map_skill("parry", "canghong-bifa");
        map_skill("strike", "qingmang-zhang");

        prepare_skill("claw", "xiao-qinna");

        create_family("日月神教", 13, "青龍堂長老");

        set("inquiry", ([
                "驚虹一筆" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dagger.jing" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob",3);
        setup();

        carry_object("/d/heimuya/npc/obj/jinpao")->wear();
        carry_object("/d/meizhuang/obj/panguanbi")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-25000 )
        {
                command("hmm");
                command("say 我從來不和正派武林人士交往，你快滾吧！");
                return;
        }

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你現在江湖經驗太淺，還應該多走動走動。");
                return;
        }

        if (ob->query_skill("dagger", 1) < 80)
        {
                command("en");
                command("say 我所精研的乃是打穴法，這三十四路蒼虹筆法天下無雙。");
                command("say 你既然要做我的弟子，就應該在短兵刃上面多下功夫。");
                return;
        }

        if (ob->query_skill("tianhuan-shenjue", 1) < 80
           && ob->query_skill("riyue-xinfa", 1) < 80)
        {
                command("hmm");
                command("say 你連本門最基本的內功都沒修好，怎麼學習上乘武學。");
                return;
        }

        command("nod2");
        command("say 那你以後就跟著我好了。");
        command("say 教內事務繁多，切莫亂了規矩。");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/canghong-bifa/jing", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("canghong-bifa", 1) < 1)
                return "你連蒼虹筆法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-30000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 150)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("canghong-bifa", 1) < 100)
                return "你的蒼虹筆法還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "哈哈一笑，說道：不錯，不錯，孺子可"
                     "教也。今天老夫就傳你這招。$n" HIY "說完便將$N" HIY
                     "招至身前，嘀嘀咕咕說了半天。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 剛才我所說的便是這筆法的精要，你聽懂了多少？");
        tell_object(me, HIC "你學會了「驚虹一筆」。\n" NOR);
        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("canghong-bifa"))
                me->improve_skill("canghong-bifa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/canghong-bifa/jing", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
