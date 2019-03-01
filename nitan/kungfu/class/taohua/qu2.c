// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// qu.c 曲靈風

#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

mixed ask_book1();
mixed ask_book2();
mixed ask_skill1();

#define HETU    "/clone/book/hetu"
#define LUOSHU  "/clone/book/luoshu"

void create()
{
        set_name("曲靈風", ({ "qu lingfeng", "qu", "lingfeng" }));
        set("gender", "男性");
        set("age", 46);
        set("long", "曲靈風是黃藥師的大徒弟，也是黃藥師最得意的徒兒。他\n"
                    "對黃藥師一貫忠心耿耿，尤其是性格古怪，象極了他師父\n"
                    "的邪氣。他身形修長，相貌英俊，白衣飄飄，形容瀟洒。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 30);
        set("int", 24);
        set("con", 27);
        set("dex", 23);
        set("shen_type",1);
        set("max_qi", 4500);
        set("max_jing", 2500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 120);
        set("level", 20);
        set("combat_exp", 1000000);

        set_skill("force", 200);
        set_skill("bibo-shengong", 200);
        set_skill("unarmed", 180);
        set_skill("xuanfeng-tui", 180);
        set_skill("strike", 180);
        set_skill("luoying-shenzhang", 180);
        set_skill("finger", 200);
        set_skill("throwing", 200);
        set_skill("tanzhi-shentong", 200);
        set_skill("dodge", 200);
        set_skill("luoying-shenfa", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("luoying-shenjian", 200);
        set_skill("whip", 200);
        set_skill("canglang-bian", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "bibo-shenfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("finger", "tanzhi-shengong");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("whip", "canglang-bian");
        map_skill("parry", "luoying-shenjian");
        map_skill("sword", "luoying-shenjian");

        prepare_skill("finger", "tanzhi-shentong");

        create_family("桃花島", 2, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sui" :),
                (: perform_action, "finger.jinglei" :),
                (: perform_action, "strike.qimen" :),
                (: perform_action, "unarmed.kuang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "東邪"     : "家師人稱東邪！呵呵。",
                "西毒"     : "歐陽鋒是與家師並世齊名的高手，人稱老毒物。",
                "南帝"     : "聽家師說段王爺現在出家當了和尚，法名一燈。",
                "北丐"     : "北丐洪七公是丐幫幫主，現在揚州城外。",
                "黃蓉"     : "她是師父的愛女。",
                "黃藥師"   : "你要拜訪家師？",
                "桃花島"   : "這兒就是桃花島，你若不是本派弟子，要過桃花陣。",
                "桃花陣"   : "往南就是了。",
                "風雷神劍" : (: ask_skill1 :),
                "河圖"     : (: ask_book1 :),
                "洛書"     : (: ask_book2 :),
        ]));
        set("master_ob", 4);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian");
}

/*
void attempt_apprentice(object ob)
{
        string master;

        if (! permit_recruit(ob))
                return;

        if( stringp(master=query_temp("taohua/master", ob)) )
        {
                if (master != name())
                {
                        command("say 家師不是讓你拜" + master + "的嗎？你怎麼來"
                                "找我來了？");
                        return;
                }
                command("say 好吧，既然家師有令，我就收下你了，不過要好好遵守桃"
                        "花島的規矩。");
                command("recruit "+query("id", ob));
                delete_temp("taohua/master", ob);
                return;
        }

        command("shake");
        command("say 我可不敢擅自收徒，你還是找家師黃島主吧！");
}
*/

void attempt_apprentice(object ob)
{
        string ttt;

        if (! permit_recruit(ob))
                return;
                
        if ((int)ob->query_skill("bibo-shengong", 1) < 60)
        {
                command("say " + RANK_D->query_respect(ob) +
                        "是否還應該在內功修為上多下點功夫？");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 60)
        {
                command("say " + RANK_D->query_respect(ob) +
                        "是否還應該在文學修養上多下點功夫？");
                return;
        }

        if( query("gender", this_player()) == "男性" )
                ttt = "門生";
                
        else if( query("gender", this_player()) == "女性" )
                ttt = "青衣"; 
                
        command("recruit "+query("id", ob));
        set("title", "歸雲莊"+ttt, ob);
        command("say " + "雖然我收你為徒，但我不喜俗務，所以你還是陸師弟的門下，明白了麼？\n");
        command("say " + "以後來這兒，先進密室等我，注意別讓別人發現了。\n");
        return;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/luoying-shenjian/fenglei", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，問這個幹嘛？";

        if (me->query_skill("luoying-shenjian", 1) < 1)
                return "你連落英神劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<120 )
                return "師父吩咐過，不傳功給無功勞的弟子。";

        if (me->query_skill("force") < 120)
                return "你的內功修為不夠，還是多鍛煉鍛煉吧。";

        if (me->query_skill("luoying-shenjian", 1) < 80)
                return "你的落英神劍還不夠熟練，練高了再來找我。";

        message_sort(HIY "\n$n" HIY "看了看$N" HIY "，沒說什麼，隨手從懷中輕輕取"
                     "出了一本劍譜，指著其中一段對$N" HIY "細說良久，$N" HIY "一"
                     "邊聽一邊不住地點頭。\n\n" NOR, me, this_object());

        command("nod");
        command("say 這招並不復雜，你自己下去練吧。");
        tell_object(me, HIC "你學會了「風雷神劍」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("luoying-shenjian"))
                me->improve_skill("luoying-shenjian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/luoying-shenjian/fenglei", 1, me);
        addn("family/gongji", -120, me);

        return 1;
}

mixed ask_book1()
{
        object ob, owner, me = this_player();

        if( !query_temp("taohua/countbook", me) )
                return "對不起，沒師父的允許，書籍恕不外借。";

        ob = find_object(HETU);

        if (! ob) ob = load_object(HETU);
        owner = environment(ob);

        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？那本「河圖」不就是你拿著在看麼？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我師父已將「河圖」借給別人了。";

                if( query("family/family_name", owner) == "桃花島" )
                        return "那本「河圖」現在在我師兄"+query("name", owner)+
                               "手中，你要看就去找他吧。";
                else
                        return "那本「河圖」現在已落到了"+query("name", owner)+
                               "手中，你去找他吧！";
        }
        ob->move(this_object());

        message_vision(CYN "$N" CYN "嘆道：既然是師父的命令，這本「河圖」就"
                       "交給你吧。\n" NOR, this_object(), me);
        command("givehetuto"+query("id", me));
        return 1;
}

mixed ask_book2()
{
        object ob, owner, me = this_player();

        if( !query_temp("taohua/countbook", me) )
                return "對不起，沒師父的允許，書籍恕不外借。";

        ob = find_object(LUOSHU);

        if (! ob) ob = load_object(LUOSHU);
        owner = environment(ob);

        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？那本「洛書」不就是你拿著在看麼？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我師父已將「洛書」借給別人了。";

                if( query("family/family_name", owner) == "桃花島" )
                        return "那本「洛書」現在在我師兄"+query("name", owner)+
                               "手中，你要看就去找他吧。";
                else
                        return "那本「洛書」現在已落到了"+query("name", owner)+
                               "手中，你去找他吧！";
        }
        ob->move(this_object());

        message_vision(CYN "$N" CYN "嘆道：既然是師父的命令，這本「洛書」就"
                       "交給你吧。\n" NOR, this_object(), me);
        command("giveluoshuto"+query("id", me));
        return 1;
}

int accept_fight(object ob)
{
        command("wield jian");
}
