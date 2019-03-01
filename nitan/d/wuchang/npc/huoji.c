//Edited by fandog, 02/15/2000

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("伙計", ({ "huo ji", "huo", "waiter" }) );
        set("gender", "男性" );
        set("age", 17);
        set("long",
                "這位小伙計正笑咪咪地忙著，還不時拿起掛在脖子上的抹布擦臉。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小伙計");
        set("no_get", "1");
        set("vendor_goods", ({
                "/d/jingzhou/obj/donggua",
                "/d/jingzhou/obj/houtou",
                "/d/jingzhou/obj/longfeng",
                "/d/jingzhou/obj/tianma",
                "/d/jingzhou/obj/wuchangyu",
                "/d/jingzhou/obj/xianggu",
                "/d/jingzhou/obj/zzjiayu",
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
                        say("小伙計笑咪咪地說道：這位" + RANK_D->query_respect(ob) + "，您請喝杯茶，歇歇腳□。\n");
                        break;
                case 1:
                        say("小伙計用脖子上的毛巾抹了抹手，說道：這位" + RANK_D->query_respect(ob) + "，您有什麼事？\n");
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

  ob->move("/d/wuchang/hzjie1");
        message("vision","只聽“乒”地一聲，"+query("name", ob)+"被人從四季美裡一腳踢了出來，狼狽萬狀的逃開了。\n",environment(ob),ob);
}