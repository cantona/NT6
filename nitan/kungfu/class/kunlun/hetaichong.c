#include <ansi.h>
#include "kunlun.h"

#define TIEQIN    "/clone/lonely/tieqin"
#define JIANJING  "/clone/lonely/book/xunleijian"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_jian();
mixed ask_jing();
string ask_me();
string ask_ding();
string ask_su();

void create()
{
        object ob;
        set_name("何太沖", ({"he taichong", "he", "taichong"}));
        set("long", @LONG
他就是名揚江湖的昆侖派第四代掌門鐵琴先生
何太沖。雖然此時他年紀已大，但仍然看得出
他年輕時的英俊瀟洒。
LONG);
        set("nickname", WHT "鐵琴先生" NOR);
        set("gender", "男性");
        set("age", 43);
        set("attitude", "heroism");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 150);
        set("combat_exp", 1600000);

        set_skill("force", 220);
        set_skill("kunlun-xinfa", 200);
        set_skill("liangyi-shengong", 220);
        set_skill("dodge", 200);
        set_skill("chuanyun-bu", 200);
        set_skill("hand", 200);
        set_skill("sanyin-shou", 200);
        set_skill("cuff", 200);
        set_skill("zhentian-quan", 200);
        set_skill("parry", 200);
        set_skill("sword", 220);
        set_skill("kunlun-jian", 220);
        set_skill("xunlei-jian", 220);
        set_skill("zhengliangyi-jian", 220);
        set_skill("throwing", 200);
        set_skill("kunlun-qifa", 200);
        set_skill("tanqin-jifa", 240);
        set_skill("tieqin-yin", 240);
        set_skill("literate", 220);
        set_skill("martial-cognize", 200);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "zhengliangyi-jian");
        map_skill("sword", "kunlun-jian");
        map_skill("cuff", "zhentian-quan");
        map_skill("hand", "sanyin-shou");
        map_skill("throwing", "kunlun-qifa");
        map_skill("tanqin-jifa", "tieqin-yin");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("cuff", "zhentian-quan");

        create_family("昆侖派", 4, "掌門");

        set("inquiry", ([
                "絕招"      : "你要問什麼絕招？",
                "絕技"      : "你要問什麼絕技？",
                "損筋訣"    : "嗯，這招你去找我內子求教吧。",
                "無聲無色"  : "嗯，這招你去找我內子求教吧。",
                "石破天驚"  : (: ask_skill1 :),
                "流星電閃"  : (: ask_skill2 :),
                "迅雷一擊"  : (: ask_skill3 :),
                "域外梵音"  : (: ask_skill4 :),
                "玉碎昆岡"  : (: ask_skill5 :),
                "鐵琴劍"    : (: ask_jian :),
                "劍經"      : (: ask_jing :),
                "迅雷劍經"  : (: ask_jing :),
                "心法" : (: ask_me :),
                "蘇習之" : (: ask_su :),
                "追殺" : (: ask_ding :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.fanyin" :),
                (: perform_action, "throwing.liu" :),
                (: perform_action, "cuff.shi" :),
                (: perform_action, "hand.sun" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        set("book_count", 1);
        set("ding_count", 18);
        set("master_ob",4);
        setup();

        if (clonep())
        {
                ob = find_object(TIEQIN);
                if (! ob) ob = load_object(TIEQIN);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("clone/weapon/changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }

        carry_object("clone/misc/cloth")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("gender", me) == "女性" )
        {
                command("say 我不收女徒弟，你去找我夫人好了。");
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

        command("say 既然你如此有心，我便收下你，希望你能夠有所作為。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/zhentian-quan/shi", me) )
                return "咦？這招你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("zhentian-quan", 1) < 1)
                return "你連震天拳法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<100 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("zhentian-quan", 1) < 80)
                return "你的震天拳法修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "略微點了點頭，說道：我這給你"
                       "演示一遍，你可要看好了。\n說完便只見$n" HIY
                       "拉開架式，提運內勁，聚力于掌一拳揮出，頓\n"
                       "時$N" HIY "周圍呼嘯聲驟起，氣勢當真有如石"
                       "破天驚。\n" NOR, me, this_object());
        command("nod");
        command("say 這招石破天驚招式並不復雜，下去稍加練習便成。");
        tell_object(me, HIC "你學會了「石破天驚」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("zhentian-quan"))
                me->improve_skill("zhentian-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhentian-quan/shi", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/kunlun-qifa/liu", me) )
                return "咦？這招你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("kunlun-qifa", 1) < 1)
                return "你連昆侖器法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功修為怎麼這麼差？練好了再來吧！";

        if (me->query_skill("kunlun-qifa", 1) < 120)
                return "你的昆侖器法修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "凝視了$N" HIY "一會，幹咳了一"
                       "聲，其余弟子會意連忙全部退下。\n$n" HIY "這"
                       "才將$N" HIY "招到面前，在$N" HIY "耳邊輕聲"
                       "嘀咕了些話，$N" HIY "一邊聽\n一邊不住的點頭"
                       "，看來對$n" HIY "的教導大有所悟。\n" NOR,
                       me, this_object());
        command("nod");
        command("say 這招流星電閃用來偷襲和暗算敵人很有效，你多練練吧！");
        tell_object(me, HIC "你學會了「流星電閃」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("kunlun-qifa"))
                me->improve_skill("kunlun-qifa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/kunlun-qifa/liu", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/xunlei-jian/xun", me) )
                return "這招我已經解釋得很清楚了，還有什麼不懂就自己下去練！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("xunlei-jian", 1) < 1)
                return "你連迅雷劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<50 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("xunlei-jian", 1) < 100)
                return "你的迅雷劍法修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "點了點頭，隨手從身後的書架上取"
                       "出一本劍經，指著其中\n一段對$N" HIY "細說了"
                       "良久，$N" HIY "一邊聽一邊點頭。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 剛才我所說的便是這迅雷一擊的精髓，你自己下去練吧。");
        tell_object(me, HIC "你學會了「迅雷一擊」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("xunlei-jian"))
                me->improve_skill("xunlei-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xunlei-jian/xun", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/kunlun-jian/fanyin", me) )
                return "給我自己下去練，少跟我糾纏不休！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("kunlun-jian", 1) < 1)
                return "你連昆侖劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<1000 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不了這一招！";

        if (me->query_skill("tanqin-jifa", 1) < 120)
                return "你的彈琴技法尚且不夠熟練, 學不了這一招！";

        if (me->query_skill("kunlun-jian", 1) < 130)
                return "你的昆侖劍法修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "凝視了$N" HIY "半天，說道：“既"
                       "然你劍術已成，我今日便\n傳你這招吧。其余不相"
                       "幹的人都給我出去！”待其余弟子退\n下後，$n"
                       HIY "警惕的望了望四周，確定四下沒人後，這才從"
                       "\n鐵琴下抽出一柄長劍，慢慢的演示劍招。$N" HIY
                       "只覺劍招精妙奇\n巧，實乃前所謂聞。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 這招你下去後找個僻靜之地勤加練習，可千萬別泄露出去。");
        tell_object(me, HIC "你學會了「域外梵音」。\n" NOR);

        if (me->can_improve_skill("tanqin-jifa"))
                me->improve_skill("tanqin-jifa", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("kunlun-jian"))
                me->improve_skill("kunlun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/kunlun-jian/fanyin", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/zhengliangyi-jian/sui", me) )
                return "自己下去練，別老跟我糾纏不休！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素無瓜葛，何出此言？";

        if (me->query_skill("zhengliangyi-jian", 1) < 1)
                return "你連正兩儀劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<800 )
                return "你對本派所作出的貢獻不夠，這一招我暫時還不能傳你。";

        if (me->query_skill("force") < 250)
                return "你的內功火候不足，學不了這一招。";

        if( query("max_neili", me)<3000 )
                return "你的內力修為不足，學不了這一招。";

        if (me->query_skill("zhengliangyi-jian", 1) < 180)
                return "你的正兩儀劍法修為還不夠，自己下去練練再來吧。";

        message_vision(HIY "$n" HIY "眉頭微微一皺，一揮手，示意其它弟"
                       "子全部出去。待\n其余弟子陸續退下後，$n" HIY "謹"
                       "慎的環顧下四周，確定四下\n沒人後，這才將$N" HIY
                       "招至身邊，悄聲在$N" HIY "耳旁細說良久。待授\n招"
                       "完畢後，$n" HIY "又緩緩的搖了搖頭，接著道：這一"
                       "招乃是\n寧為玉碎，不為瓦全的拼死一擊，使用前一"
                       "定要慎重考慮。\n" NOR, me, this_object());
        command("sigh");
        command("say 行了，你自己下去練吧。");
        tell_object(me, HIC "你學會了「玉碎昆岡」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("zhengliangyi-jian"))
                me->improve_skill("zhengliangyi-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhengliangyi-jian/sui", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_jian()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "昆侖派" )
                return "你是哪裡來的？少在這裡跟我羅嗦！";

        if( query("family/master_id", me) != "hezudao" && 
            query("family/master_id", me) != "banshuxian" && 
            query("family/master_id", me) != "hetaichong" )
                return "哼！你還沒有資格使用我的寶劍。";

        if (me->query_skill("kunlun-jian", 1) < 150)
                return "還不快給我滾回去用心練劍，少在這裡羅嗦！";

        if (me->query_skill("tanqin-jifa", 1) < 100)
                return "你連琴都彈不好，還用什麼鐵琴劍？";

        if (present("tieqin jian", me))
                return "我的鐵琴劍現在不就在你手裡嗎？";

        ob = present("tieqin jian", this_object());

        if (! objectp(ob))
                return "你來晚了，鐵琴劍現在不在我這裡。";

        message_vision("$N拿出" WHT "鐵琴劍" NOR "(tieqin jian)給$n。\n",
                       this_object(), me);
        ob->move(me, 1);

        ob = new("clone/weapon/changjian");
        ob->move(this_object());
        ob->wield();

        return "我這柄鐵琴劍你就暫且拿去吧，多用它揚揚我們昆侖派的威風。";
}

mixed ask_jing()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if( query("family/family_name", me) != "昆侖派" )
                return "你是哪裡來的？少在這裡跟我羅嗦！";

        if (me->query_skill("xunlei-jian", 1) > 120)
                return "你的迅雷劍法已經到這個地步，沒必要再去參讀劍經了。";

        if (me->query_skill("sword", 1) < 30)
                return "你的劍法這麼差，還讀不懂劍經，練高點再來吧。";

        ob = find_object(JIANJING);
        if (! ob) ob = load_object(JIANJING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我不是已經把劍經給你了嗎，難道是弄丟了？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，那本「迅雷劍經」已經讓你同門師兄拿去了。";

                if( query("family/family_name", owner) == "昆侖派" )
                        return "那本「迅雷劍經」現在在你同門"+query("name", owner)+
                               "手中，你要用就去找他吧。";
                else
                        return "你來得正好，我正為此擔憂呢。聽說劍經落入" +
                               query("name", owner)+"手中，你去把他做了，搶回劍經！";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "說道：既然如此，這本「迅雷劍經」今日我便"
                       "交與你，可別弄丟了。\n" NOR, this_object(), me);
        command("givexunleijianjingto"+query("id", me));
        return 1;
}

/*
void unconcious()
{
        die();
}
*/
string ask_me()
{
        mapping fam;
        object ob;
        ob = this_player();
        if( !(fam=query("family", this_player()) )
                || fam["family_name"] != "昆侖派")
                return RANK_D->query_respect(this_player()) +
                        "與本派素無來往，不知此話從何談起？";
        if (query("book_count") < 1)
                return "你來晚了，本派心經已被你師兄拿走了。";
//             if(ob->query("gender")=="男性"||ob->query("per")<23)
//                return "本派心經不在我這裡。";
        addn("book_count", -1);
        ob = new("/clone/book/force-book2");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到昆侖心法啦。\n");
        return "我這裡有本「心法」，是有關吐吶吸氣的，你拿回去好好鑽研，有空多來找我哦！";
}

string ask_ding()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
                || fam["family_name"] != "昆侖派")
                return RANK_D->query_respect(this_player()) +
                        "與本派素無來往，不知此話從何談起？";

        if(this_player()->query_skill("mantianhuayu",1) < 60)
                return "你如此自願為師門效力，不枉我平時一番栽培，速速去吧！";

        if ( present("sangmen ding", this_player()) )
                return RANK_D->query_respect(this_player()) +
                        "你現在身上不是有嗎，怎麼又來要了？";
        if (query("ding_count") < 1)
                return "喪門釘已給了我派去追殺蘇習之的人，你就不用去了。";
        addn("ding_count", -1);
        set_temp("kunlun/ding", 1, this_player());
        ob = new("/d/kunlun/obj/sangmending");
        ob->move(this_player());
        return "你如此自願為師門效力，不枉我平時一番栽培，這把喪門釘你就拿去吧。";
}
string ask_su()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
                || fam["family_name"] != "昆侖派")
                return RANK_D->query_respect(this_player()) +
                        "與本派素無來往，不知此話從何談起？";

        if( query_temp("kunlun/ding", this_player()) )
                return "你還待在這裡做什麼，還不快去追蘇習之！";
        return "蘇習之這家伙竟然敢偷看本派的兩儀神劍，我派弟子必當將其追殺。";
}
