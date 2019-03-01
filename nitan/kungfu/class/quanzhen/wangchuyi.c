// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

string ask_me();
mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("王處一", ({"wang chuyi", "wang"}));
        set("gender", "男性");
        set("age", 35);
        set("class", "taoist");
        set("nickname",RED"玉陽子"NOR);
        set("long",
                "他就是全真七子之五王處一王真人。他身材修長，服飾整潔，\n"
                "三綹黑須飄在胸前，神態瀟洒。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 32);
        set("dex", 30);

        set("title","全真七子之五");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 4200);
        set("max_qi", 4200);
        set("jing", 2100);
        set("max_jing", 2100);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 100);

        set("combat_exp", 1200000);

        set_skill("force", 170);
        set_skill("quanzhen-xinfa", 170);
        set_skill("sword", 160);
        set_skill("quanzhen-jian",160);
        set_skill("dodge", 150);
        set_skill("jinyan-gong", 150);
        set_skill("parry", 170);
        set_skill("strike", 170);
        set_skill("chongyang-shenzhang", 170);
        set_skill("haotian-zhang", 170);
        set_skill("literate",100);
        set_skill("finger",150);
        set_skill("zhongnan-zhi", 170);
        set_skill("taoism",100);
        set_skill("medical", 180);
        set_skill("liandan-shu", 180);
        set_skill("cuff",150);
        set_skill("chunyang-quan",150);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike", "haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄門正宗。\n",
                "南帝"   : (: ask_me :),
                "段皇爺" : (: ask_me :),
                "纏字訣" : (: ask_skill1 :),
                "定陽針" : (: ask_skill2 :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 90 )
        {
                command("say 你的本門內功心法火候不足，難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<8000 )
        {
                command("say 我看你還是多做一些俠義之事吧。\n");
                return;
        }
        command("say 好吧，我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

string ask_me()
{
        object me=this_player();

        if( query_temp("tmark/指", me) == 1 )
        {
                addn_temp("tmark/指", 1, me);
                return("去年師傅去過段皇爺那裡，據說段皇爺把他最厲害的一陽指功夫傳授給我師傅了。\n");
        } else
        {
                set_temp("tmark/指", 0, me);
                return("段皇爺遇上了一件大傷心事，現在出家做了和尚了，唉！");
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/quanzhen-jian/chan", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何說起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你連全真劍法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<200 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<10000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("quanzhen-jian", 1) < 80)
                return "你的全真劍法不夠嫻熟，練高點再來吧。";

        if (me->query_skill("force") < 100)
                return "你的內功修為不夠，修煉高後再來找我吧。";

        message_sort(HIY "\n$n" HIY "微笑著點了點頭，說道：“看好了。”說"
                     "罷即抽出腰間長劍，慢慢演示起來。只見$n" HIY "劍招緊"
                     "密圓動，連綿不絕，內力便如細絲般從長劍劍鋒透出，帶出"
                     "陣陣風聲。直看得$N" HIY "目瞪口呆。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 此招無非是以劍招迷惑對手，並無復雜之舉。");
        tell_object(me, HIC "你學會了「纏字訣」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/quanzhen-jian/chan", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/quanzhen-jian/ding", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何說起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你連全真劍法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<12000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("quanzhen-jian", 1) < 100)
                return "你的全真劍法不夠嫻熟，練高點再來吧。";

        if (me->query_skill("force") < 150)
                return "你的內功修為不夠，修煉高後再來找我吧。";

        message_sort(HIY "\n$n" HIY "點了點頭，喝道：“看仔細了。”話音剛"
                     "落，只見$n" HIY "腳下左弓右箭，深深吸入一口氣，神氣"
                     "完足如雷霆五岳，電光火石間一劍斜斜刺出，頓時只聽得“"
                     "哧”的一聲，$N" HIY "腳下的方磚竟然應聲而碎，裂成了"
                     "數塊。\n\n" NOR, me, this_object());

        command("nod");
        command("say 此招的精要無非是以氣駕劍，達至隨心所欲。");
        tell_object(me, HIC "你學會了「定陽針」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/quanzhen-jian/ding", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

int accept_object(object who, object ob)
{
        object obj1,obj2,obj3,obj4;
        object me=this_player();

        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");

        if( query("name", ob) != HIR"熊膽"NOR
                 && query("name", ob) != HIY"田七"NOR
                 && query("name", ob) != HIW"沒藥"NOR
                 && query("name", ob) != RED"血竭"NOR )
                    return 0;

        remove_call_out("destroying");
        call_out("destroying", 1, me, ob);
        message_vision("王處一看了看$N送去的藥，點了點頭道：難為你了，\n"
                       "我可以教你點功夫。\n", who);

        addn_temp("tmark/王", 60, who);
        return 1;
}
