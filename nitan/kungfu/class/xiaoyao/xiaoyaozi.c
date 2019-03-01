// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#define ZHIHUAN    "/clone/unique/zhihuan"

mixed ask_zhihuan();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();

void create()
{
        object ob;
        set_name("逍遙子", ({ "xiaoyao zi", "xiaoyao", "zi" }));
        set("title", "逍遙派開山祖師");
        set("long", @LONG
眼前此人須眉皆白，看不出有多老。他便是逍
遙派開山祖師無崖子。然而似乎身染重疾，行
動不便。雖然如此，從眉宇仍然看得出此人當
年必然是一位風流倜儻的美男子。想不到今天
淪落到這個地步，真是世事難料。
LONG );
        set("gender", "男性");
        set("age", 95);
        set("class", "scholar");
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 36);
        set("int", 41);
        set("con", 37);
        set("dex", 38);

        set("max_qi", 7500);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 5000000);

        set_skill("force", 600);
        set_skill("xiaowuxiang", 600);
        set_skill("beiming-shengong", 600);
        set_skill("dodge", 600);
        set_skill("lingbo-weibu", 600);
        set_skill("feiyan-zoubi", 600);
        set_skill("strike", 600);
        // set_skill("panyang-zhang", 440);
        set_skill("liuyang-zhang", 600);
        set_skill("hand", 600);
        set_skill("qingyun-shou", 600);
        set_skill("zhemei-shou", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("liuyue-jian", 600);
        set_skill("blade", 600);
        set_skill("ruyi-dao", 600);
        set_skill("literate", 800);
        set_skill("medical", 650);
        set_skill("xiaoyao-qixue", 600);
        set_skill("mathematics", 800);
        set_skill("qimen-wuxing", 800);
        set_skill("drawing",   800);
        set_skill("chuixiao-jifa", 600);
        set_skill("tanqin-jifa", 600);
        set_skill("chess", 800);
        set_skill("calligraphy", 800);
        set_skill("construction", 1000);
	set_skill("xiaoyao-you", 800);
        set_skill("martial-cognize", 940);

        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("hand", "zhemei-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "zhemei-jian");
        map_skill("sword", "liuyue-jian");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "zhemei-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("逍遙派", 1, "開山祖師");
        set("class", "taoist");

        set("inquiry", ([
                "流月劍訣"   : (: ask_skill1 :),
                "天升劍訣"   : (: ask_skill2 :),
                "洛神凌波"   : (: ask_skill3 :),
                "生死符"     : (: ask_skill4 :),
                "寰陽式"     : (: ask_skill5 :),
                "折梅式"     : (: ask_skill6 :),
                "海淵式"     : (: ask_skill7 :),
                "化妖功"     : (: ask_skill8 :),
                "逍遙神仙環" : (: ask_zhihuan :),
                "掌門人信物" : (: ask_zhihuan :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhe" :),
                (: perform_action, "hand.hai" :),
                (: perform_action, "hand.hua" :),
                (: perform_action, "dodge.ling" :),
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.zhong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        if (clonep())
        {
                ob = find_object(ZHIHUAN);
                if (! ob) ob = load_object(ZHIHUAN);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wear();
                }
        }

        carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query_temp("pass_zhenlong", ob) )
        {
                int btimes;
                delete_temp("pass_zhenlong", ob);
                if( query("betrayer/times", ob) )
                {
                        command("sigh");
                        command("say 你破了珍瓏，和我是有緣人，可是你"
                                "曾經判師，卻不能收你。");
                        return;
                }

                command("haha");
                command("say 你破了珍瓏，和我是有緣人，我一定要收你為"
                        "徒！");
                btimes=query("betrayer/times", ob);
                command("recruit "+query("id", ob));
                set("betryer/times", btimes, ob);

                if( query("max_neili", ob)<500 )
                {
                        command("say 不過你內力太差…嗯…也好，待我傳功于你！");
                        set("max_neili", 500+random(100), ob);
                        if (ob->query_skill("force", 1) < 50)
                                ob->set_skill("force", 50 + random(10));

                        if (ob->query_skill("beiming-shengong", 1) < 50)
                                ob->set_skill("beiming-shengong", 50 + random(10));

                        message_vision(HIC "$N" HIC "把掌心按在$n" HIC "天靈蓋上，雙眼微"
                                       "閉，手掌不住的顫動，忽的落下，緩緩道：好，好！\n" NOR,
                                       this_object(), ob);
                }

                return;
        }

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("xiaowuxiang", 1) < 130 &&
            (int)ob->query_skill("beiming-shengong", 1) < 130)
        {
                command("say 我逍遙派的本門內功的你都沒有學利索，還談什麼？");
                return;
        }

        if ((int)ob->query_skill("force", 1) < 130)
        {
                command("say 我逍遙派的的武功基礎就是內功，你先把內功基礎打好。");
                return;
        }

        if ((int)ob->query_skill("dodge", 1) < 130)
        {
                command("say 逍遙逍遙，你輕功基礎這麼差，何談逍遙？");
                return;
        }

        if (ob->query_int() < 40)
        {
                command("say 我逍遙講究的就是悟，但是" + RANK_D->query_respect(ob) +
                        "的悟性似乎還有待提高啊。");
                return;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("say 你的經驗也忒低了點，好好鍛煉鍛煉再說吧。");
                return;
        }

        command("haha");
        command("say 想不到在這世上竟然還有人可以繼承我逍遙派的衣砵！");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyue-jian/liu", me) )
                return "我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("liuyue-jian", 1) < 1)
                return "你連流月劍舞都未曾學過，何來絕招？";

        if( query("family/gongji", me)<400 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("liuyue-jian", 1) < 120)
                return "你的流月劍舞火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "點了點頭，從懷中輕輕取出了一本"
                       "劍譜，指著其中的一段對\n$N" HIY "不厭其煩的"
                       "細說良久，$N" HIY "一邊聽一邊點頭。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 這招的變化看似很煩瑣，其實不難，多練習便成。");
        tell_object(me, HIC "你學會了「流月劍訣」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("liuyue-jian"))
                me->improve_skill("liuyue-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyue-jian/liu", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyue-jian/sheng", me) )
                return "我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("liuyue-jian", 1) < 1)
                return "你連流月劍舞都未曾學過，何來絕招？";

        if( query("family/gongji", me)<500 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("liuyue-jian", 1) < 140)
                return "你的流月劍舞火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "笑了笑，當即從$N" HIY "手中接過"
                       "長劍，慢慢的演示劍招，$N" HIY "見招\n式優美華"
                       "麗，輕盈靈動，實乃前所謂聞，頓時大有所悟。\n"
                       NOR, me, this_object());

        command("say 這招的關鍵在于靈動二字，你下去練吧。");
        tell_object(me, HIC "你學會了「天升劍訣」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("liuyue-jian"))
                me->improve_skill("liuyue-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyue-jian/sheng", 1, me);
        addn("family/gongji", -500, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/lingbo-weibu/ling", me) )
                return "我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("lingbo-weibu", 1) < 1)
                return "你連凌波微步都未曾練過，何來洛神凌波？";

        if( query("family/gongji", me)<600 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("lingbo-weibu", 1) < 120)
                return "你的凌波微步火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "對$N" HIY "微笑道：“想不到"
                       "今日你的輕功能有如此造詣，我便傳\n你此招"
                       "，看好了！”說完只見$n" HIY "提起真氣，依"
                       "照先天伏羲六十\n四卦將凌波微步由頭到尾迅"
                       "速無比的走了一次。但見$n" HIY "意態飄\n逸"
                       "，影子亂飛，真個將逍遙二字發揮得淋漓盡至"
                       "。\n" NOR, me, this_object());

        command("haha");
        command("say 你看懂了多少？");
        tell_object(me, HIC "你學會了「洛神凌波」。\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("lingbo-weibu"))
                me->improve_skill("lingbo-weibu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingbo-weibu/ling", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/zhong", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你連天山六陽掌都未曾學過，何來絕招？";

        if( query("family/gongji", me)<600 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("liuyang-zhang", 1) < 150)
                return "你的天山六陽掌火候未到，尚且學不了這一招。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微微一笑，隨即"
                       "便點了點頭，將$N" HIY "招至身邊，在\n耳旁低聲"
                       "細說良久，$N" HIY "聽後會心的一笑，看來大有所"
                       "悟。\n" NOR, me, this_object());

        command("haha");
        command("say 對付那些不肯降服之人，用這招最合適不過。");
        tell_object(me, HIC "你學會了「生死符」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/zhong", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/huan", me) )
                return "這招我不是已經教會你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你連天山六陽掌都未曾學過，何來絕招？";

        if( query("family/gongji", me)<900 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("liuyang-zhang", 1) < 130)
                return "你的天山六陽掌火候未到，尚且學不了這一招。";

        message_vision(HIY "$n" HIY "微微一笑，慢悠悠伸出一掌，正搭"
                       "在$N" HIY "的左肩之上，$N" HIY "稍作\n詫異，"
                       "霎時只覺$n" HIY "內力源源不絕的洶湧而入，異"
                       "種真氣注滿體\n內，全身竟似快要炸裂開來，不禁"
                       "大驚失色。\n" NOR, me, this_object());

        command("say 你懂了嗎？");
        tell_object(me, HIC "你學會了「寰陽式」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/huan", 1, me);
        addn("family/gongji", -900, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/zhe", me) )
                return "這招我不是已經教會你了嗎？";

/*
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";
*/

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你連逍遙折梅手都未曾學過，何來絕招？";

        if( query("family/gongji", me)<400 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("zhemei-shou", 1) < 80)
                return "你的逍遙折梅手火候未到，尚且學不了這一招。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微微一笑。當下"
                       "一聲清嘯，合逍遙折梅手諸多變\n化為一式，隨手"
                       "輕輕揮出，招數虛虛實實，煞是精妙。直看得$N"
                       HIY "眼\n花繚亂，目瞪口呆。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 招式便是如此，剩下的就靠你自己了。");
        tell_object(me, HIC "你學會了「折梅式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/zhe", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hai", me) )
                return "這招我不是已經教會你了嗎？";

/*
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";
*/

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你連逍遙折梅手都未曾學過，何來絕招？";

        if( query("family/gongji", me)<900 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("zhemei-shou", 1) < 130)
                return "你的逍遙折梅手火候未到，尚且學不了這一招。";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，當下也不答"
                       "話，單手輕輕一揮而出，手出如\n風，單掌頓時變"
                       "化出漫天掌影，虛虛實實，重重疊疊，霎那間已罩"
                       "\n住$N" HIY "周身穴道，$n" HIY "那掌影卻只是"
                       "一沾而過，未傷$N" HIY "半毫。招數\n之巧妙，當"
                       "真只能用“無可比擬”四字形容。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 此招便如海之浩瀚，淵之深絕，可要勤加練習。");
        tell_object(me, HIC "你學會了「海淵式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hai", 1, me);
        addn("family/gongji", -900, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hua", me) )
                return "你自己下去練習吧。";

/*
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";
*/

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你連逍遙折梅手都未曾學過，何來絕招？";

        if( query("family/gongji", me)<2500 )
                return "你雖在我逍遙門下，卻甚無作為，這招我先不忙傳你。";

        if ((int)me->query_skill("beiming-shengong", 1) < 220)
                return "你的北冥神功火候不足，學不成這招。";

        if (me->query_skill("zhemei-shou", 1) < 220)
                return "你的逍遙折梅手火候未到，尚且學不了這一招。";

        if( query("max_neili", me)<3500 )
                return "你的內力修為不夠，強運這招會擾亂自身的真元。";

        message_vision(HIY "$n" HIY "對$N" HIY "微微一笑，模樣頗為讚"
                       "許，說道：“我在這裡給你演示\n一遍，能否領悟"
                       "就全靠你的悟性了。”話音剛落，只見$n" HIY "起"
                       "身\n而立，大袖一揮，掌緣頓時幻起萬道霞光，$n"
                       HIY "翻過掌心，掌中\n霞光也隨之盪漾。$n" HIY
                       "接著催動內力，霎那間，掌中霞光竟由紫\n變紅，"
                       "由紅轉白……竟接連幻出七種顏色，便宛如一道彩"
                       "虹橫架于\n掌心之上。此時，$n" HIY "一聲斷喝，"
                       "七色掌勁相繼迸出掌心。只聽\n得“哧哧哧哧哧哧"
                       "哧”七聲連響，$N" HIY "對面的石壁竟被$n" HIY
                       "的七色\n掌勁貫穿出七個碗口粗的深穴。\n" NOR,
                       me, this_object());

        command("haha");
        command("say 這招乃是我畢生精力所創，剛才不過是一成的威力罷了。");
        command("say 非到性命不保，絕不可輕易施展此招。");
        tell_object(me, HIC "你學會了「化妖功」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hua", 1, me);
        addn("family/gongji", -2500, me);
        return 1;

}

mixed ask_zhihuan()
{
        int cost;
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "逍遙派" )
                return "給我滾開！";

        if( query("family/master_id", me) != query("id") )
                return "你還不配！";

        if (me->query_skill("zhemei-shou", 1) < 200 &&
           me->query_skill("liuyang-zhang", 1) < 200)
                return "你拿去也沒用。";

        if( query("family/first", me) ) cost = 250;
        else cost = 500;

        if( query("family/gongji", me) < cost )
                return "你為逍遙派所做的貢獻不夠，逍遙神仙環我不能給你。\n";

        ob = find_object(ZHIHUAN);
        if (! ob) ob = load_object(ZHIHUAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "本門的信物不就在你手中嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了，逍遙神仙環現在不在我手中。";

                if( query("family/family_name", owner) == "逍遙派" )
                        return "逍遙神仙環現在落在本派"+query("name", owner)+
                               "手中，你要用就去找他吧。";
                else
                        return "我正為此事擔憂呢，本門信物現在落入了"+query("name", owner)+
                               "之手，你趕快去把他殺了，把指環取回來！";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "微微一笑，道：“這逍遙神仙環你便拿去，希"
                       "望日後你能繼承我的衣砵。”\n" NOR, this_object(), me);
        command("give shenxian huan to "+query("id", me));
        addn("family/gongji", -cost, me);

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "灰飛煙滅" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/hui",
                           "name"    : "灰飛煙滅",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 150,
                           "sk2"     : "liuyang-zhang",
                           "lv2"     : 150,
                           "neili"   : 2000,
                           "gongxian": 1000, ]));
                break;

        case "九部式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/jiubu",
                           "name"    : "九部式",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "free"    : 1,
                           "gongxian": 1000, ]));
                break;

        case "空手入白刃" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/duo",
                           "name"    : "空手入白刃",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "free"    : 1,
                           "neili"   : 1400, ]));
                break;

        case "白虹掌力" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/baihong",
                           "name"    : "白虹掌力",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 100,
                           "free"    : 1,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000, ]));
                break;

        case "九天式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/jiutian",
                           "name"    : "九天式",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "free"    : 1,
                           "gongxian": 600,
                           "neili"   : 1400, ]));
                break;

        case "神光離合" :
               return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/lingbo-weibu/shen",
                               "name"    : "神光離合",
                             "sk1"     : "lingbo-weibu",
                               "lv1"     : 220,
                             "sk2"     : "dodge",
                            "free"    : 1,
                             "lv2"     : 320,
                             "gongxian": 1600,
                             "neili"   : 1400, ]));
                  break;
        case "破神訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/po",
                           "name"    : "破神訣",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "free"    : 1,
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1400, ]));
                break;

        default:
                return 0;
        }
}
