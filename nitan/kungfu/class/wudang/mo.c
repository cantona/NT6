#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_me();
mixed ask_me1();
mixed ask_me2();

void create()
{
        set_name("莫聲谷", ({ "mo shenggu", "mo" }));
        set("nickname", "武當七俠");
        set("long",
                "他就是張三豐的七弟子莫聲谷。\n"
                "他看起來二十多歲，顯得稚氣未脫。\n"
                "但也是江湖中行俠仗義，聲明遠播的俠客。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 24);
        set("int", 27);
        set("con", 25);
        set("dex", 22);

        set("max_qi", 3600);
        set("max_jing", 1800);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 60);
        set("combat_exp", 850000);
        set("score", 300000);

        set_skill("force", 150);
        set_skill("yinyun-ziqi", 150);
        set_skill("taiji-shengong", 150);
        set_skill("dodge", 150);
        set_skill("tiyunzong", 150);
        set_skill("unarmed", 135);
        set_skill("taiji-quan", 135);
        set_skill("strike", 150);
        set_skill("zhenshan-zhang", 150);
        set_skill("hand", 100);
        set_skill("paiyun-shou", 100);
        set_skill("wudang-zhang", 125);
        set_skill("parry", 140);
        set_skill("sword", 130);
        set_skill("wudang-jian", 130);
        set_skill("taiji-jian", 130);
        set_skill("taoism", 70);
        set_skill("literate", 80);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "zhenshan-zhang");
        map_skill("hand", "paiyun-shou");

        prepare_skill("unarmed", "taiji-quan");

        set("no_teach", ([
                "taiji-shengong" : "要想學習太極神功請向張真人請教。",
                "taiji-jian"     : "太極劍必須張真人親傳。",
                "taiji-quan"     : "太極拳必須張真人親傳。",
        ]));

        set("inquiry", ([
                "隔山打牛" : (: ask_skill1 :),
                "太極初升" : (: ask_skill2 :),
                // "繞指柔劍" : (: ask_me :),
                // "宋青書"   : (: ask_me1 :),
                // "raozhi"   : (: ask_me :),
                // "qingshu"  : (: ask_me1 :),
                // "teach"    : (: ask_me2 :),
                // "指教"     : (: ask_me2 :),
                "石柱"     : "在石柱面壁可以大有收獲的。",
                "面壁"     : "面壁是一定要注明技能的。",
                "張三豐"   : "我恩師學究天人，尤其是他的道學心法。"
        ]));

        create_family("武當派", 2, "弟子");

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.sui" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 4);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<2000 )
        {
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi", 1) < 50)
        {
                command("say 我武當派最注重內功心法" + RANK_D->query_respect(ob)+
                        "是否應該在武當心法上多下點功夫啊?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 50)
        {
                command("say 習武是為了強身健體，一味的練武是不可取的做！");
                command("say 我看你還需要在修身養性方面多鍛煉鍛煉，以提高你"
                        "的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 希望你能好好用功，發揚我武當精神!");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/zhenshan-zhang/da", me) )
                return "能教的我都教了，你自己練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("zhenshan-zhang", 1) < 1)
                return "你連震山掌都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<50 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<6000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("zhenshan-zhang", 1) < 40)
                return "你的震山掌修為太淺，修煉好了再來吧。";

        if( query("max_neili", me)<200 )
                return "你的內力修為太淺，修煉高了再來吧。";

        message_vision(HIY "$n" HIY "點了點頭，將$N" HIY "招至"
                       "身邊，在耳旁低聲細說良久，$N" HIY "聽"
                       "後會心\n的一笑，看來大有所悟。\n" NOR, me,
                       this_object());
        command("say 這招再簡單不過，自己下去練吧。");
        tell_object(me, HIC "你學會了「隔山打牛」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("zhenshan-zhang"))
                me->improve_skill("zhenshan-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhenshan-zhang/da", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/wudang-jian/sheng", me) )
                return "你自己去練習吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我們武當派的人，何出此言？";

        if (me->query_skill("wudang-jian", 1) < 1)
                return "你連武當劍法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<80 )
                return "你為我武當派效力還不夠，這招我先不忙傳你。";

        if( query("shen", me)<8000 )
                return "你行俠仗義的事情做的還很不夠，我不能傳你絕招！";

        if (me->query_skill("force") < 80)
                return "你的內功的修為不夠，練高了再來吧。";

        if (me->query_skill("wudang-jian", 1) < 60)
                return "你的武當劍法修為太淺，修煉好了再來吧。";

        if( query("max_neili", me)<300 )
                return "你的內力修為太淺，修煉高了再來吧。";

        message_vision(HIY "$n" HIY "微微一笑，從懷中輕輕取出了一本"
                       "劍譜，指著其中一段對$N" HIY "細\n說良久，$N"
                       HIY "一邊聽一邊點頭。\n" NOR, me, this_object());
        command("say 你懂了嗎？");
        tell_object(me, HIC "你學會了「太極初升」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("wudang-jian"))
                me->improve_skill("wudang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/wudang-jian/sheng", 1, me);
        addn("family/gongji", -80, me);

        return 1;
}
