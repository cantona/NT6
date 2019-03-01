// seller.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("小販", ({ "seller" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long", "這位小販子正笑咪咪地來回忙著，還不時招呼過往的客人進來。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/shaolin/obj/hulu",
                "/d/city/obj/zhubang",
                "/d/village/obj/zhujian",
                "/d/xingxiu/obj/fire",
                "/d/suzhou/npc/obj/xianggu",
        }) );
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("coin", 100);
}
void init()
{
        object ob;
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say("小販子笑呵呵說道：這位" + RANK_D->query_respect(ob) + "，您想要點什麼？\n");
        return;
}
