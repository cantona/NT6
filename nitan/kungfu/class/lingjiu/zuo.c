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
        set_name("左子穆", ({ "zuo zimu", "zuo", "zimu"}));
        set("gender", "男性");
        set("title", "無量劍派東宗掌門");
        set("age", 54);
        set("long", @LONG
這就是無量劍派東宗掌門左子穆，只見他五十
多歲年紀，身著青衫，作儒生打扮。他腰間佩
有一柄長劍，想必劍法著實了得。
LONG );
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
    
        set("qi", 3800);
        set("max_qi", 3800);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 120);
        set("level", 20);
        set("combat_exp", 2000000);

        set_skill("force", 180);
        set_skill("xiaowuxiang", 180);
        // set_skill("dahai-wuliang", 180);
        set_skill("dodge", 180);
        set_skill("feiyan-zoubi", 180);
        set_skill("sword", 180);
        set_skill("wuliang-jian", 180);
        set_skill("strike", 180);
        set_skill("liuyang-zhang", 180);
        // set_skill("unarmed", 160);
        // set_skill("liuhe-quan", 160);
        // set_skill("claw", 160);
        // set_skill("da-qinna", 160);
        set_skill("parry", 180);
        set_skill("martial-cognize", 160);
        set_skill("literate", 160);

        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "xiaowuxiang");
        map_skill("sword", "wuliang-jian");
        map_skill("parry", "wuliang-jian");
        map_skill("strike", "liuyang-zhang");

        prepare_skill("strike", "liuyang-zhang");

        set("inquiry", ([
                "乾坤無量" : (: ask_me :),
                "虛竹子"   : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
                "虛竹"     : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
        ]));

        create_family("無量劍派", 22, "東宗掌門");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.qian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
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
                command("say 你我素不相識，何談得上“指教”二字？");
                return -1;
        }

        if( query("family/master_id", ob) != "xuzhu zi" )
        {
                command("en");
                command("say 這個…你還是去找你師父學好了。");
                return -1; 

        }

        if (skill != "wuliang-jian" && skill != "sword")
        {
                command("say 我只傳授你一些劍法方面的知識，閣下不學就算了。");
                return -1;
        }

        if( !query_temp("can_learn/zuozimu", ob) )
        {
                command("say 既然閣下是主公身旁的人，我也就恭敬不如從命了。");
                set_temp("can_learn/zuozimu", 1, ob);
        }
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/wuliang-jian/qian", me) )
                return "閣下不是已經練成這招了嗎？";

        if( query("family/family_name", me) != "靈鷲宮" && 
           query("family/family_name", me) != "無量劍派" )
                return "你我素不相識，不知閣下此話是什麼意思？";

        if (me->query_skill("wuliang-jian", 1) < 1)
                return "閣下連無量劍法都未曾學習，何談絕招可言？";

        if( query("family/family_name", me) == "靈鷲宮" && 
           query("family/gongji", me)<300 )
                return "…這個…主公有令，不得傳功給無功勞的弟子。";

        if (me->query_skill("force") < 150)
                return "你的內功火候不足，練不成這招。";

        if (me->query_skill("wuliang-jian", 1) < 100)
                return "你的無量劍法火候未到，練不成這招。";

        message_sort(HIY "$n" HIY "點了點頭，拔出腰間佩帶的長"
                     "劍，手臂一振，當即朝著$N" HIY "“唰唰"
                     "唰唰”連攻四劍，這四劍一氣呵成，去勢極"
                     "快，全然籠罩$N" HIY "的周身要穴。\n" NOR,
                     me, this_object());
        command("nod");
        command("say 這招是無量劍法的精髓，以後可要勤加練習。");
        tell_object(me, HIC "你學會了「乾坤無量」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("wuliang-jian"))
                me->improve_skill("wuliang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/wuliang-jian/qian", 1, me);
        if( query("family/family_name", me) == "靈鷲宮" )
                addn("family/gongji", -300, me);
        return 1;
}

/*
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("nod2");
        command("say 那你以後就跟著我好了。");
        command("recruit "+query("id", ob));
}
*/

/*
void unconcious()
{
        die();
}
*/
