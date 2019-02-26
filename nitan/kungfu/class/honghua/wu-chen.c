#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

void create()
{
        set_name("無塵道長", ({"wuchen daozhang", "wuchen", "daozhang"}));
        set("title", "紅花會二當家");
        set("nickname", HIR "追魂奪命劍" NOR );
        set("gender", "男性");
        set("age", 52);
        set("long", "無塵道人少年時混跡綠林，劫富濟貧，做下\n"
                    "了無數巨案，後因一事萬念懼恢，出家做了\n"
                    "道人。憑自身所創的一套追魂奪命劍威鎮江\n"
                    "湖，後被紅花會老當家於萬亭請出來做了副\n"
                    "手。\n");
        set("attitude", "peaceful");
        set("class", "taoist");
        set("shen_type", 1);
        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 5500);
        set("max_qi", 5500);
        set("jing", 4200);
        set("max_jing", 4200);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 180);
        set("combat_exp", 4000000);
        set("score", 1000000);

        set_skill("force", 240);
        set_skill("honghua-xinfa", 240);
        set_skill("tianchi-neigong", 240);
        set_skill("unarmed", 260);
        set_skill("lianhuan-mizongtui", 260);
        set_skill("dodge", 260);
        set_skill("yanzi-chuanyun", 240);
        set_skill("zhuihun-jian", 260);
        set_skill("parry", 240);
        set_skill("sword", 260);
        set_skill("taoism", 150);
        set_skill("martial-cognize", 220);
        set_skill("literate", 200);

        map_skill("force"  , "tianchi-neigong");
        map_skill("unarmed", "lianhuan-mizongtui");
        map_skill("dodge"  , "lianhuan-mizongtui");
        map_skill("parry"  , "zhuihun-jian");
        map_skill("sword"  , "zhuihun-jian");

        create_family("紅花會", 4, "當家");

        set("inquiry", ([
                "奪命連環" : (: ask_skill1 :),
                "追魂奪命" : (: ask_skill2 :),
                "誅天剎神" : (: ask_skill3 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zhu" :),
                (: perform_action, "sword.zhui" :),
                (: perform_action, "unarmed.lian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();
        
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
    
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<20000 )
        {
                command("say 你非我俠義中人，我不能收你。");
                return;
        }

        if( query("combat_exp", me)<350000 )
        {
                command("say 你的江湖經驗太淺，就算收了你，恐怕也難有作為。");
                return;
        }

        if ((int)me->query_skill("honghua-xinfa", 1) < 80)
        {
                command("say 你內功修煉得太差，下去把本門的心法練好了再來。");
                return;
        }

        if ((int)me->query_skill("sword", 1) < 80)
        {
                command("say 你的劍法練成這樣，叫我如何傳你精深的劍技？");
                return;
        }

        command("haha");
        command("say 既然如此，那你以後就跟着我好了。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/lianhuan-mizongtui/lian", me) )
                return "這招俺不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("lianhuan-mizongtui", 1) < 1)
                return "你連連環迷蹤腿都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<600 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<50000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("dodge") < 150)
                return "你的輕功火候不足，學不成這招。";

        if( query("max_neili", me)<1800 )
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("lianhuan-mizongtui", 1) < 120)
                return "你的連環迷蹤腿還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "大笑數聲，對$N" HIY "説道：“想不到"
                       "你的腿法居然能有如此造\n詣，今日我傳你這招又何妨"
                       "？”説罷，$n" HIY "隨即擺開架勢，慢\n慢的演示招數"
                       "。\n" NOR, me, this_object());

        command("haha");
        command("say 對不義之人一上來就要痛下殺手，絲毫不要留情。");
        tell_object(me, HIC "你學會了「奪命連環」。\n" NOR);

        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("lianhuan-mizongtui"))
                me->improve_skill("lianhuan-mizongtui", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lianhuan-mizongtui/lian", 1, me);
          addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/zhuihun-jian/zhui", me) )
                return "自己下去練，別跟我糾纏個沒完！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("zhuihun-jian", 1) < 1)
                return "你連追魂奪命劍都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<300 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<35000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 120)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<800 )
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("zhuihun-jian", 1) < 100)
                return "你的追魂奪命劍還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "點了點頭，從懷中輕輕取出了一本"
                       "劍譜，指着其中一段對\n$N" HIY "細説良久，$N"
                       HIY "一邊聽一邊點頭。\n" NOR, me, this_object());

        command("nod");
        command("say 這是我早期的得意之作，看似複雜實卻並不難練。");
        tell_object(me, HIC "你學會了「追魂奪命」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("zhuihun-jian"))
                me->improve_skill("zhuihun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhuihun-jian/zhui", 1, me);
          addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/zhuihun-jian/zhu", me) )
                return "多説無益，趕快去練功，以後行俠仗義就靠你們了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本會素無瓜葛，何出此言？";

        if (me->query_skill("zhuihun-jian", 1) < 1)
                return "你連追魂奪命劍都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<1200 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<80000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if( !query("can_perform/zhuihun-jian/zhui", me) )
                return "這招是由「追魂奪命」演化而來，等你通曉那招後再來吧。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<1800 )
                return "你的內力修為不夠，學不成這招。";

        if (me->query_skill("zhuihun-jian", 1) < 160)
                return "你的追魂奪命劍還練得不到家，自己下去練練再來吧！";

        message_vision( HIY "$n" HIY "凝視了$N" HIY "好一會兒，隨即大笑數"
                        "聲，讚道：“不錯，不錯。\n今日我傳你這招，可要看"
                        "好了！”$n" HIY "話音剛落，隨即便一聲\n清嘯，手"
                        "中長劍龍吟不止，迸出萬道光華疾閃而過。頓時只見石"
                        "屑\n飛濺，只聽“嗤”的一聲，$N" HIY "對面的青石"
                        "桌案竟已被$n" HIY "手中\n長劍激盪出的劍芒貫穿，"
                        "磚地尚留下碗口粗的大洞，直看得$N" HIY "目瞪\n口"
                        "呆，半天説不出一句話。\n" NOR, me, this_object());

        command("haha");
        command("say 這招是我生平力作，也不知用它殺了多少奸惡之徒。");
        tell_object(me, HIC "你學會了「誅天剎神」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("zhuihun-jian"))
                me->improve_skill("zhuihun-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhuihun-jian/zhu", 1, me);
          addn("family/gongji", -1200, me);
        return 1;
}
