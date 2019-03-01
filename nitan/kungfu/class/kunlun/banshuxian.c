#include <ansi.h>
#include "kunlun.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

mixed ask_skill1();
mixed ask_skill2();
string ask_me();

void create()
{
        set_name("班淑嫻", ({ "ban shuxian", "ban", "shuxian" }));
        set("title", "昆侖派掌門夫人");
        set("long", @LONG
她就是昆侖派第四代掌門鐵琴先生何太沖的夫
人班淑嫻。只見她身材高大，頭發花白，雙目
含威。眉心間聚有煞氣。
LONG);
        set("gender", "女性");
        set("age", 46);
        set("attitude", "heroism");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 4800);
        set("max_jing", 2800);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 130);
        set("combat_exp", 1500000);

        set_skill("force", 210);
        set_skill("kunlun-xinfa", 200);
        set_skill("liangyi-shengong", 210);
        set_skill("dodge", 180);
        set_skill("chuanyun-bu", 180);
        set_skill("hand", 210);
        set_skill("sanyin-shou", 210);
        set_skill("cuff", 210);
        set_skill("zhentian-quan", 210);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("kunlun-jian", 200);
        set_skill("xunlei-jian", 200);
        set_skill("zhengliangyi-jian", 200);
        set_skill("throwing", 180);
        set_skill("kunlun-qifa", 180);
        set_skill("tanqin-jifa", 160);
        set_skill("qiuyue-lai", 160);
        set_skill("literate", 220);
        set_skill("martial-cognize", 200);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "kunlun-jian");
        map_skill("sword", "zhengliangyi-jian");
        map_skill("cuff", "zhentian-quan");
        map_skill("hand", "sanyin-shou");
        map_skill("throwing", "kunlun-qifa");
        map_skill("tanqin-jifa", "qiuyue-lai");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("cuff", "zhentian-quan");

        set("coagents", ({
                ([ "startroom" : "/d/kunlun/tieqinju",
                   "id"        : "he taichong" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷喝道："
                                "你給我站住！我們昆侖派豈是由得外"
                                "人隨便走動地方？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？給我放下來！" NOR,
        ]));

        create_family("昆侖派", 4, "掌門夫人");

        set("inquiry", ([
                "絕招"      : "你要問什麼絕招？",
                "絕技"      : "你要問什麼絕技？",
                "石破天驚"  : "這招你找我丈夫學去，別來煩我。",
                "流星電閃"  : "這招你找我丈夫學去，別來煩我。",
                "迅雷一擊"  : "這招你找我丈夫學去，別來煩我。",
                "域外梵音"  : "這招你找我丈夫學去，別來煩我。",
                "玉碎昆岡"  : "這招你找我丈夫學去，別來煩我。",
                "秘籍"      : (: ask_me :),
                "損筋訣"    : (: ask_skill1 :),
                "無聲無色"  : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.wu" :),
                (: perform_action, "throwing.liu" :),
                (: perform_action, "cuff.shi" :),
                (: perform_action, "hand.sun" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        set("master_ob",4);
        setup();

        carry_object("clone/weapon/changjian")->wield();
        carry_object("clone/misc/cloth")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("gender", me) != "女性" )
        {
                command("say 我看見你們這些臭男人就煩，快給我滾開！");
                return;
        }

        if( query("combat_exp", me)<150000 )
        {
                command("say 你的江湖經驗太淺，還是鍛煉鍛煉再說吧。");
                return;
        }

        if ((int)me->query_skill("kunlun-xinfa", 1) < 80)
        {
                command("say 你對本門的內功心法所知尚淺，練習高了再來找我吧。");
                return;
        }

        command("say 好吧，以後你就跟我吧，你須得安心學藝，不可亂來。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/sanyin-shou/sun", me) )
                return "自己下去練，別老跟我糾纏不休！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("sanyin-shou", 1) < 1)
                return "你連三陰手都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<400 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("sanyin-shou", 1) < 140)
                return "你的三陰手修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "微微一笑，對$N" HIY "說道：看"
                       "好了。說完單手輕輕拂\n過身前的茶幾，不著半"
                       "點力道。$N" HIY "正詫異間，茶幾突然\n從中碎"
                       "裂，“喀嚓”一聲斷為兩截。\n" NOR, me,
                       this_object());
        command("smile");
        command("say 這招便是損筋訣，並不復雜，只需記住‘以柔克剛’四字皆可。");
        tell_object(me, HIC "你學會了「損筋訣」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("sanyin-shou"))
                me->improve_skill("sanyin-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sanyin-shou/sun", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/zhengliangyi-jian/wu", me) )
                return "自己下去練，別老跟我糾纏不休！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("zhengliangyi-jian", 1) < 1)
                return "你連正兩儀劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1200 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 220)
                return "你的內功火候不足，學不了這一招。";

        if (me->query_skill("dodge") < 220)
                return "你的輕功火候不足，學不了這一招。";

        if (me->query_dex() < 45)
                return "你的身法實在太差，學不了這一招。";

        if (me->query_skill("zhengliangyi-jian", 1) < 160)
                return "你的正兩儀劍法修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "眉頭微微一皺，一揮手，示意其它弟子"
                       "全部出去。\n待其余昆侖派弟子陸續退下後，$n" HIY
                       "謹慎的環顧了下\n四周，最後將$N" HIY "招至身邊，"
                       "悄聲在$N" HIY "耳旁細說良久。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 剛才我所說的你都記牢了嗎？自己下去練吧！");
        tell_object(me, HIC "你學會了「無聲無色」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("zhengliangyi-jian"))
                me->improve_skill("zhengliangyi-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhengliangyi-jian/wu", 1, me);
        addn("family/gongji", -1200, me);

        return 1;
}

string ask_me()
{
        mapping fam;
        object ob;
        ob = this_player();

        if( !(fam=query("family", this_player()) )
                || fam["family_name"] != "昆侖派")
                return RANK_D->query_respect(this_player()) +
                        "與本派素無來往，不知此話從何談起？";
        if( query("gender", ob) == "男性" )
                return "給我走開，我看見你們這些臭男人就煩。";
        if (query("book_count") < 1)
                return "你來晚了，本派真經已被你師兄拿走了。";
        addn("book_count", -1);
        ob = new("/clone/book/lyj-book.c");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到兩儀劍心得啦。\n");
        return "先師曾傳下來這本「兩儀劍心得」，你拿回去好好鑽研。";
}
