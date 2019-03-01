// fengqi.c

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("鳳七", ({ "feng qi", "feng", "qi" }) );
        set("gender", "男性" );
        set("title", "酒樓老板" );
        set("age", 42);
        set("long", @LONG
鳳七是鳳天南的遠房祖弟，在這英雄樓當掌櫃。武功沒有什麼，為人
卻極是機靈，江湖上大大小小的事情都知道一些
LONG );
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("rank_info/respect", "七哥");
        set("vendor_goods", ({
                "/clone/food/jitui",
                "/clone/food/jiudai",
                "/clone/food/baozi",
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
        if (interactive(ob) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;
        switch (random(2))
        {
                case 0:
                        say( "鳳七笑咪咪地說道：這位" + RANK_D->query_respect(ob)
                                + "，進來喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "鳳七笑咪咪地說道：這位" + RANK_D->query_respect(ob)
                                + "，快請進。\n");
                        break;
        }
}

void unconcious()
{
        die();
}