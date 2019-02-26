#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("秦偉邦", ({ "qin weibang", "qin", "weibang"}));
        set("title", "日月神教青旗旗主");
        set("long", @LONG
這是日月神教青旗旗主秦偉邦，三十多歲年紀
便已被提拔為旗主，可謂功勞不小。
LONG);
        set("gender", "男性" );
        set("class", "scholar");
        set("age", 32);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 36);
        set("int", 36);
        set("con", 36);
        set("dex", 36);
        
        set("max_qi", 3400);
        set("max_jing", 2200);
        set("neili", 3600);
        set("max_neili", 3600);
        set("jiali", 120);
        set("combat_exp", 1500000);
        set("score", 10000);

        set_skill("force", 160);
        set_skill("riyue-xinfa", 160);
        set_skill("dodge", 150);
        set_skill("feiyan-zoubi", 150);
        set_skill("blade", 160);
        set_skill("danding-dao", 160);
        set_skill("parry", 150);
        set_skill("cuff", 150);
        set_skill("zhenyu-quan", 150);
        set_skill("claw", 150);
        set_skill("poyue-zhao", 150);
        set_skill("martial-cognize", 150);
        set_skill("literate", 160);

        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "riyue-xinfa");
        map_skill("blade", "danding-dao");
        map_skill("parry", "danding-dao");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");

        prepare_skill("claw", "poyue-zhao");
        prepare_skill("cuff", "zhenyu-quan");

        create_family("日月神教", 14, "旗主");

        set("inquiry", ([
                "環環相扣" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.kou" :),
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

        if( query("shen", ob)>0 )
        {
                command("heng");
                command("say 我日月神教從來不和正派人士結交，快給我滾開。");
                return;
        }

        if( query("gender", ob) == "女性" )
        {
                command("sneer");
                command("say 教內規矩甚嚴，我職位未到，不敢私收女徒。");
                return;
        }

        command("nod2");
        command("say 那你就跟着我吧，入教之後的各種規矩可要多注意。");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/danding-dao/kou", me) )
                return "這招我已經教過你了，自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("danding-dao", 1) < 1)
                return "你連丹碇刀法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<80 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-8000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 100)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("danding-dao", 1) < 80)
                return "你的丹碇刀法還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "點了點頭，將$N" HIY "招至身邊，在耳"
                     "旁低聲細説良久，$N" HIY "聽後不禁會心地一笑，看來大"
                     "有所悟。\n\n" NOR, me, this_object());

        command("nod");
        command("say 這招很簡單，稍加練習便行。");
        tell_object(me, HIC "你學會了「環環相扣」。\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("danding-dao"))
                me->improve_skill("danding-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/danding-dao/kou", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}
