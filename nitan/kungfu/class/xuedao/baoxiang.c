// This program is a part of NT MudLIB

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "xuedao.h"

mixed ask_skill1();

void create()
{
        set_name("寶象", ({ "bao xiang", "bao", "xiang" }));
        set("long", @LONG
一個極高極瘦的僧人，倆眼兇芒四射。此人在
血刀老祖門下，最是心狠手辣。
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
        set_skill("xuehai-mogong", 160);
        set_skill("mizong-neigong", 180);
        set_skill("parry", 160);
        set_skill("blade", 160);
        set_skill("xuedao-daofa", 160);
        set_skill("dodge", 160);
        set_skill("shenkong-xing", 160);
        set_skill("hand", 160);
        set_skill("dashou-yin", 160);
        set_skill("cuff", 160);
        set_skill("yujiamu-quan", 160);
        set_skill("sword", 160);
        set_skill("mingwang-jian", 160);
        set_skill("lamaism", 160);
        set_skill("literate", 140);
        set_skill("martial-cognize", 100);

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("no_teach", ([
                "xuedao-daofa" : "血刀大法必須由老祖親傳。",
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.huo" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
        }) );

        create_family("血刀門", 5, "弟子");
        set("class", "bonze");

        set("inquiry", ([
                // "流星火雨" : (: ask_skill1 :),
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/xuedao/shandong3",
                   "id" : "xuedao laozu" ]),
        }));

        set("master_ob", 4);
        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/clone/weapon/gangdao")->wield();

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

        if ((int)ob->query_skill("lamaism", 1) < 40)
        {
                command("say 入我血刀門，修習密宗佛法是首要的。\n");
                return;
        }

        if ((int)ob->query_skill("force") < 75)
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

        if( query("can_perform/honglian-dao/huo", me) )
                return "我不是都已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我血刀門的，再羅嗦我宰了你！";

        if (me->query_skill("honglian-dao", 1) < 1)
                return "你連紅蓮刀法都沒學，還羅嗦什麼？";

        if( query("family/gongji", me)<80 )
                return "老祖說了，咋們的絕技不傳無功之人。";

        if( query("shen", me)>-8000 )
                return "你這樣心慈手軟，就算學會這招又有什麼用？";

        if (me->query_skill("force") < 120)
                return "你的內功修為實在太差，快去多練練再來。";

        if( query("max_neili", me)<800 )
                return "你的內力差成這樣，居然還好意思來找我？";

        if (me->query_skill("honglian-dao", 1) < 80)
                return "等你把紅蓮刀法練熟了再來找我吧。";

        message_vision(HIY "$n" HIY "獰笑數聲，伸手將$N" HIY "招到身前，低聲在$N" HIY
                       "耳旁嘀咕了半\n天。然後又拔出腰刀翻轉數下，斜撩而出。似乎是"
                       "一種頗為\n獨特的刀訣。\n" NOR, me, this_object());

        command("bored");
        command("say 好了，好了。你自己去練吧。");
        tell_object(me, HIC "你學會了「流星火雨」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("honglian-dao"))
                me->improve_skill("honglian-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/honglian-dao/huo", 1, me);
        addn("family/gongji", -80, me);

        return 1;
}
