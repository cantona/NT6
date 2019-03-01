// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("朱丹臣", ({ "zhu danchen", "zhu", "danchen" }));
        set("title", "大理國護衛" );
        set("nickname", CYN "筆硯生" NOR);
        set("long", "他是大理國四大護衛之一。一副書生酸溜溜的打扮行頭。\n");
        set("gender", "男性");
        set("age", 40);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 20);
        set("con", 25);
        set("dex", 25);
        
        set("max_qi", 1800);
        set("max_jing", 1000);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 50);
        set("level", 12);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("kurong-changong", 120);
        set_skill("dodge", 120);
        set_skill("tiannan-bu", 120);
        set_skill("cuff", 120);
        set_skill("jinyu-quan", 120);
        set_skill("strike", 120);
        set_skill("wuluo-zhang", 120);
        set_skill("dagger", 140);
        //set_skill("qingliang-daxuefa", 140);
        set_skill("parry", 120);
        set_skill("literate", 280);
        set_skill("martial-cognize", 140);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        //map_skill("dagger", "qingliang-daxuefa");
        map_skill("parry", "jinyu-quan");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        set("inquiry", ([
                // "透骨釘"   : (: ask_skill1 :),
        ]));

        create_family("段氏皇族", 15, "家臣");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dagger.ding" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        // carry_object("/d/meizhuang/obj/panguanbi")->wield();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("smile");
        command("say 世子殿下何需如此，只要有事吩咐在下一聲便是。");
        command("say 若世子不嫌棄，我這裡倒是有一套筆法可以傳授予你。");

        return;
}

/*
int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "段氏皇族" )
        {
                command("sneer");
                command("say 我與閣下素不相識，不知閣下此話從何說起？");
                return -1;
        }

        if (skill != "qingliang-daxuefa" && skill != "dagger")
        {
                command("say 朱某生平只對筆法一項有所研究，其它功夫所知甚淺。");
                return -1;
        }

        if( !query_temp("can_learn/zhudanchen", ob) )
        {
                command("hehe");
                command("say 既然世子有心習武，在下理當竭盡所能傳授。");
                set_temp("can_learn/zhudanchen", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/qingliang-daxuefa/ding", me) )
                return "我不是已經教給你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和我素無瓜葛，何出此言？";

        if (me->query_skill("qingliang-daxuefa", 1) < 1)
                return "你連我清涼打穴法都未學，怎麼來絕招一說？";

        if( query("family/gongji", me)<400 )
                return "恕在下無禮，王爺吩咐過，不得傳功給無功子弟。";

        if (me->query_skill("force") < 150)
                return "你的內功修為太差，學不了這一招。";

        if( query("max_neili",1, me)<1200 )
                return "你的內力修為太差，學不了這一招。";

        if (me->query_skill("qingliang-daxuefa", 1) < 100)
                return "你清涼打穴法的火候還不夠，回去練練再來吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，伸手將$N" HIY "招到身前，低"
                     "聲在$N" HIY "耳旁嘀咕了半天。然後又拔出腰間鐵扇翻轉數"
                     "下，斜刺而出。似乎是一種頗為獨特的打穴法。\n\n" NOR,
                     me, this_object());

        command("smile");
        command("say 這招並不難練，依世子的悟性很快就可以熟練運用了。");
        tell_object(me, HIC "你學會了「透骨釘」。\n" NOR);
        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("qingliang-daxuefa"))
                me->improve_skill("qingliang-daxuefa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qingliang-daxuefa/ding", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}
*/
