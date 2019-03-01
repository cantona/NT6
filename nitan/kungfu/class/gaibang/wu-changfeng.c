#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include "fight.h"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("吳長風", ({ "wu changfeng", "wu", "changfeng" }));
        set("long", @LONG
吳長風乃丐幫元老，武功甚為了得。
LONG);
        set("nickname", HIR "大勇長老" NOR);
        set("title", "丐幫九袋長老");
        set("gender", "男性");
        set("age", 45);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4200);
        set("max_jing", 3200);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 300000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 180);
        set_skill("cuff", 180);
        set_skill("changquan", 180);
        set_skill("jueming-tui", 180);
        set_skill("strike", 240);
        set_skill("xiaoyaoyou", 220);
        set_skill("parry", 220);
        set_skill("staff", 180);
        set_skill("fengmo-zhang", 180);
        set_skill("blade", 240);
        set_skill("liuhe-zhang", 240);
        set_skill("liuhe-dao", 240);
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("martial-cognize", 220);

        map_skill("force", "huntian-qigong");
        map_skill("cuff", "changquan");
        map_skill("strike", "liuhe-zhang");
        map_skill("staff", "jiaohua-bangfa");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("strike", "liuhe-zhang");

        create_family("丐幫", 18, "長老");

        set("inquiry", ([
                "烏龍探海" : (: ask_skill1 :),
                "閃刀訣"   : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.shan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(__DIR__"obj/guitou-blade")->wield();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<120000 )
        {
                command("say 你的江湖經驗不夠，還是先向其他師父學習吧。");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say 你身為丐幫弟子，竟然不做好事？");
                return;
        }

        if( query("family/beggarlvl", ob)<4 )
        {
                command("say 你在本幫的地位太低，還是先向其他師父學習吧。");
                return;
        }

        if (ob->query_skill("force") < 90)
        {
                command("say 你的內功火候還不夠，還是先向其他師父學習吧。");
                return;
        }
        command("nod");
        command("say 我便收下你，希望日後努力上進，能有所作為。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/liuhe-zhang/tan", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何說起？";

        if (me->query_skill("liuhe-zhang", 1) < 1)
                return "你連六合掌法都未曾學過，哪裡來絕招？";

        if( query("family/gongji", me)<50 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<3000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("liuhe-zhang", 1) < 60)
                return "你的六合掌法火候未到，還得多練習練習。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，也不答話，忽然間單掌颼"
                     "的探出，正向$N" HIY "胸前拍落。$N" HIY "登時大驚"
                     "失色，急忙向後躍開數尺，可已然不及，$n" HIY "的"
                     "單掌正搭在$N" HIY "的胸部左側，招術甚為奇巧。\n"
                     "\n" NOR, me, this_object());

        if( query("gender", me) == "女性" )
        {
                command("ah");
                command("say …對…對不住…我…我忘了你是女的。");
        } else
                command("haha");

        command("say 招式便是如此，自己下去練習吧。");
        tell_object(me, HIC "你學會了「烏龍探海」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuhe-zhang"))
                me->improve_skill("liuhe-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuhe-zhang/tan", 1, me);
        addn("family/gongji", -50, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/liuhe-dao/shan", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與在下素不相識，不知此話從何說起？";

        if (me->query_skill("liuhe-dao", 1) < 1)
                return "你連六合刀法都未曾學過，哪裡來絕招？";

        if( query("family/gongji", me)<200 )
                return "你在我們丐幫內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<5000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("liuhe-dao", 1) < 80)
                return "你的六合刀法火候未到，還得多練習練習。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "笑了笑，拔出腰間佩刀"
                     "握在手中，說道：“這六合刀法的要訣不過是展、抹"
                     "、鉤、剁、砍、劈六勢，看好了。”說完便只見$n" HIY
                     "手中鋼刀吞吐不定，形若遊龍，勢如猛虎。接連變換"
                     "了數種方位，最後只聽哧的一聲砍落，刀身震得嗡嗡"
                     "直響。\n" NOR, me, this_object());

        command("nod");
        command("say 只要掌握了四象六合的方位，這招便不難練習。");
        tell_object(me, HIC "你學會了「閃刀訣」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("liuhe-dao"))
                me->improve_skill("liuhe-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuhe-dao/shan", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}
