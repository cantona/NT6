#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

mixed ask_skill1();

void create()
{
        set_name("文泰來", ({ "wen tailai", "wen","tailai" }));
        set("title", "紅花會四當家");
        set("nickname", HIW "奔雷手" NOR);
        set("long", "文泰來號稱“奔雷手”，十五歲起浪蕩江湖，\n"
                    "手下不知擊斃過多少神奸巨憝、兇徒惡霸。\n");
        set("gender", "男性");
        set("age", 34);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 150);
        set("combat_exp", 1500000);
        set("score", 10000);

        set_skill("force", 200);
        set_skill("honghua-xinfa", 200);
        set_skill("tianchi-neigong", 200);
        set_skill("strike", 220);
        set_skill("benlei-zhang", 220);
        set_skill("dodge", 200);
        set_skill("hanwang-qingdao", 200);
        set_skill("blade", 200);
        set_skill("yanzi-chuanyun", 200);
        set_skill("parry", 200);
        set_skill("martial-cognize", 180);
        set_skill("literate", 150);

        map_skill("force"  , "tianchi-neigong");
        map_skill("blade"  , "hanwang-qingdao");
        map_skill("strike" , "benlei-zhang");
        map_skill("dodge"  , "yanzi-chuanyun");
        map_skill("parry"  , "benlei-zhang");

        prepare_skill("strike", "benlei-zhang");

        set("coagents", ({
                ([ "startroom" : "/d/kaifeng/hh_houting",
                   "id"        : "zhao banshan" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷喝道："
                                "你給我站住！我們紅花會豈是由得外"
                                "人隨便走動地方？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？給我放下來！" NOR,
        ]));

        create_family("紅花會", 4, "四當家");

        set("inquiry", ([
                "雷霆萬鈞"  : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "strike.lei" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object("/d/wudang/obj/greyrobe")->wear();
    
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<10000 )
        {
                command("say 哼，我文泰來從不收無義之人。");
                return;
        }

        if( query("combat_exp", me)<150000 )
        {
                command("say 你的江湖經驗太淺，就算收了你，恐怕也難有作為。");
                return;
        }

        if ((int)me->query_skill("honghua-xinfa", 1) < 60)
        {
                command("say 你連本門內功心法都沒練好，怎麼習我高深的掌法？");
                return;
        }

        command("haha");
        command("say 不錯，不錯，你以後就跟着我吧。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/benlei-zhang/lei", me) )
                return "這招俺不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素無瓜葛，何出此言？";

        if (me->query_skill("benlei-zhang", 1) < 1)
                return "你連霹靂奔雷掌都沒學，還談什麼絕招可言？";

            if( query("family/gongji", me)<600 )
                return "你在會中所作的貢獻還不夠，這招我不忙傳你。";

        if( query("shen", me)<20000 )
                return "你俠義正事做得不夠，這招我不能傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不成這一招。";

        if (me->query_skill("benlei-zhang", 1) < 120)
                return "你的霹靂奔雷掌還練得不到家，自己下去練練再來吧！";

        message_vision(HIY "$n" HIY "大笑數聲，對$N" HIY "説道：“想不到"
                       "你的掌法居然能有如此造\n詣，今日我傳你這招又何妨"
                       "？”説罷，$n" HIY "隨即擺開架勢，慢\n慢的演示招數"
                       "。\n" NOR, me, this_object());

        command("haha");
        command("say 剛才那些全是這套掌法的精髓，可要給俺記牢了。");
        tell_object(me, HIC "你學會了「雷霆萬鈞」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("benlei-zhang"))
                me->improve_skill("benlei-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/benlei-zhang/lei", 1, me);
          addn("family/gongji", -600, me);

        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;
        
        return 0;
}

void unconcious()
{
        die();
}
