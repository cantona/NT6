#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_me();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

void create()
{
        set_name("桑三娘", ({ "sang sanniang", "sang", "sanniang"}));
        set("title", "日月神教天香堂長老");
        set("nickname", HIR "掌刑使者" NOR);
        set("long", @LONG
這是日月神教天香堂香主桑三娘。只見她神情
古怪，面無絲毫微笑，面容卻相當清秀。
LONG);
        set("gender", "女性" );
        set("class", "scholar");
        set("age", 41);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 36);
        set("int", 36);
        set("con", 36);
        set("dex", 36);
        
        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 5400);
        set("max_neili", 5400);
        set("jiali", 150);
        set("combat_exp", 2000000);
        set("score", 10000);

        set_skill("force", 180);
        set_skill("riyue-xinfa", 180);
        set_skill("tianhuan-shenjue", 180);
        set_skill("dodge", 200);
        set_skill("feiyan-zoubi", 200);
        set_skill("juechen-shenfa", 200);
        set_skill("dagger", 180);
        set_skill("jifeng-cixuefa", 180);
        set_skill("hand", 200);
        set_skill("lansha-shou", 200);
        set_skill("strike", 160);
        set_skill("qingmang-zhang", 160);
        set_skill("cuff", 140);
        set_skill("zhenyu-quan", 140);
        set_skill("claw", 140);
        set_skill("poyue-zhao", 140);
        set_skill("parry", 180);
        set_skill("throwing", 200);
        set_skill("heixue-shenzhen", 200);
        set_skill("martial-cognize", 180);
        set_skill("literate", 220);

        map_skill("dodge", "juechen-shenfa");
        map_skill("force", "tianhuan-shenjue");
        map_skill("dagger", "jifeng-cixuefa");
        map_skill("hand", "lansha-shou");
        map_skill("parry", "lansha-shou");
        map_skill("strike", "qingmang-zhang");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");
        map_skill("throwing", "heixue-shenzhen");

        prepare_skill("hand", "lansha-shou");

        set("no_teach", ([
                "tianhuan-shenjue" : "這門內功你還是去讓其他長老教你吧。",
        ]));

        create_family("日月神教", 13, "天香堂長老");

        set("inquiry", ([
                "黑血神針" : (: ask_me :),
                "破靛神砂" : (: ask_skill1 :),
                "星羅棋佈" : (: ask_skill2 :),
                "天蠍藏針" : (: ask_skill3 :),
        ]));

        set("zhen_count", 3);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.po" :),
                (: perform_action, "throwing.luo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set("master_ob",3);
        setup();

        carry_object("/d/heimuya/npc/obj/jinpao")->wear();
        set_temp("handing", carry_object("/d/heimuya/npc/obj/shenzhen"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-15000 )
        {
                command("sneer");
                command("say 你為人如此正直，幹嘛又來我日月神教？");
                return;
        }

        if( query("combat_exp", ob)<100000 )
        {
                command("say 你現在江湖經驗太淺，還應該多走動走動。");
                return;
        }

        if (ob->query_skill("tianhuan-shenjue", 1) < 50
           && ob->query_skill("riyue-xinfa", 1) < 50)
        {
                command("hmm");
                command("say 你怎麼連本門最基本的內功都沒學好？");
                return;
        }

        command("say 。……嗯……那你就跟着我吧。");
        command("say 日月神教內規矩眾多，可少給我惹事。");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_me()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != query("family/family_name") )
                return "給我滾開！少在我面前羅嗦。";

        if( query("shen", me)>-30000 )
                return "像你這樣心慈手軟，拿了這神針去也沒什麼用。";

        if ((int)me->query_skill("heixue-shenzhen", 1) < 140)
                return "你黑血神針的手法還不到家，拿了這神針去也沒什麼用。";

        if (query("zhen_count") < 1)
                return "我又不是賣這個的，哪裏帶得了那麼多。";

        addn("zhen_count", -1);
        ob = new("/d/heimuya/npc/obj/shenzhen");
        message_vision("$N拿出五十根" WHT "黑血神針" NOR "(Heixue shenzhen)給$n。\n",
                       this_object(), me);
        ob->move(me, 1);
        return "我這兒的黑血神針你先拿去用吧。";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/lansha-shou/po", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("lansha-shou", 1) < 1)
                return "你連藍砂手都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-20000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 150)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("lansha-shou", 1) < 100)
                return "你的藍砂手還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "對$N" HIY "笑了笑，也不答話，突然"
                     "間身形急轉，宛若鬼魅，悄然伸出五指朝$N" HIY "胸前"
                     "抓落，$N" HIY "見狀大驚失色，連忙騰挪閃躲，可已然"
                     "不及。$n" HIY "五指正好拂在$N" HIY "的胸前。\n\n"
                     NOR, me, this_object()); 

        command("haha");
        command("say 這式手法用來暗算或是偷襲再合適不過。");
        tell_object(me, HIC "你學會了「破靛神砂」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("lansha-shou"))
                me->improve_skill("lansha-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lansha-shou/po", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/heixue-shenzhen/luo", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("heixue-shenzhen", 1) < 1)
                return "你連黑血神針都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-35000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 200)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("heixue-shenzhen", 1) < 140)
                return "你的黑血神針還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "陰陰一笑，將$N" HIY "招至跟前，輕"
                     "聲在耳旁祕密説了些什麼。隨後又伸出右手，十指箕張"
                     "，一伸一縮，看樣子是一種很特別的暗器法門。\n\n"
                     NOR, me, this_object()); 

        command("nod");
        command("say 剛才我説的全是精要，你可要記清楚了。");
        tell_object(me, HIC "你學會了「星羅棋佈」。\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("heixue-shenzhen"))
                me->improve_skill("heixue-shenzhen", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/heixue-shenzhen/luo", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/jifeng-cixuefa/cang", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑來搗什麼亂？";

        if (me->query_skill("jifeng-cixuefa", 1) < 1)
                return "你連疾風刺穴法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "你在教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)>-15000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 120)
                return "你的內功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("dodge") < 120)
                return "你的輕功火候尚需提高，練好了再來找我吧。";

        if (me->query_skill("jifeng-cixuefa", 1) < 100)
                return "你的疾風刺穴法還練得不到家，自己下去練練再來吧！";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，隨即便從$N"
                     HIY "的手中接過匕首，一聲叱喝，連環刺出五招，只"
                     "見這五刺連環攻勢凌厲之極，招數層出不窮，當真精"
                     "妙無比。\n\n" NOR, me, this_object()); 

        command("nod");
        command("say 這招的要點不過一個疾字，其實是很簡單的招式。");
        tell_object(me, HIC "你學會了「天蠍藏針」。\n" NOR);
        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("jifeng-cixuefa"))
                me->improve_skill("jifeng-cixuefa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jifeng-cixuefa/cang", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}
