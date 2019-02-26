// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "xuedao.h"

mixed ask_skill1();

void create()
{
        set_name("勝諦", ({ "sheng di", "sheng", "di" }));
        set("long", @LONG
這是一個身形魁梧的西藏僧人，神色冷漠。武
功是同門中最高的一人。
LONG);
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 21);
        set("con", 24);
        set("dex", 22);
        set("max_qi", 5000);
        set("max_jing", 2500);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 30);
        set("combat_exp", 250000);

        set_skill("force", 160);
        set_skill("mizong-neigong", 160);
        set_skill("xuehai-mogong", 160);
        set_skill("parry", 160);
        set_skill("blade", 140);
        set_skill("xuedao-daofa", 140);
        set_skill("sword", 160);
        set_skill("mingwang-jian", 160);
        set_skill("dodge", 160);
        set_skill("shenkong-xing", 160);
        set_skill("hand", 140);
        set_skill("dashou-yin", 140);
        set_skill("cuff", 140);
        set_skill("yujiamu-quan", 140);
        set_skill("lamaism", 160);
        set_skill("literate", 140);
        set_skill("martial-cognize", 100);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("blade", "xuedao-daofa");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ruo" :),
                (: perform_action, "sword.xiang" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
        }) );

        create_family("血刀門", 5, "弟子");
        set("class", "bonze");

        set("inquiry", ([
                // "冰河開封" : (: ask_skill1 :),
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/xuedao/shandong3",
                   "id" : "xuedao laozu" ]),
        }));

        set("master_ob", 4);
        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/clone/weapon/changjian")->wield();

        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("class", ob) != "bonze" )
        {
                set_temp("pending/join_bonze", 1, ob);
                command("say 你不是出家人，我們血刀門是不會收留的。"
                        "如果你要出家，請找善勇師弟。");
                return;
        }

        if( query("shen", ob)>0 )
        {
                command("say 我正想找你們俠義道的晦氣。\n");
                this_object()->kill_ob(ob);
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 50)
        {
                command("say 入我血刀門，修習密宗佛法是首要的。\n");
                return;
        }

        if ((int)ob->query_skill("force") < 70)
        {
                command("say 你這個笨蛋！怎麼不先把內功練好！\n");
                return;
        }

        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/xuedao-daofa/kai", me) )
                return "我不是都已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我血刀門的，再羅嗦我宰了你！";

        if (me->query_skill("xuedao-daofa", 1) < 1)
                return "你連雪山刀法都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<50 )
                return "老祖説了，咋們的絕技不傳無功之人。";

        if( query("shen", me)>-3000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 100)
                return "你的內功修為實在太差，快去多練練再來。";

        if( query("max_neili", me)<600 )
                return "你的內力差成這樣，居然還好意思來找我？";

        if (me->query_skill("xuedao-daofa", 1) < 80)
                return "等你把雪山刀法練熟了再來找我吧。";

        message_vision(HIY "$n" HIY "微微一笑，在$N" HIY "耳邊輕聲嘀咕了幾句，然後"
                       "順手拔出腰\n間的剛刀凌空劈斬了幾下，霎時只見刀光一展而過，"
                       "招式煞\n是驚奇。$N" HIY "看後若有所悟的點了點頭。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 招數便是如此，你看懂了多少？");
        tell_object(me, HIC "你學會了「冰河開封」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuedao-daofa"))
                me->improve_skill("xuedao-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuedao-daofa/kai", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}
