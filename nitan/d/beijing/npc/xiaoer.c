// xiaoer.c 小二

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "這位店小二正笑咪咪地忙著，還不時拿起掛在脖子上的抹布擦臉。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小二哥");
        set("vendor_goods", ({
                "/d/city/obj/jitui",
                "/d/city/obj/jiudai",
                "/d/city/obj/baozi",
                "/d/beijing/obj/mian",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{        
        object ob; 
        mapping myfam; 

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) {
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
                                + "，進來吃碗面，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "店小二用脖子上的毛巾抹了抹手，說道：這位" + RANK_D->query_respect(ob)
                                + "，請進請進。\n");
                        break;
        }
}

