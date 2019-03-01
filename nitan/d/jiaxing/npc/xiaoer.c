// xiaoer.c 小二
// Jay 5/23/96

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
        set("no_get", "1");
        set("vendor_goods", ({
                FOOD_DIR"jitui",
                FOOD_DIR"baozi",
                LIQUID_DIR"jiudai",
                __DIR__"obj/yadan",
                __DIR__"obj/zongzi",
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
/*
                if( (myfam=query("family", ob) )
                && myfam["family_name"] == "丐幫"
                && ob->query_skill("begging",1) > 10 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
*/
                {
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(4) ) {
                case 0:
                        say( "店小二笑咪咪地説道：這位" + RANK_D->query_respect(ob) + "，進來喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "店小二用脖子上的毛巾抹了抹手，説道：這位" + RANK_D->query_respect(ob) + "，請進請進。\n");
                        break;
                case 2:
                        say( "店小二熱情地打招呼，説道：這位" + RANK_D->query_respect(ob) + "，嚐嚐我們嘉興的臭鴨蛋吧，很好吃的。\n");
                        break;
                case 3:
                        say( "店小二熱情地打招呼，説道：這位" + RANK_D->query_respect(ob) + "，嚐嚐我們嘉興的特產南湖粽子吧。\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n店小二大喝一聲：你這臭要飯的進來幹什麼？ 給我滾出去！\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);

}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        ob->move("/d/quanzhou/nanhu1");
        message("vision","只聽“乒”地一聲，"+query("name", ob)+"被人從煙雨樓裏一腳踢了出來，狼狽萬狀的逃開了。\n",environment(ob),ob);
}
