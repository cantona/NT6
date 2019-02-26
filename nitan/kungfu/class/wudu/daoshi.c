#include <ansi.h>
#include "wudu.h"

inherit NPC;
inherit F_MASTER;
inherit F_DEALER;

mixed ask_me();

void create()
{
        set_name("遊方道人", ({ "dao ren", "dao", "daoren" }) );
        set("gender", "男性" );
        set("age", 34);
        set("long", "一個白淨矮胖的道士，見誰都笑眯眯的，正悠\n"
                    "閒的品着一杯香茶。\n");
        set("max_qi", 1800);
        set("max_jing", 1000);
        set("max_neili", 2000);
        set("neili", 2000);
        set("jiali", 50);
        set("combat_exp", 200000);
        set("attitude", "friendly");

        set_skill("force", 80);
        set_skill("wudu-shengong", 80);
        set_skill("dodge", 80);
        set_skill("wudu-yanluobu", 80);
        set_skill("strike", 80);
        set_skill("tianchan-zhang", 80);
        set_skill("claw", 80);
        set_skill("wusheng-zhao", 80);
        set_skill("parry", 80);
        set_skill("literate", 50);
        set_skill("poison", 80);
        set_skill("wudu-qishu", 80 );
        set_skill("martial-cognize", 60);

        map_skill("force", "wudu-shengong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("claw", "wusheng-zhao");
        map_skill("parry", "wusheng-zhao");
        map_skill("poison", "wudu-qishu");

        prepare_skill("strike", "tianchan-zhang");
        prepare_skill("claw", "wusheng-zhao");

        set("inquiry", ([
                "五毒教"  : (: ask_me :),
                "回去"    : (: ask_me :),
                "回教"    : (: ask_me :),
                "回五毒教": (: ask_me :),
        ]) );

        create_family("五毒教", 13, "護法弟子");

        set("vendor_goods", ([
               "/d/wudu/obj/jiedudan" : 300000,
        ]));

        setup();
        set("startroom", "/d/wudu/neijin");
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 30);
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment() ) return;
        switch(random(3))
        {
        case 0:
                say(CYN "遊方道人嘿嘿一陣奸笑道：這位" + RANK_D->query_respect(ob) +
                    CYN "，也是來住店的嗎？\n" NOR);
                break;
        case 1:
                say(CYN "遊方道人點了點手道：這位" + RANK_D->query_respect(ob) +
                    CYN "請過這裏坐，這是要去那啊？\n" NOR);
                break;
        case 2:
                say(CYN "遊方道人面現驚訝之色道：這位" + RANK_D->query_respect(ob) +
                    CYN "眉現黑氣，近日會有大難。\n遊方道人繼續説道：貧道有一些隨身"
                    "丹丸可以賣給你，或許可救你一命。\n" NOR);
                break;
        }
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-1000 )
        {
                command("say 我教弟子貴在隨心所欲，不收偽君子。");
                return;
        }
        command("recruit "+query("id", ob));
        set("title", "五毒教教眾", ob);
        return;
}

mixed ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "五毒教" )
                return "你大爺的，你羅裏八嗦到底想説啥子？";

        if (find_object(query("startroom")) != environment())
                return "我這裏還有事，你就自己走回去吧。";

        command("say 這位"+ RANK_D->query_respect(me) + "來的正好，這裏"
                "正有馬車要回山辦事，就讓他們送你一程吧。\n");

        message_vision(HIC "遊方道人一招手，一輛馬車駛過來停在門前。\n$N"
                       HIC "急忙鑽進車中，只聽一陣清脆的鞭響，馬車絕塵而"
                       "去。\n\n" NOR, me);

        ob = load_object("/d/wudu/damen");
        ob = find_object("/d/wudu/damen");

        message("vision", HIC "\n遠處一輛馬車急駛而來，車門一開" +
                          query("name", me)+HIC"從裏面鑽了出來"
                          "。\n\n" NOR, environment(me), ({me}));

        me->move("/d/wudu/damen");
        tell_object(me, CYN "\n車把勢説道：這位" + RANK_D->query_respect(me) +
                        CYN "已經到了，請下車吧。\n\n" NOR);
        return 1;

}
