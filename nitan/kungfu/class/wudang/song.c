// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "wudang.h"

#define WUDANG    "/clone/book/wudang"
inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;
inherit F_COAGENT;

mixed ask_book1();
mixed ask_book2();
mixed ask_skill();

void create()
{
        set_name("宋遠橋", ({ "song yuanqiao", "song" }));
        set("nickname", "武當首俠");
        set("long",
                "他就是張三豐的大弟子、武當七俠之首的宋遠橋。\n"
                "身穿一件幹幹凈凈的灰色道袍。\n"
                "他已年過六十，身材瘦長，滿臉紅光。恬淡沖和，沉默寡言。\n");
        set("gender", "男性");
        set("age", 61);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 31);
        set("int", 27);
        set("con", 32);
        set("dex", 30);

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 160);
        set("combat_exp", 1500000);
        set("score", 70000);

        set_skill("force", 200);
        set_skill("yinyun-ziqi", 200);
        set_skill("taiji-shengong", 200);
        set_skill("dodge", 160);
        set_skill("tiyunzong", 160);
        set_skill("unarmed", 185);
        set_skill("taiji-quan", 185);
        set_skill("strike", 185);
        set_skill("wudang-zhang", 185);
        set_skill("zhenshan-zhang", 185);
        set_skill("hand", 185);
        set_skill("paiyun-shou", 185);
        set_skill("parry", 180);
        set_skill("sword", 185);
        set_skill("wudang-jian", 185);
        set_skill("shenmen-jian", 185);
        set_skill("taiji-jian", 185);
        set_skill("taoism", 190);
        set_skill("literate", 120);
        set_skill("medical", 200);
        set_skill("liandan-shu", 200);

        set("no_teach", ([
                "taiji-shengong" : "要想學習太極神功請向張真人請教。",
                "taiji-jian"     : "太極劍必須張真人親傳。",
                "taiji-quan"     : "太極拳必須張真人親傳。",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "zhenshan-zhang");
        map_skill("hand", "paiyun-shou");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武當派", 2, "弟子");

        set("inquiry", ([
                "武當藥理"   : (: ask_book1 :),
                "太極十三式" : (: ask_book2 :),
                "神門刺"     : (: ask_skill :),
                "絕招"       : (: ask_skill :),
        ]));

        set("book_count", 1);

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
        }) );

        set("coagents", ({
                ([ "startroom" : "/d/wudang/houyuan",
                   "id"        : "yu lianzhou" ]),
        }));

        set("master_ob", 4);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();

}
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
        if( query("shen", ob)<25000 )
        {
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }
        if ((int)ob->query_skill("yinyun-ziqi", 1) < 80)
        {
                command("say 我武當派最注重內功心法" + RANK_D->query_respect(ob)+
                        "是否應該在武當心法上多下點功夫啊?");
                return;
        }
        if ((int)ob->query_skill("taoism", 1) < 80)
        {
                command("say 習武是為了強身健體，一味的練武是不可取的。");
                command("say 我看你還需要在修身養性方面多鍛煉鍛煉，以提高"
                        "你的道德心法。");
                return;
        }
        command("say 好吧，我就收下你了。");
        command("say 希望你能全心修煉道家心法，領悟道家真髓！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_book1()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "武當派" )
                return "你又不是我武當派的傳人，這話是什麼意思？";

        if( query("shen", me)<10000 )
                return "你俠義正事做得不夠，這本書我還不能給你。";

        if ((int)me->query_skill("wudang-yaoli", 1) < 50)
                return "你對武當藥理的了解太淺，還是過段時間再說吧。";

        ob = find_object(WUDANG);
        if (! ob) ob = load_object(WUDANG);
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
                        return "…嗯…武當藥理現在不在我手裡。";

                if( query("family/family_name", owner) == "武當派" )
                        return "那書現在暫時是你同門"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                        return "武當藥理經現在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 這本武當藥理你就拿去看吧，可要認真研讀。");
        command("give liandan miben to "+query("id", me));
        return 1;
}

mixed ask_book2()
{
        object ob;

        if( query("family/family_name", this_player()) != query("family/family_name") )
                return RANK_D->query_respect(this_player()) +
                       "與本派素無來往，不知此話從何談起？";

        if (query("book_count") < 1)
                return "你來晚了，本派的內功心法不在此處。";

        addn("book_count", -1);
        ob = new("/clone/book/force_book");
        message_vision("$N拿出太極十三式(shu)給$n。\n",
                       this_object(), this_player());
        ob->move(this_player(), 1);
        return "好吧，這本「太極十三式」你拿回去好好鑽研。";
}

void reset()
{
        set("book_count", 1);
}

mixed ask_skill()
{
        object me;

        me = this_player();
        if( query("can_perform/shenmen-jian/ci", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if( query("shen", me)<140000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("shenmen-jian", 1) < 160)
                return "你的神門十三劍還不到家，要多練練！";

        if( query("family/gongji", me)<200 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        message_vision(HIY "$n" HIY "點了點頭，在$N" HIY
                       HIY "耳邊輕聲嘀咕了幾句，又拔出"
                       "腰間長劍，揮舞出幾個劍花，然後"
                       "猛地斜斜刺出。\n招式簡樸，毫無"
                       "半點華麗可言。\n" NOR,
                       me, this_object());
        command("nod");
        command("say 你可明白了？");
        tell_object(me, HIC "你學會了「神門刺」這一招。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        set("can_perform/shenmen-jian/ci", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}

/*
mixed ask_skill()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/ci", me) )
                return "你不是已經會了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你連太極劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<30000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("force") < 160)
                return "你的內功的修為不夠，練高了再來吧。";

        if (me->query_skill("taiji-jian", 1) < 120)
                return "你的太極劍還不到家，要多練練！";

        message_vision(HIY "$n" HIY "點了點頭，在$N" HIY "耳邊輕聲嘀"
                       "咕了幾句，又拔出腰間長\n劍，揮舞出幾個劍花，"
                       "然後猛地斜斜刺出。招式簡樸，毫無\n半點華麗可"
                       "言。\n" NOR, me, this_object());
        command("nod");
        command("say 你可明白了？");
        tell_object(me, HIC "你學會了「神門刺」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/ci", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "綿綿不絕" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/paiyun-shou/mian",
                           "name"    : "綿綿不絕",
                           "sk1"     : "paiyun-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "gongxian": 500,
                           "shen"    : 30000, ]));
                break;

        case "隔山打牛" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhenshan-zhang/da",
                           "name"    : "隔山打牛",
                           "sk1"     : "zhenshan-zhang",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "gongxian": 400,
                           "shen"    : 30000, ]));
                break;

        default:
                return 0;
        }
}
