// This program is a part of NT MudLIB
// huang.c 黃藥師

#include <ansi.h>
#include "taohua.h"

#define TAOHUA    "/clone/book/taohua"
#define XIAOPU    "/clone/book/xiaopu"
#define XUANFENG  "/clone/book/xuanfengtui"
//#define YUXIAO    "/clone/unique/yuxiao"
#define YUXIAO    "/clone/lonely/yuxiao"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_QUESTER;

void   consider();
int    ask_shagu();

mixed  ask_leave();
mixed  ask_book1();
mixed  ask_book2();
mixed  ask_book3();
mixed  ask_book4();
mixed  ask_yuxiao();

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();
mixed  ask_skill5();
mixed  ask_skill6();
mixed  ask_skill7();
mixed  ask_skill8();
mixed  ask_skill9();
mixed  ask_skill10();
mixed  ask_skill11();

mixed  try_to_learn_bibai();
mixed  try_to_learn_count();

string* xuedao = ({
        "風池穴", "風府穴", "強間穴", "大椎穴", "至陽穴",
        "百會穴", "靈台穴", "太陽穴", "膻中穴", "命門穴",
});

void create()
{
        object ob;
        set_name("黃藥師", ({"huang yaoshi", "huang", "yaoshi"}));
        set("title", "東海桃花島島主");
        set("nickname", HIC "東邪" NOR );
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是桃花島主。行事好惡全由己心，因此被\n"
                    "人稱作「東邪」。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("qi", 7000);
        set("max_qi", 7000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("level", 60);
        set("combat_exp", 4000000);

        set_skill("force", 600);
        set_skill("bibo-shengong", 600);
        set_skill("hand", 620);
        set_skill("finger", 600);
        set_skill("tanzhi-shentong", 600);
        set_skill("unarmed", 600);
        set_skill("strike", 600);
        set_skill("luoying-shenzhang", 600);
        set_skill("xuanfeng-tui", 600);
        set_skill("dodge", 600);
        set_skill("luoying-shenfa", 620);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("throwing", 600);
        set_skill("luoying-shenjian", 600);
        set_skill("yuxiao-jianfa", 600);
        set_skill("lanhua-shou", 600);
        set_skill("whip", 600);
        set_skill("canglang-bian", 600);
        set_skill("qimen-wuxing", 2100);
        set_skill("count", 2100);
        set_skill("mathematics", 2100);
        set_skill("literate", 2100);
        set_skill("chuixiao-jifa", 600);
        set_skill("bihai-chaosheng", 600);
        set_skill("taohua-yuan", 600);
        set_skill("calligraphy", 600);
        set_skill("medical", 600);
        set_skill("taoism", 400);
        set_skill("taohua-yaoli", 600);
        set_skill("qimen-xuanshu", 600);
        set_skill("martial-cognize", 620);

        map_skill("force", "bibo-shengong");
        map_skill("finger", "tanzhi-shentong");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("whip", "canglang-bian");
        map_skill("strike", "luoying-shenzhang");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "tanzhi-shentong");
        map_skill("sword", "yuxiao-jianfa");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("medical", "taohua-yaoli");

        prepare_skill("finger" , "tanzhi-shentong");

        set("no_teach", ([
                "count"           : (: try_to_learn_count :),
                "bihai-chaosheng" : (: try_to_learn_bibai :),
        ]));

        set("inquiry", ([
                "離島"       : (: ask_leave :),
                "桃花藥理"   : (: ask_book1 :),
                "簫譜"       : (: ask_book2 :),
                "旋風掃葉腿" : (: ask_book3 :),
                "河圖"       : (: ask_book4 :),
                "洛書"       : (: ask_book4 :),
                "玉簫"       : (: ask_yuxiao :),
                "奇門五轉"   : (: ask_skill1 :),
                "蘭花拂穴"   : (: ask_skill2 :),
                "影落飛花"   : (: ask_skill3 :),
                "天外清音"   : (: ask_skill4 :),
                "天地情長"   : (: ask_skill5 :),
                "碧海潮生"   : (: ask_skill6 :),
                "定昆侖"     : (: ask_skill7 :),
                "嘯滄海"     : (: ask_skill8 :),
                "破九域"     : (: ask_skill9 :),
                "轉乾坤"     : (: ask_skill10 :),
                "漫天花雨"     : (: ask_skill11 :),
                "傻姑"       : (: ask_shagu :),
                "碧浪滔天"   : "這招你去讓馮默風教你吧。",
                "披星戴月"   : "這招你去讓陸乘風教你吧。",
                "狂風絕技"   : "這招你去讓陸乘風教你吧。",
                "隨波逐流"   : "這招你去讓曲靈風教你吧。",
                "黃蓉"       : "你敢直稱我女兒的閨名？",
                "九陰真經"   : "如果你能幫我取得真經，我一定重重謝你。",
                "九陰神功"   : "九陰神功恢弘正大，乃蓋世奇功！",
                "蘭花手"     : "蘭花拂穴手…唉…可惜我幾個弟子都算不得成才！",
                "彈指神通"   : "…唉…我一身絕藝竟然無人可以繼承？",
                "玉蕭劍法"   : "不是性情中人，如何能夠領會這劍法？",
                "碧波神功"   : "…唉…我桃花島的內功何等厲害，可惜…",
                "九花玉露丸" : "這個東西難制得緊，你好好學學桃花藥理，以後自己制吧。",
                "無常丹"     : "…嗯…等你學通了桃花藥理的奧妙，自己慢慢制吧。",
        ]));

        create_family("桃花島", 1, "島主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bihai" :),
                (: perform_action, "sword.qing" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "finger.ding" :),
                (: perform_action, "finger.xiao" :),
                (: perform_action, "finger.po" :),
                (: perform_action, "finger.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        if (clonep())
        {
                ob = find_object(YUXIAO);
                if (! ob) ob = load_object(YUXIAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        set_temp("handing", ob);
                } else
                {
                        set_temp("handing", carry_object("/d/taohua/obj/huaban"));
                }
        }
        carry_object(__DIR__"obj/bupao")->wear();
        // carry_object("/clone/book/jiuyin2");
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()))
        {
                if( query_temp("th_tomb_thief", ob) )
                {
                        command("say " + RANK_D->query_rude(ob) + "，膽敢私闖我夫人墓室，納命來！\n");
                        start_busy(1);
                        kill_ob(ob);
                }
                if( query("th_killer", ob) || query_temp("th_killer", ob) )
                {
                        command("sneer"+query("id", ob));
                        command("say 孽徒好大膽子，居然同門弟子手足相殘！");
                        message_vision(HIR "黃藥師說完一抬手，一指戳在$N的" +
                                       xuedao[random(sizeof(xuedao))] + "上。\n" NOR, ob);
                        call_out("move_it", 1, ob);
                }

                if( query("kill_th_traitor", ob )
                 && query("help_chengfeng", ob )
                 && query("help_lingfeng", ob )
                 && query("help_mofeng", ob) )
                {
                        set_temp("huang_recr", 1, ob);
                        command("smile "+query("id", ob));
                }
        }
}

void move_it(object ob)
{
        object *inv;
        int k;

        if (ob)
        {
                set("eff_qi", 10, ob);
                set("eff_jing", 10, ob);
                set("jing", 0, ob);
                delete("th_killer", ob);
                delete_temp("th_killer", ob);

                inv = all_inventory(ob);
                for (k = 0; k < sizeof(inv); k++)
                {
                        if( (query("armor_prop", inv[k]) && query("equipped", inv[k]) )
                         || query("no_get", inv[k]) )
                                continue;
                        destruct(inv[k]);
                }
                ob->unconcious();
                ob->move("/d/taohua/maze/maze"+(random(63)+1));
        }
}

void attempt_apprentice(object ob)
{
        string master;
        string *app = ({ "陸乘風", "曲靈風" });
        object obj;

        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 25)
        {
                command("say 我不收資質差的弟子，您請回吧！");
                return;
        }

        if( query("shen", ob)<-10000
         || query("shen", ob)>10000 )
        {
                command("say 我不與成名人物打交道，您請回吧！");
                return;
        }
        /*
        if( query("combat_exp", ob)<400000 )
        {
                if( stringp(master=query_temp("taohua/master", ob)) )
                {
                        command("say 不是讓你和" + master + "學藝嗎？你怎麼回事？");
                        return;
                }

                if( query("family/family_name", ob) == "桃花島" && 
                    query("family/master_name", ob) != "黃藥師" )
                {
                        command("say你好好跟"+query("family/master_name", ob)+
                                "學藝，水平到了老夫自然會親自點撥你。");
                        return;
                }

                master = app[random(sizeof(app))];

                command("say 嗯…念你長途跋涉趕來拜師，老夫就收你入桃花島。");
                command("say 不過你武學方面成就有限，還是先跟我弟子" + master + "學習吧。");
                set_temp("taohua/master", master, ob);
                set("family/family_name", "桃花島", ob);
                return;
        }
        */

        if( !query_temp("huang_recr", ob) && !query("reborn", ob) )
        {
                tell_object(ob, "黃藥師對你睬也不睬。\n");
                return;
        }

        command("say 很好，很好。");
        command("recruit "+query("id", ob));

        obj = new("/d/taohua/obj/bagua");
        obj->move(this_object());

        command("give "+query("id", ob)+" bagua");

        if( query("short", environment(this_object())) != "黃藥師居處" )
        {
                write("說完，黃藥師飄然而去。\n");
                destruct(this_object());
        }
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/huang/count", me) )
        {
                command("say 你是誰？哪裡來的？要幹啥？");
                return -1;
        }

        if (skill != "count"
            && skill != "mathematics"
            && skill != "chuixiao-jifa")
        {
                command("say 老叫花教你什麼就學什麼，你不學就算了。");
                return -1;
        }

        if ((int)me->query_skill("count", 1) > 379)
        {
                command("say 到此為止，你的功力也不差了，剩下的自己去練。");
                return -1;
        }

        return 1;
}

mixed try_to_learn_count()
{
        object ob = this_player();

        if( query("can_learn/huang/count", ob) )
                return 0;

        if (ob->query_skill("mathematics", 1) >= 200)
        {
                command("nod2");
                command("say 看來你對算術也頗有見解，今日老夫就教"
                        "你些陰陽八卦的知識。");
                set("can_learn/huang/count", 1, ob);
                return 0;
        }
        return "陰陽八卦我不輕易傳授。";
}

mixed try_to_learn_bibai()
{
        object ob = this_player();

        if( query("can_learn/huang/bihai-chaosheng", ob) )
                return 0;

        if (ob->query_skill("bibo-shengong", 1) >= 120
        &&  ob->query_skill("chuixiao-jifa", 1) >= 120)
        {
                command("sigh");
                command("say 想不到你蕭技居然已達此境界，今日老夫"
                        "就傳你碧海潮生曲吧。");
                set("can_learn/huang/bihai-chaosheng", 1, ob);
                return 0;
        }
        return "爾非性情中人，這碧海潮生曲並不適合你。";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/luoying-shenzhang/zhuan", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("luoying-shenzhang", 1) < 1)
                return "你連落英神劍掌都沒學，跑來搗什麼亂？";

        if( query("family/gongji", me)<350 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功火候尚需提高，練好了再來吧。";

        if (me->query_skill("qimen-wuxing", 1) < 120)
                return "你對奇門五行的研究不夠，這招還學不會。";

        if (me->query_skill("luoying-shenzhang", 1) < 120)
                return "哼！等你把落英神劍掌練熟了再來找我！";

        message_sort(HIY "\n$n" HIY "打量了$N" HIY "一眼，隨手攻出一掌。$N" HIY
                     "見來勢平平，並不見奇，哪知在作出抵擋的一瞬間才發覺$n" HIY
                     "掌力猶如黃河決堤般洶湧而入，$N" HIY "頓時再也把持不住，被"
                     "那掌力帶得接連旋轉了數圈，好不容易才停了下來。\n\n" NOR,
                     me, this_object());

        command("say 好了，你下去吧。");
        tell_object(me, HIC "你學會了「奇門五轉」。\n" NOR);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("luoying-shenzhang"))
                me->improve_skill("luoying-shenzhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/luoying-shenzhang/zhuan", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/lanhua-shou/fu", me) )
                return "自己下去練，羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("lanhua-shou", 1) < 1)
                return "你連蘭花拂穴手都沒學，跑來搗什麼亂？";

        if( query("family/gongji", me)<300 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 160)
                return "你的內功火候尚需提高，練好了再來吧。";

        if (me->query_skill("lanhua-shou", 1) < 120)
                return "等你把蘭花拂穴手練熟了再來找老夫。";

        message_sort(HIY "\n$n" HIY "微微點了點頭，反手輕輕伸出三指，婉轉如一朵"
                     "盛開的蘭花，對準$N" HIY "的幾處穴道虛擊數下。\n\n" NOR,
                     me, this_object());

        command("say 看懂了麼？");
        tell_object(me, HIC "你學會了「蘭花拂穴」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("lanhua-shou"))
                me->improve_skill("lanhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lanhua-shou/fu", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/lanhua-shou/fei", me) )
                return "唉…你自己下去練吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("lanhua-shou", 1) < 1)
                return "你連蘭花拂穴手都沒學，跑來搗什麼亂？";

        if( query("family/gongji", me)<400 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候尚需提高，練好了再來吧。";

        if (me->query_skill("lanhua-shou", 1) < 140)
                return "等你把蘭花拂穴手練熟了再來找老夫。";

        message_sort(HIY "\n$n" HIY "一聲長嘆，伸手將$N" HIY "招至他身旁，低聲"
                     "在$N" HIY "耳邊細說良久。$N" HIY "一邊聽一邊點頭，看來對"
                     "$n" HIY "的教導大有所悟。\n\n" NOR, me, this_object());

        command("say 唉…你自己下去練吧。");
        tell_object(me, HIC "你學會了「影落飛花」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("lanhua-shou"))
                me->improve_skill("lanhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lanhua-shou/fei", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/tian", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("yuxiao-jianfa", 1) < 1)
                return "你連玉簫劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<350 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("bibo-shengong", 1) < 120)
                return "你碧波神功的修為不夠，學不了這一招。";

        if (me->query_skill("yuxiao-jianfa", 1) < 120)
                return "你的玉簫劍法還不夠熟練，練高了再來找我。";

        message_sort(HIY "\n$n" HIY "微微點了點頭，伸手將$N" HIY "招到面前，在"
                     "$N" HIY "耳邊輕聲嘀咕了些話。$N" HIY "聽了半天，突然間不"
                     "由會心的一笑，看來大有所悟。\n\n" NOR, me, this_object());

        command("nod2");
        command("say 你下去練吧。");
        tell_object(me, HIC "你學會了「天外清音」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        if (me->can_improve_skill("bibo-shengong"))
                me->improve_skill("bibo-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/tian", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/qing", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("yuxiao-jianfa", 1) < 1)
                return "你連玉簫劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候尚需提高，練好了再來吧。";

        if (me->query_skill("yuxiao-jianfa", 1) < 150)
                return "就你這點本事？等你把玉簫劍法練熟了再來找我吧！";

        message_sort(HIY "\n$n" HIY "舉頭望天，若有所思，隨手搭在$N" HIY "的肩"
                     "頭，$N" HIY "忽然發現內力源源而逝，不由大驚！\n\n" NOR,
                     me, this_object());

        command("sigh");
        command("say 你懂了麼？");
        tell_object(me, HIC "你學會了「天地情長」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/qing", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/bihai", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("yuxiao-jianfa", 1) < 1
        &&  me->query_skill("bibo-shengong", 1) < 1
        &&  me->query_skill("bihai-chaosheng", 1) < 1)
                return "你玉簫劍法、碧波神功、碧海潮生曲一樣都沒學，搗什麼亂？";

        if( query("family/gongji", me)<1000 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("bibo-shengong", 1) < 180)
                return "你碧波神功的修為不夠，學不了這一招。";

        if (me->query_skill("yuxiao-jianfa", 1) < 180)
                return "你的玉簫劍法還不夠熟練，練高了再來找我。";

        if (me->query_skill("bihai-chaosheng", 1) < 180)
                return "你的碧海潮生曲練好了嗎？";

        message_sort(HIY "\n$n" HIY "更不答話，單手撫按玉簫，只聽得簫聲如鳴琴擊"
                     "玉，發了幾聲，接著悠悠揚揚，飄下清亮柔和的洞簫聲來。只聽那"
                     "洞簫聲情致飄忽，纏綿宛轉，便似一女子一會兒嘆息，一會兒又似"
                     "呻吟，一會兒卻又軟語溫存或柔聲叫喚。緊跟著那簫聲清亮宛如大"
                     "海浩淼，萬裡無波，遠處潮水緩緩推近，漸近漸快，其後洪濤洶湧"
                     "，白浪連山，而潮水中魚躍鯨浮，海面上風嘯鷗飛，再加上水妖海"
                     "怪，群魔弄潮，忽而冰山飄至，忽而熱海如沸，極盡變幻之能事。"
                     "時至最後，卻聽那簫聲癒來癒細，幾乎難以聽聞，便尤如大海潮退"
                     "後水平如鏡一般，但海底卻又是暗流湍急，洶湧澎湃。直待$n" HIY
                     "這首碧海潮生曲奏完，卻發現$N" HIY "早已陶醉在這簫聲之中，完"
                     "全無法自拔。\n\n" NOR, me, this_object());

        command("nod");
        command("say 你下去練吧。");
        tell_object(me, HIC "你學會了「碧海潮生按玉簫」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("chuixiao-jifa"))
                me->improve_skill("chuixiao-jifa", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        if (me->can_improve_skill("bibo-shengong"))
                me->improve_skill("bibo-shengong", 1500000);
        if (me->can_improve_skill("bihai-chaosheng"))
                me->improve_skill("bihai-chaosheng", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/bihai", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/ding", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你連彈指神通都沒學，瞎胡鬧什麼？";

        if( query("family/gongji", me)<450 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功火候尚需提高，練好了再來吧。";

        if (me->query_skill("tanzhi-shentong", 1) < 120)
                return "你的彈指神通火候還不夠，等你練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "轉過頭看了$N" HIY "一眼，更不答話，只是輕"
                     "輕伸出兩指，合指輕彈，頓時只聽“颼”的一聲，一縷若有若無"
                     "的罡氣已至$n" HIY "指尖射出，朝$N" HIY "電射而去。$N" HIY
                     "頓覺脅下一麻，已被$n" HIY "的指氣射中，全身酸軟無力，呆立"
                     "當場。\n\n" NOR, me, this_object());

        command("say 招式便是如此，你站在這裡琢磨一下吧。");
        tell_object(me, HIC "你學會了「定昆侖」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/ding", 1, me);
        addn("family/gongji", -450, me);
        me->start_busy(15);

        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/xiao", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你連彈指神通都沒學，瞎胡鬧什麼？";

        if( query("family/gongji", me)<800 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 280)
                return "你的內功火候尚需提高，練好了再來吧。";

        if( query("max_neili", me)<3000 )
                return "你的內力修為太差，還是練高點再來吧。";

        if (me->query_skill("tanzhi-shentong", 1) < 200)
                return "你的彈指神通火候還不夠，等你練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "一聲長嘆，伸手將$N" HIY "招至他身旁，低聲"
                     "在$N" HIY "耳邊細說良久。$N" HIY "一邊聽一邊點頭，看來對"
                     "$n" HIY "的教導大有所悟。\n\n" NOR, me, this_object());

        command("nod2");
        command("say …嗯…你自己練去吧。");
        tell_object(me, HIC "你學會了「嘯滄海」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/xiao", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/po", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你連彈指神通都沒學，瞎胡鬧什麼？";

        if( query("family/gongji", me)<1300 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 250)
                return "你的內功火候尚需提高，練好了再來吧。";

        if( query("max_neili", me)<2500 )
                return "你的內力修為太差，還是練高點再來吧。";

        if (me->query_skill("throwing", 1) < 180)
                return "你的暗器運用還不夠嫻熟，下去練練再來吧。";

        if (me->query_skill("tanzhi-shentong", 1) < 180)
                return "你的彈指神通火候還不夠，等你練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "微微一笑，當下也不作答，隨手從身旁桃花樹"
                     "上拈下一片花瓣，$N" HIY "正感納悶，忽聞破空聲大作，那片"
                     "花瓣已由$n" HIY "指尖疾彈而出，頓時只聽噗嗤一聲，已沒入"
                     "$N" HIY "身前的青石磚內，石面僅留下一個小孔。\n\n" NOR,
                      me, this_object());

        command("haha");
        tell_object(me, HIC "你學會了「破九域」。\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/po", 1, me);
        addn("family/gongji", -1300, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/zhuan", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你連彈指神通都沒學，瞎胡鬧什麼？";

        if( query("family/gongji", me)<2200 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。";

        if (me->query_skill("force") < 300)
                return "你的內功火候尚需提高，練好了再來吧。";

        if( query("max_neili", me)<3500 )
                return "你的內力修為太差，還是練高點再來吧。";

        if (me->query_skill("qimen-wuxing", 1) < 200)
                return "你對奇門五行的研究不夠，這招還學不會。";

        if (me->query_skill("tanzhi-shentong", 1) < 220)
                return "你的彈指神通火候還不夠，等你練熟了再來找我。";

        message_sort(HIY "\n$n" HIY "凝視了$N" HIY "半天，方道：“想不到我桃花"
                     "島居然還有你這等人才，想必日後繼承老夫衣砵非你莫屬了。”"
                     "$n" HIY "說完哈哈一笑，將$N" HIY "招至身旁，低聲細說講解"
                     "良久，全是$N" HIY "平生從未涉入的境界，$N" HIY "一邊聽一"
                     "邊點頭，看來對$n" HIY "的教導大有所悟。\n\n" NOR,
                     me, this_object());

        command("haha");
        command("say 能傳授的我都已傳授了，日後就自己努力吧。");
        tell_object(me, HIC "你學會了「轉乾坤」。\n" NOR);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/zhuan", 1, me);
        addn("family/gongji", -2200, me);

        return 1;
}

//增加漫天花雨的PFM
mixed ask_skill11() 
{ 
        object me; 
        
        me = this_player(); 
        
        if( query("can_perform/tanzhi-shentong/huayu", me) )
                return "這一招我不是已經教過你了嗎？還羅嗦什麼！"; 
        
        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，打聽老夫的武功有何企圖？"; 
        
        if (me->query_skill("tanzhi-shentong", 1) < 1) 
                return "你連彈指神通都沒學，瞎胡鬧什麼？"; 
        
        if( query("family/gongji", me)<2200 )
                return "你在我桃花島無所作為，這招老夫暫時還不能傳你。"; 
        
        if (me->query_skill("force") < 300) 
                return "你的內功火候尚需提高，練好了再來吧。"; 
        
        if( query("max_neili", me)<3500 )
                return "你的內力修為太差，還是練高點再來吧。"; 
        
        if (me->query_skill("qimen-wuxing", 1) < 200) 
                return "你對奇門五行的研究不夠，這招還學不會。"; 
        
        if (me->query_skill("tanzhi-shentong", 1) < 220) 
                return "你的彈指神通火候還不夠，等你練熟了再來找我。"; 
        
        message_sort(HIY "\n$n" HIY "凝視了$N" HIY "半天，方道：“想不到我桃花" 
                     "島居然還有你這等人才，想必日後繼承老夫衣砵非你莫屬了。”" 
                     "$n" HIY "說完哈哈一笑，將$N" HIY "招至身旁，低聲細說講解" 
                     "良久，全是$N" HIY "平生從未涉入的境界，$N" HIY "一邊聽一" 
                     "邊點頭，看來對$n" HIY "的教導大有所悟。\n\n" NOR, 
                     me, this_object());  
        
        command("haha"); 
        command("say 能傳授的我都已傳授了，日後就自己努力吧。"); 
        tell_object(me, HIC "你學會了「漫天花雨」。\n" NOR); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        me->improve_skill("martial-cognize", 1500000); 
        set("can_perform/tanzhi-shentong/huayu", 1, me);
        addn("family/gongji", -2200, me);
        
        return 1; 
} 

mixed ask_leave()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) == "桃花島" )
        {
                message_vision(CYN "$N" CYN "對$n" CYN "怒道：你既然入桃花島"
                               "門下，桃花陣就傷你不得，要離島自己走到海邊去"
                               "！\n" NOR, this_object(), me);
                return 1;
        }

        command("hmm");
        message_vision(HIW "\n$N" HIW "冷哼一聲，揮手招來兩個啞僕，將$n" HIW
                       "送了出去。\n\n" NOR, this_object(), me);
        me->move("/d/taohua/haitan");
        message_vision(HIW "\n$N" HIW "跟隨啞僕來到了海邊。\n\n" NOR, me);
        return 1;
}

mixed ask_book1()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "桃花島" )
                return "給我滾開！";

        if( query("family/master_id", me) != query("id") )
                return "只有老夫的弟子才配借讀此書。";

        if ((int)me->query_skill("taohua-yaoli", 1) < 60)
                return "你對桃花藥理的了解太淺，等你有所領悟後再說。";

        ob = find_object(TAOHUA);
        if (! ob) ob = load_object(TAOHUA);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "那本藥理不就是你拿著在看嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…桃花藥理現在不在我手裡。";

                if( query("family/family_name", owner) == "桃花島" )
                        return "那書現在暫時是你同門"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                return "桃花藥理現在落在了"+query("name", owner)+
                       "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 這本桃花藥理你就拿去看吧，可要認真研讀。");
        command("give taohua yaoshu to "+query("id", me));
        return 1;
}

mixed ask_book2()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "桃花島" )
                return "給我滾開！";

        if( query("family/master_id", me) != query("id") )
                return "只有老夫的弟子才配借讀此書。";

        if ((int)me->query_skill("chuixiao-jifa", 1) >= 150)
                return "你的簫技到如此地步，那曲譜對你已無多大幫助。";

        ob = find_object(XIAOPU);
        if (! ob) ob = load_object(XIAOPU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "那本簫譜不就是你拿著在看嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "我的簫譜已經借出去了。";

                if( query("family/family_name", owner) == "桃花島" )
                        return "簫譜現在暫時是你同門"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                        return "老夫的簫譜現在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 這本簫譜你就拿去看吧。");
        command("give xiao pu to "+query("id", me));
        return 1;
}

mixed ask_book3()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "桃花島" )
                return "給我滾開！";

        command("say 當年我性子太急，錯怪了乘風．．．");
        command("sigh");

        if (! query("xfsy_xinfa_given") || query("xfsy_xinfa_given") < 10)
        {
                command("say 我如今有一套心法，相煩" + RANK_D->query_respect(me) +
                        "交與乘風，照著我這功訣去做，和常人一般慢慢行走卻是不難，唉，……");
                ob = new(XUANFENG);
                ob->move(me);
                set("xfsy_xinfa_given", 1);
                message_vision("$N遞給$n一張薄紙。\n", this_object(), me);
        } else
                command("say 你去找乘風吧。");
        return 1;
}

mixed ask_book4()
{
        object me = this_player();

        if( query("family/family_name", me) != "桃花島"
         && !query("can_learn/huang/count", me) )
                return "給我滾開！";

        if( query("combat_exp", me)<1000000 )
                return "你現在的經驗太低，還是先多練練基本功。";

        if ((int)me->query_skill("count", 1) < 100)
                return "就算給你也讀不懂，和我羅嗦什麼。";

        set_temp("taohua/countbook", 1, me);
        command("nod");
        command("say 你去找曲靈風吧，這書我讓他在保管。");
        return 1;
}

mixed ask_yuxiao()
{
        object me;
        object ob;
        object owner;
int cost;

        me = this_player();

        if( query("family/family_name", me) != "桃花島" )
                return "給我滾開！";

        if( query("family/master_id", me) != query("id") )
                return "等你成了老夫的弟子再說。";

        if (me->query_skill("yuxiao-jianfa", 1) < 150)
                return "你還是先將你的玉蕭劍法練練高再說。";

        if (me->query_skill("chuixiao-jifa", 1) < 150)
                return "哼！你連簫都吹不好，拿玉蕭又有何用？";

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "你為我桃花島效力還不夠，等你擁有足夠的師門功績再來兌換玉簫使用時間吧。";
        ob = find_object(YUXIAO);
        if (! ob) ob = load_object(YUXIAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "老夫不是把玉蕭交給你了嗎？還羅嗦什麼！";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "玉簫現在不在老夫這裡。";

                if( query("family/family_name", owner) == "桃花島" )
                        return "玉簫現在暫時是你同門"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "老夫的玉簫現在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        set_temp("handing", carry_object("/d/taohua/obj/huaban"));
        command("say 念你刻苦用功，今日老夫就將玉簫借給你。");
        command("say 行走江湖萬事多加小心，可不要丟了老夫的臉。");
        command("give yu xiao to "+query("id", me));
addn("family/gongji", -cost, me); 
        ob->start_borrowing();
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != "/clone/book/jiuyin1")
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        message_sort("黃藥師看了看$N送來的秘籍，點了點頭，說道：\n"
                     "難得你將真經送回。你送我的東西我就收下了。\n"
                     "作為補償, 你可以從我這裡學點功夫。\n", me);

        command("heihei");
        command("say 好吧，既然這樣，我就傳你陰陽八卦，你可以隨時來問我！");
        destruct(ob);
        set("can_learn/huang/count", 1, me);

        return 1;
}

int ask_shagu()
{
        object me, obj;

        me = this_player();

        command("say 這孩子是我在打聽靈風下落時找到的，很可能是靈風之女，可惜不知受了什麼驚嚇，變成這種樣子。");
        if( (present("amulet",me) || query_temp("play_with_shagu", me)>10 )
         && !query_temp("ask_huang_about_shagu", me) )
        {
                command("say 這孩子腦筋不太好，難得你和她如此投緣，我給你書信一封，如果你見到她爹靈風，煩請轉交。");
                obj = new("/d/taohua/obj/shouyu");
                obj->move(me);
                set_temp("ask_huang_about_shagu", 1, me);
                message_vision("$N遞給$n一封書信。\n", this_object(), me);
        }

        command("sigh");
        return 1;
}

/*
void unconcious()
{
        die();
}
*/
