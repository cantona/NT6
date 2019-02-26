// This program is a part of NT MudLIB
// wang.c

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();
mixed  ask_skill5();
mixed  ask_skill6();
string ask_jiuyin();
string ask_duan();
string ask_zhipu();

void create()
{
        set_name("王重陽", ({ "wang chongyang", "wang", "chongyang" }));
        set("long", @LONG
他就是全真教的開山祖師、首代掌教王重陽王
真人。他白鬚飄飄，寬袍緩袖，眉目清癯，頗
有些仙風道骨的味道。他本來一腔熱血欲報效
國家力抗金兵，可惜朝廷腐敗，於是便心灰意
冷，兼此時又從道德經中悟得了天地萬物滋生
的大道，從而手創全真教。
LONG);
        set("title", "全真派開山祖師");
        set("nickname", HIW "中神通" NOR);
        set("age", 76);
        set("gender", "男性");
        set("class", "taoist");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);
        set("max_qi", 8000);
        set("max_jing", 8000);
        set("neili", 10000);
        set("jingli", 8000);
        set("max_neili", 10000);
        set("max_jingli", 8000);
        set("jiali", 250);
        set("level", 70);
        set("combat_exp", 8000000);
        set("no_get", 1);

        set_skill("force", 650);
        set_skill("quanzhen-jianzhen", 800);
        set_skill("array", 800);
        set_skill("quanzhen-xinfa", 700);
        // set_skill("xuanmen-neigong", 380);
        set_skill("unarmed", 700);
        set_skill("xiantian-gong", 650);
        set_skill("dodge", 700);
        // set_skill("tianshan-feidu", 360);
        set_skill("jinyan-gong", 700);
        set_skill("parry", 700);
        set_skill("jinguan-yusuo", 700);
        set_skill("strike", 700);
        set_skill("chongyang-shenzhang", 660);
        set_skill("haotian-zhang", 700);
        set_skill("finger", 700);
        set_skill("zhongnan-zhi", 660);
        set_skill("sun-finger", 700);
        // set_skill("qixing-shou", 380);
        set_skill("sword", 700);
        // set_skill("qixing-jian", 360);
        // set_skill("tonggui-jian", 360);
        set_skill("quanzhen-jian", 700);
        // set_skill("tiangang-chenfa", 340);
        set_skill("taoism", 650);
        set_skill("literate", 650);
        set_skill("huajia-su", 700);
        set_skill("martial-cognize", 650);
        set_skill("medical", 680);
        set_skill("liandan-shu", 680);
        set_skill("cuff",680);
        set_skill("whip",680);
        set_skill("chunyang-quan",680);
        set_skill("duanyun-bian",680);
        set_skill("array",650);
        set_skill("beidou-zhenfa", 650);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        // map_skill("whip", "tiangang-chenfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "haotian-zhang");
        map_skill("unarmed", "xiantian-gong");
        map_skill("finger", "sun-finger");
        map_skill("strike", "haotian-zhang");
        // map_skill("hand", "qixing-shou");
        map_skill("cuff",   "chunyang-quan");
        map_skill("whip",   "duanyun-bian");
        prepare_skill("unarmed", "xiantian-gong");

        set("no_teach/sun-finger", "一陽指乃是段家祕傳，我不能教你。");

        create_family("全真教", 1, "掌教");

        set("inquiry", ([
                "全真教"     : "我全真教是天下道家玄門正宗。",
                "絕招"       : "你想學什麼絕招？",
                "絕技"       : "你想學什麼絕招？",
                "九陰真經"   : (: ask_jiuyin :),
                "段皇爺"     : (: ask_duan :),
                "五氣朝元"   : (: ask_skill1 :),
                "一氣化三清" : (: ask_skill2 :),
                "化三清"     : (: ask_skill2 :),
                "天地混元"   : (: ask_skill3 :),
                "五陰焚滅"   : (: ask_skill4 :),
                "神威浩蕩"   : (: ask_skill5 :),
                "三連環"     : (: ask_skill6 :),
                "一陽指"     : (: ask_zhipu :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.hun" :),
                (: perform_action, "unarmed.fen" :),
                (: perform_action, "unarmed.dang" :),
                (: perform_action, "unarmed.jian" :),
                (: perform_action, "parry.suo" :),
                (: exert_function, "hup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(__DIR__"obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 35)
        {
                command("say 你的悟性還不夠，還是先找我那幾個徒弟學習吧。");
                return;
        }


        if ((int)ob->query_skill("xiantian-gong", 1) < 120
           && (int)ob->query_skill("quanzhen-xinfa", 1) < 120)
        {
                command("say 你的本門內功心法火候不足，只怕難以"
                        "領略更高深的武功。");
                return;
        }

        if( query("combat_exp", ob)<480000 )
        {
                command("say 你的實戰經驗太差，看來難以領略更高深的武功。");
                return;
        }

        if( query("shen", ob)<80000 )
        {
                command("say 行俠仗義是我輩學武人的宗旨，你多做些俠"
                        "義之事，我方能收你為徒。");
                return;
        }
        command("say 不錯，以你資質定可傳我衣缽！我就收下你這個徒弟了。");
        command("recruit "+query("id", ob));
}


mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/hup", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你連先天功都沒學，何談絕招可言？";

        if( query("family/gongji", me)<800 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<100000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("xiantian-gong", 1) < 200)
                return "你先天功的修為不夠，還是練高了再來吧。";

        if( query("max_neili", me)<2000 )
                return "你的內力修為仍不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，從懷中輕輕取出了一本"
                     "小冊子，指着其中的一段對$N" HIY "細説良久，$N"
                     HIY "一邊聽一邊點頭。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 你自己下去練吧。");
        tell_object(me, HIC "你學會了「五氣朝元」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/hup", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/quanzhen-jian/hua", me) )
                return "你全真劍法已達如此造詣，我已沒什麼可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你連全真劍法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<1600 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<100000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("quanzhen-jian", 1) < 200)
                return "你對我派劍法的瞭解還不夠透徹，研究透了再來找我吧。";

        if (me->query_skill("xiantian-gong", 1) < 100 &&
            me->query_skill("quanzhen-xinfa", 1) < 100)
                return "你全真的內功的修為不夠，還是練高了再來吧。";

        if( query("max_neili", me)<4800 )
                return "你的內力修為仍不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，隨手從道袍上撕下一角布"
                     "條，內力吞吐間，只見那布條登時變得如同堅鐵，伸手"
                     "刺處，變幻無方，宛若三把長劍齊出，招式當真絕妙無"
                     "比。只看得$N" HIY "目瞪口呆。\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say 你自己下去揣摩吧，切記莫走進邪魔歪道！");
        tell_object(me, HIC "你學會了「一氣化三清」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        /*
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        */
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/quanzhen-jian/hua", 1, me);
        addn("family/gongji", -1600, me);

        return 1;
}

mixed ask_skill6()
{
        object me;
        me = this_player();

        if( query("can_perform/quanzhen-jian/lian", me) )
                return "你全真劍法已達如此造詣，我已沒什麼可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你連全真劍法都沒學，何談絕招可言？";

        if( query("family/gongji", me)<1600 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<100000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("quanzhen-jian", 1) < 200)
                return "你對我派劍法的瞭解還不夠透徹，研究透了再來找我吧。";

        if (me->query_skill("quanzhen-xinfa", 1) < 100)
                return "你全真心法的修為不夠，還是練高了再來吧。";

        if( query("max_neili", me)<4800 )
                return "你的內力修為仍不足，還是練高點再來吧。";

        command("haha");
        command("say 你自己下去揣摩吧，切記莫走進邪魔歪道！");
        tell_object(me, HIC "你學會了「三連環絕技」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("quanzhen-xinfa"))
                me->improve_skill("quanzhen-xinfa", 1800000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/quanzhen-jian/lian", 1, me);
        addn("family/gongji", -1600, me);

        return 1;
}


mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/hun", me) )
                return "這招你不是已經學會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你連先天功都沒學，何談絕招可言？";

        if( query("family/gongji", me)<1800 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<120000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("xiantian-gong", 1) < 200)
                return "你先天功的修為不夠，還是練高了再來吧。";

        if( query("max_neili", me)<6800 )
                return "你的內力修為仍不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，對$N" HIY "説道：“你的"
                     "先天功達此境界，實屬不凡，今日為師傳你這招又有何"
                     "妨？”説罷$n" HIY "便擺開架勢，慢慢地演示招數。\n"
                     "\n" NOR, me, this_object());

        command("nod");
        command("say 招式便是如此，能否領悟就靠你自己了。");
        tell_object(me, HIC "你學會了「天地混元」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/hun", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/fen", me) )
                return "這招你不是已經學會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你連先天功都沒學，何談絕招可言？";

        if( query("family/gongji", me)<2000 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<130000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("xiantian-gong", 1) < 240)
                return "你先天功的修為不夠，還是練高了再來吧。";

        if( query("max_neili", me)<6800 )
                return "你的內力修為仍不足，還是練高點再來吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，對$N" HIY "説道：“難得"
                     "你有如此造詣，今日師父就傳你這招，可看好了！”$n"
                     HIY "隨即一聲清哮，全身真氣急速運轉，引得周圍氣流"
                     "波動不已。左掌微微一抖，先天真氣隨招式而盪漾，激"
                     "起千層氣浪，威力之強，當可用驚天地、泣鬼神來描述"
                     "，直看得$N" HIY "目瞪口呆。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 招式便是如此，你自己下去練吧。");
        tell_object(me, HIC "你學會了「五陰焚滅」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/fen", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/dang", me) )
                return "這招你不是已經學會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "閣下與貧道素不相識，不知此話從何説起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你連先天功都沒學，何談絕招可言？";

        if( query("family/gongji", me)<2800 )
                return "你在我全真教內甚無作為，這招我暫時還不能傳你。";

        if( query("shen", me)<180000 )
                return "你的俠義正事還做得不夠，這招我暫時還不能傳你。";

        if (me->query_skill("xiantian-gong", 1) < 240)
                return "你先天功的修為不夠，還是練高了再來吧。";

        if( query("max_neili", me)<8000 )
                return "你的內力修為仍不足，還是練高點再來吧。";

        if( !query("can_perform/xiantian-gong/fen", me) )
                return "此招乃是由「五陰焚滅」昇華而來，你還是逐步學習吧？";

        message_sort(HIY "\n$n" HIY "微微點了點頭，隨手搭在$N" HIY "的"
                     "肩上，突然$N" HIY "陡覺全身筋脈劇震，內息澎湃洶湧"
                     "之極，猶如江河絕堤，便欲衝關破出一般，不由大驚。"
                     "\n\n" NOR, me, this_object());

        command("haha");
        command("say 你可明白了？");
        tell_object(me, HIC "你學會了「神威浩蕩」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/dang", 1, me);
        addn("family/gongji", -2800, me);

        return 1;
}

string ask_jiuyin()
{
        mapping fam;
        int lvl_force;

        if( !(fam=query("family", this_player()) )
            || fam["family_name"] != "全真教")
                return RANK_D->query_respect(this_player()) +
                "與本教毫無瓜葛，這話從何説起？";
        if (!(lvl_force = this_player()->query_skill("force", 1))
            || lvl_force < 50)
                return RANK_D->query_respect(this_player()) +
                "的基本內功火候如此之淺，強練真經上的上乘武功有害無益。";
        return "九陰真經是天下武學正宗，我已交給我師弟周伯通保管。";
}

string ask_duan()
{
        object me=this_player();
        if( query_temp("tmark/指", me) == 2 )
        {
                addn_temp("tmark/指", 1, me);
                return("段皇爺號稱‘南帝’，家傳的一陽指是天下最厲害的指法。\n");
        }
        else {
                set_temp("tmark/指", 0, me);
                return("你問段皇爺做甚麼，莫非想與他為難？\n");
        }
}

string ask_zhipu()
{
        object ob,me=this_player();
        if( query_temp("tmark/指", me) == 3 )
        {
                set_temp("tmark/指", 0, me);
                if(query("book_count")>0)
        {
                        ob=new(BOOK_DIR"sun_book");
                        ob->move(me);
                        addn("book_count",-1);
                        message("channel:rumor",MAG"【謠言】某人："+query("name", this_player())+"拿了一陽指訣啦。\n"NOR,users());
                        return("好吧，你歷經艱苦，意志甚堅，這本指法譜就交給你了。\n");
                }
                else return("你來晚了，指法譜已經被人取走了。\n");
        }
        else {
                set_temp("tmark/指", 0, me);
                return  RANK_D->query_respect(me) + "不是想跟我較量較量吧？\n";
        }
}

int accept_ask(object me, string topic) 
{ 
        switch (topic) 
        { 
        case "歷練" : 
        case "歷煉" : 
        case "鍛鍊" : 
                return QUEST_D->accept_ask(this_object(), me, topic); 
                break; 
        case "先天罡氣" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/xiantian-gong/xian", 
                                "name"    : "先天罡氣",
                                "sk1"     : "xiantian-gong", 
                                "lv1"     : 1000, 
                                "sk2"     : "unarmed", 
                                "lv2"     : 1000, 
                                "sk3"     : "force",
                                "lv3"     : 1000, 
                                "reborn"  : 1,
                                "gongxian": 3000, ])); 
                break; 
       case "日月無光" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                            ([ "perform" : "can_perform/duanyun-bian/guang", 
                       "name"    : "日月無光",
                 "sk1"     : "duanyun-bian", 
                  "lv1"     : 120, 
                 "neili"   : 1400, 
                    "shen"    : 24000, ])); 
                break; 
        case "斷雲助日" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/duanyun-bian/duan", 
                        "name"    : "斷雲助日",
                  "sk1"     : "duanyun-bian", 
                   "lv1"     : 220, 
                  "neili"   : 2400, 
                  "gongxian"   : 1400, 
                              "shen"    : 44000, ])); 
                 break; 
        case "風雲變色" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/duanyun-bian/bian", 
                        "name"    : "風雲變色",
        "sk1"     : "duanyun-bian", 
         "lv1"     : 320, 
        "neili"   : 4400, 
            "gongxian"   : 2400, 
                                "shen"    : 44000, ])); 
                 break; 
                return 0; 
        } 
} 

/*
void unconcious()
{
        die();
}
*/
