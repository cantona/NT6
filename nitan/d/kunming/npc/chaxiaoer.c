#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("茶小二", ({ "xiao er", "xiao" }));
        set("shen_type", 1);

        set("str", 30);
        set("gender", "男性");
        set("age", 25);
        set("long",
                "這個茶小二正忙着給客人送茶，遞煙。");
        set("combat_exp", 500);
        set("attitude", "friendly");
                
        set("vendor_goods", ({
                __DIR__"obj/yan",
                __DIR__"obj/wan",
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

        if ( interactive(ob = this_player()) && !is_fighting() )
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
        case 0 :
                say (CYN "茶小二熱情的説到：這位" + RANK_D->query_respect(ob) +
                     CYN "，馬上給你上茶。\n" NOR);
                break;
        case 1 :
                say (CYN "茶小二説道：這位" + RANK_D->query_respect(ob) + 
                     CYN "要不要來兩口水煙提提神。\n" NOR);
                break;
        }
}