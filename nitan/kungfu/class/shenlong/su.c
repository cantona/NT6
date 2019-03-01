// This program is a part of NT MudLIB
// su.c 蘇荃

#include "shenlong.h"

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_huimou();
mixed ask_hengchen();
mixed ask_huixiang();
void create()
{
        set_name("蘇荃", ({ "su quan", "su" }));
        set("title",  HIY"神龍教"NOR"教主夫人" );
        set("long", "她就是神龍教教主洪安通的夫人。\n");
        set("gender", "女性");
        set("age", 23);
        set("attitude", "friendly");
        set("str", 35);
        set("int", 30);
        set("con", 30);
        set("dex", 38);

        set("max_qi", 3500);
        set("max_jing", 1800);
        set("neili", 3700);
        set("max_neili", 3700);
        set("jiali", 50);
        set("level", 30);
        set("combat_exp", 620000);
        set("shen_type", -1);

        set_skill("force", 450);
        set_skill("shenlong-xinfa", 450);
        set_skill("dodge", 480);
        set_skill("yixing-bufa", 460);
        set_skill("hand", 450);
        set_skill("sword", 450);
        set_skill("meiren-sanzhao", 450);
        set_skill("strike", 480);
        set_skill("shenlong-bashi", 450);
        set_skill("huagu-mianzhang", 420);
        set_skill("parry", 450);
        set_skill("staff", 450);
        set_skill("shedao-qigong", 420);
        set_skill("literate", 400);
        set_skill("medical", 400);
        set_skill("shenlong-mixin", 400);
        set_skill("martial-cognize", 200);
        set_skill("shenlong-jian", 400);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("strike", "huagu-mianzhang");
        map_skill("hand", "shenlong-bashi");
        map_skill("sword", "shenlong-jian");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("神龍教", 1, "教主夫人");

        set("inquiry", ([
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao)。",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao)。",
                "退教"   : "哈哈哈哈！退教？這麼多年我還真聽過幾起，不過他們已經都死了。",
                "口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！",
                "rujiao" : "一般人是入不了我神龍教的(join shenlongjiao)。",
                "tuijiao": "哈哈哈哈！退教？這麼多年我還真聽過幾起，不過他們已經都死了。",
              "貴妃回眸" : (: ask_huimou :),
              "小憐橫陳" : (: ask_hengchen :),
              "飛燕回翔" : (: ask_huixiang :),
        ]));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: command("smile") :),
                (: command("haha") :),
                (: command("chat 憑你這" + RANK_D->query_rude(this_player())+",也敢在太歲爺頭上動土?\n") :),
                (: command("say 你活得不耐煩了找死啊？\n") :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );
        set("master_ob", 5);
        setup();
        carry_object("/d/shenlong/npc/obj/ycloth")->wear();
        carry_object(__DIR__"obj/duanjian")->wield();
        add_money("silver", 50);
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                   set("combat_exp", 100000);
                   set("qi", 100);
                   set("jing", 100);
        }
}

void attempt_apprentice(object ob)
{
        command("say 好吧，你就和我學武功吧。");
        command("recruit "+query("id", ob));
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

        case "玉女無情" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/meiren-sanzhao/wuqing",
                           "name"    : "玉女無情",
                           "sk1"     : "meiren-sanzhao",
                           "lv1"     : 100,
                           "sk2"     : "sword",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;

        default:
                return 0;
        }
}

mixed ask_huimou()
{
        object me;

         me = this_player();
         if( query("can_perform/shenlong-bashi/huimou", me) )
                return "自己多練練，少在我面前羅嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪兒來的？找死啊？";

        if( query("shen", me)>-50000 )
                return "你要好好為我神教效力，手段要更狠更毒。我才能傳你這門絕招！";

        if (me->query_skill("shenlong-bashi", 1) < 150)
                return "你的神龍八式手法根基不夠，還得多練習練習。";

        if (me->query_skill("force", 1) < 150)
                return "你的內功火候不足，學不成這貴妃回眸。";


         message_vision(HIY "$n" HIY "點頭對你說道：“你看好了！”然後，又轉身對沐劍屏說道：“劍屏，"
                     "你過來！”說罷身子微曲，纖腰輕扭，右足反踢，向沐劍屏小腹踹去。沐"
                     "劍屏連忙後縮相避，$n順勢反過身來，左手摟住沐劍屏的頭頸，右手竟已"
                     "輕輕點在沐劍屏後心的穴道上。"NOR, me, this_object());

        tell_object(me, HIG "你學會了貴妃回眸。" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/huimou", 1, me);
        return 1;
}

mixed ask_hengchen()
{
        object me;

        me = this_player();
        if( query("can_perform/shenlong-bashi/hengchen", me) )
        return "自己多練練，少在我面前羅嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪兒來的？找死啊？";

        if( query("shen", me)>-80000 )
                return "你要好好為我神教效力，手段要更狠更毒。我才能傳你這門絕招！";

        if (me->query_skill("shenlong-bashi", 1) < 150)
                return "你的神龍八式手法根基不夠，還得多練習練習。";

        if (me->query_skill("force", 1) < 150)
        return "你的內功火候不足，學不成這小憐橫陳。";

        message_vision(HIY"$n" HIY "翻身臥倒並讓沐劍屏伸出右足，虛踏她後腰，手中假裝持刀架住她"
                       "頭頸。驀見$n腦袋向著她自己胸口鑽落，沐劍屏架頸中的一刀自然落空，"
                       "她順勢在地下一個筋鬥在沐劍屏胯下鑽過，右手輕輕擊在沐劍屏後心。"NOR,
                       me, this_object());

        command("say 這就是美女三招的第二招──「小憐橫陳」。");
        tell_object(me, HIG "你學會了小憐橫陳。" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/hengchen", 1, me);
        return 1;
}

mixed ask_huixiang()
{
        object me;

        me = this_player();
        if( query("can_perform/shenlong-bashi/huixiang", me) )
                return "自己多練練，少在我面前羅嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪兒來的？找死啊？";

        if( query("shen", me)>-100000 )
                return "你要好好為我神教效力，手段要更狠更毒。我才能傳你這門絕招！";

        if (me->query_skill("shenlong-bashi", 1) < 160)
                return "你的神龍八式手法根基不夠，還得多練習練習。";

        if (me->query_skill("force", 1) < 160)
                return "你的內功火候不足，學不成這飛燕回翔。";

        message_vision(HIY"$n" HIY "讓沐劍屏左手拿住她雙手手腕，右手虛執兵器，架在她的膚光白膩頭"
                     "頸之中，$n笑道：“看仔細了！”右足向前輕踢，脫身而出，接著雙手回轉"
                     "擊出一招，正中沐劍屏後心。"NOR, me, this_object());

        command("say 這就是美女三招的第二招──「飛燕回翔」。");
        tell_object(me, HIG "你學會了飛燕回翔。" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/huixiang", 1, me);
        return 1;
}
