#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "waiter" }));
        set("gender", "男性" );
        set("age", 22);
        set("long", "這位店小二正笑咪咪地忙著，還不時拿起掛在脖子上的抹布擦臉。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");

        set("rank_info/respect", "小二哥");
        set("vendor_goods", ({
                "/clone/food/jitui",
                "/clone/food/jiudai",
                "/clone/food/baozi",
                "/d/city/npc/obj/kaoya",
                "/clone/fam/pill/food",
                "/clone/fam/pill/water",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob;

        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        switch(random(2))
        {
        case 0:
                say(CYN "店小二笑咪咪地說道：這位" + RANK_D->query_respect(ob) +
                    CYN "，進來喝杯茶，歇歇腿吧。\n" NOR);
                break;
        case 1:
                say(CYN "店小二用脖子上的毛巾抹了抹手，說道：這位" +
                    RANK_D->query_respect(ob) + CYN "，請進請進。\n" NOR);
                break;
        }
}
