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
        set_name("古篤誠", ({ "gu ducheng", "gu", "ducheng" }));
        set("title", "大理國護衛" );
        set("nickname", HIY "忠心耿耿" NOR);
        set("long", "他是大理國四大護衛之一。\n");
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
        set_skill("hammer", 140);
        // set_skill("pangen-cuojiefu", 140);
        set_skill("parry", 120);
        set_skill("literate", 80);
        set_skill("martial-cognize", 140);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        //map_skill("hammer", "pangen-cuojiefu");
        map_skill("parry", "wuluo-zhang");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");
/*
        set("inquiry", ([
                "錯字訣"   : (: ask_skill1 :),
        ]));
*/
        create_family("段氏皇族", 15, "家臣");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.cuo" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("ah");
        command("say 世子殿下何需如此，只要有事吩咐在下一聲便是。");
        command("say 若世子不嫌棄，我這裡倒是有一套斧法可以傳授予你。");

        return;
}
/*
int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "段氏皇族" )
        {
                command("heng");
                command("say 你算什麼人？古某為何要聽命于你？");
                return -1;
        }

        if (skill != "pangen-cuojiefu" && skill != "hammer")
        {
                command("say 我就只有這套斧法拿得出手，其余的還是找你爹爹學吧。");
                return -1;
        }

        if( !query_temp("can_learn/guducheng", ob) )
        {
                command("hehe");
                command("say 既然世子有心習武，在下理當竭盡所能傳授。");
                set_temp("can_learn/guducheng", 1, ob);
        }
        return 1;
}
mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/pangen-cuojiefu/cuo", me) )
                return "這個…這…在下不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和古某素不相識，何出此言？";

        if (me->query_skill("pangen-cuojiefu", 1) < 1)
                return "世子殿下還是先學了在下的盤根錯節斧再說吧。";

        if( query("family/gongji", me)<150 )
                return "這個…不是我不願意…只是王爺吩咐了，無功勞者不得…那個。";

        if (me->query_skill("force") < 120)
                return "這個…世子殿下的內功修為還有待提高。";

        if( query("max_neili",1, me)<800 )
                return "這個…世子殿下的內力修為還有待提高。";

        if (me->query_skill("pangen-cuojiefu", 1) < 100)
                return "世子殿下盤根錯節斧的火候還不夠，尚且用不了這招。";

        message_sort(HIY "\n$n" HIY "對$N" HIY "點了點頭，隨即取出腰"
                     "間大斧，力貫斧柄，陡然間一聲斷喝，接連猛揮數斧"
                     "，威猛中不失精奇，招數巧妙，氣勢如虹。\n\n" NOR,
                     me, this_object()); 

        command("bow");
        command("say 古某才識淺薄，所學僅此而已，讓世子殿下見笑了。");
        tell_object(me, HIC "你學會了「錯字訣」。\n" NOR);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("pangen-cuojiefu"))
                me->improve_skill("pangen-cuojiefu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/pangen-cuojiefu/cuo", 1, me);
        addn("family/gongji", -150, me);
        return 1;
}
*/
