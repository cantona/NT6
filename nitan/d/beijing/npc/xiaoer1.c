inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "er" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "一個笑眯眯的店小二，是全聚德中的夥計。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小二哥");
        set("vendor_goods", ({
                "/d/city/obj/jitui",
                "/d/city/obj/jiudai",
                "/d/city/obj/baozi",
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
                        say( "店小二笑咪咪地説道：這位" + RANK_D->query_respect(ob)
                                + "，歡迎來到全聚德酒樓。\n");
                        break;
                case 1:
                        say( "店小二用脖子上的毛巾抹了抹手，説道：這位" + RANK_D->query_respect(ob)
                                + "，快請進，來吃全聚德的烤鴨嗎？\n");
                        break;
        }
}
