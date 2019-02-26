// This program is a part of NT MudLIB

inherit NPC;
inherit F_MASTER;

#include "emei.h"
#include <ansi.h>

mixed ask_back();

void create()
{
        set_name("李明霞", ({ "li mingxia", "li", "mingxia"}));
        set("long", "她是峨嵋派的第四代俗家弟子，平時經常掌管一些"
                    "入門弟子的雜事。\n");
        set("gender", "女性");
        set("age", 23);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "fighter");

        set("str", 24);
        set("int", 20);
        set("con", 21);
        set("dex", 18);

        set("max_qi", 1600);
        set("max_jing", 800);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("level", 10);
        set("combat_exp", 90000);

        set("inquiry", ([
                "上山" : (: ask_back :),
                "back" : (: ask_back :),
        ]));


        set_skill("force", 120);
        set_skill("linji-zhuang", 120);
        set_skill("dodge", 100);
        set_skill("zhutian-bu", 100);
        set_skill("strike", 80);
        set_skill("jinding-zhang", 80);
        set_skill("hand", 60);
        // set_skill("jieshou-jiushi", 60);
        set_skill("parry", 100);
        set_skill("sword", 120);
        set_skill("emei-xinfa", 120);
        set_skill("huifeng-jian", 120);
        set_skill("literate", 100);
        set_skill("mahayana", 100);
        set_skill("buddhism", 100);
        set_skill("martial-cognize", 20);

        map_skill("force","linji-zhuang");
        // map_skill("hand", "jieshou-jiushi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        prepare_skill("strike", "jinding-zhang");

        create_family("峨嵋派", 4, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.xing" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"female-cloth")->wear();
        carry_object(CLOTH_DIR"female-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}

mixed ask_back()
{
        object me;

        me = this_player();

        if (find_object(query("startroom")) != environment())
                return "別什麼都問我，我不知道！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是長腳了嗎？難道上山還要我來抬你？";

        if( query("age", me) >= 118 )
                return "我説你呀，年紀這麼大了還要我帶你上山麼？";

        command("say 好吧，看在同門的分上，我就帶你上山吧。");

        message_vision(HIC "$N" HIC "拉着$n" HIC "的手向山頂上走去。\n\n" NOR,
                       this_object(), me);
        tell_object(me, HIY "你覺得省力多了，毫不費勁的就上了金頂。\n" NOR);

        me->move("/d/emei/jinding");

        message("vision", HIC + name() + HIC "一手拉着" + me->name() +
                          HIC "快步的向山上走去，一會兒就不見影子了。\n" NOR,
                          environment());
        move("/d/emei/jinding");
        me->start_busy();
        call_out("back_to_startroom", 5);
        return 1;
}

void back_to_startroom()
{
        string startroom;

        if (! living(this_object()))
                return;

        if (! stringp(startroom = query("startroom")))
                return;

        if (find_object(startroom) == environment())
                return;

        message_vision(HIC "$N" HIC "頭也不回的急急忙忙走了。\n" NOR,
                       this_object());
        move(startroom);
        message_vision(HIC "$N" HIC "大步流星的趕了過來。\n" NOR,
                       this_object());
}
