//teawaiter.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("茶館小二",({"waiter","xiaoer","xiao","xiaoer","er"}));
        set("shop_id",({"waiter","xiaoer","xiao","er"}));
        set("shop_title","茶館小二");
        set("gender", "男性");
        set("combat_exp", 1000);
        set("age", 26);
        set("per", 24);
        set("attitude", "friendly");
        set("shen_type", 1);
        set_skill("unarmed", 34);
        set("vendor_goods", ({
                "/d/changan/npc/obj/teapot",
        }));

        setup();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");         
}


void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;
        switch(random(3))
        {
        case 0:
                say("小二兒笑咪咪地説道：這位" +
                    RANK_D->query_respect(ob) +
                    "，進來喝杯茶，歇歇腿吧。\n");
                break;
        case 1:
                say("小二兒用毛巾抹了抹身邊的一張桌子，説"
                    "道：這位" + RANK_D->query_respect(ob) +
                    "，快請進。\n");
                break;
        case 2:
                say("小二兒説道：這位" + RANK_D->query_respect(ob) +
                    "，進來嚐嚐我們新採的茶葉吧。準保您滿意。\n");
                break;
        }
}