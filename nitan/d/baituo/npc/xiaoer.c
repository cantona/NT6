// xiaoer.c 酒店小二

inherit F_DEALER;
inherit KNOWER;

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "男性" );
        set("age", 20);
        set("long",
                "這位店小二正笑咪咪地忙著招呼客人。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/baituo/obj/sherou",
                "/d/shaolin/obj/hulu",
        }));
        setup();
}

void init()
{
        object ob;

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
               {
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "店小二笑咪咪地說道：這位" + RANK_D->query_respect(ob)
                                + "，進來喝杯酒，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "店小二用脖子上的毛巾抹了抹手，說道：這位" + RANK_D->query_respect(ob)
                                + "，請進請進，還有雅座。\n");
                        break;
        }

}
