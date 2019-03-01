// chaboshi.c 茶博士□

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("茶博士", ({ "cha boshi", "chaboshi", "boshi" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "這位茶博士一手提著大茶壺，一手拎著抹布，笑咪咪地忙著。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("vendor_goods", ({
                __DIR__"obj/dongtingchun",
                __DIR__"obj/yinzhencha",
                __DIR__"obj/xianglian",
        }));
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
}

void init()
{
        object ob;
        mapping myfam;

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) {
                if( (myfam=query("family", ob) )
                && myfam["family_name"] == "丐幫"
                && ob->query_skill("begging",1) > 10 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
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
        switch( random(2) ) {
                case 0:
                        say( "店小二笑咪咪地說道：這位" + RANK_D->query_respect(ob) + "，進來喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "店小二用脖子上的毛巾抹了抹手，說道：這位" + RANK_D->query_respect(ob) + "，請進請進。\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n店小二大喝一聲：你這臭要飯的進來幹什麼？給我滾出去！\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);

}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        ob->move("/d/yueyang/nanjie");
        message("vision","只聽“乒”地一聲，"+query("name", ob)+"被人從洞賓樓裡一腳踢了出來，狼狽萬狀的逃開了。\n",environment(ob),ob);
}