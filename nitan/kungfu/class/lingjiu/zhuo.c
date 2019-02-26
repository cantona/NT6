// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>;
#include "etc.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_me();

void create()
{
        set_name("卓不凡", ({ "zhuo bufan", "zhuo", "bufan"}));
        set("gender", "男性");
        set("title", "一字慧劍門門主");
        set("nickname", HIY "劍神" NOR);
        set("age", 37);
        set("long", @LONG
三十三年前，一字慧劍門滿門師徒給童姥殺得
精光，當時卓不凡不在福建，倖免於難，從此
再也不敢回去，逃到長白山中荒僻極寒之地苦
研劍法，無意中得了前輩高手遺下來的一部劍
經，勤練劍法三十餘年，終於劍術大成，自信
天下無敵。
LONG );
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
    
        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 150);
        set("level", 30);
        set("combat_exp", 2200000);

        set_skill("force", 220);
        set_skill("bahuang-gong", 220);
        set_skill("sword", 240);
        set_skill("zhougong-jian", 240);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("strike", 180);
        set_skill("liuyang-zhang", 180);
        set_skill("parry", 220);
        set_skill("martial-cognize", 220);
        set_skill("literate", 180);

        map_skill("force", "bahuang-gong");
        map_skill("sword", "zhougong-jian");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "zhougong-jian");
        map_skill("strike", "liuyang-zhang");

        prepare_skill("strike", "liuyang-zhang");

        set("inquiry", ([
                "劍芒"     : (: ask_me :),
                "周公劍"   : "此乃天下第一劍法。",
                "劍神"     : "論空手，自然是我主公虛竹子第一。但若是論劍法嘛，還得是我。",
                "天山童姥" : "她殺盡我一字慧劍門滿門師徒，幸虧她死得早！",
                "虛竹"     : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
                "虛竹子"   : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
                "劍法"     : "我的周公劍天下無雙，除了主公，沒第二人能夠敵過。",
        ]));

        create_family("一字慧劍門", 3, "門主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mang" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set("master_ob",3);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "靈鷲宮" )
        {
                command("killair");
                command("say 你是什麼東西，竟想習我精妙的劍法！");
                return -1;
        }

        if( query("family/master_id", ob) != "xuzhu zi" )
        {
                command("hmm");
                command("say 恐怕這靈鷲宮裏，還輪不到你説話。");
                return -1; 

        }

        if (skill != "zhougong-jian" && skill != "sword")
        {
                command("hmm");
                command("say 其它武功我不傳授。");
                return -1;
        }

        if (skill == "sword" && ob->query_skill("sword", 1) > 179)
        {
                command("hmm");
                command("say 夠了，剩下的劍法自己去研究。");
                return -1;
        }

        if( !query_temp("can_learn/zhuobufan", ob) )
        {
                command("nod2");
                command("say 既然你感興趣，又是主公的弟子，我就教你這套周公劍。");
                set_temp("can_learn/zhuobufan", 1, ob);
        }
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/zhougong-jian/mang", me) )
                return "我已經説得夠多了，別跟我糾纏不休。";

        if( query("family/family_name", me) != "靈鷲宮" && 
           query("family/family_name", me) != "一字慧劍門" )
                return "哼！不知閣下這話是什麼意思？";

        if (me->query_skill("zhougong-jian", 1) < 1)
                return "你周公劍都未曾練過，還談什麼絕招。";

        if( query("family/family_name", me) == "靈鷲宮" && 
           query("family/gongji", me)<1000 )
                return "主公有令，不得傳功給無功勞的弟子。";

        if (me->query_skill("force") < 200)
                return "你的內功練成這樣，還練什麼劍法！";

        if( query("max_neili", me)<2200 )
                return "你的內力弱成這樣，還練什麼劍法！";

        if (me->query_skill("zhougong-jian", 1) < 140)
                return "你的周公劍火候還差得遠，再回去練練！";

        message_sort(HIY "$n" HIY "更不答話，拔出腰間佩劍，長劍一"
                     "挺，劍尖上突然生出半尺吞吐不定的青芒。當真"
                     "氣勢如虹，一展王者風範。$N" HIY "的目光頓"
                     "時一亮，似乎明白了什麼。\n" NOR, me,
                     this_object());
        command("hmm");
        command("say 看清楚了？");
        tell_object(me, HIC "你學會了「劍芒」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("zhougong-jian"))
                me->improve_skill("zhougong-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhougong-jian/mang", 1, me);
        if( query("family/family_name", me) == "靈鷲宮" )
                addn("family/gongji", -1000, me);
        return 1;
}

/*
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("smile");
        command("say 甚好！甚好！");
        command("say 我一字慧劍門門下無徒，今日老夫便收下你。");
        command("recruit "+query("id", ob));
}
*/

/*
void unconcious()
{
        die();
}
*/
