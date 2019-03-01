// seller.c

inherit KNOWER;
inherit F_VENDOR;

void create()
{
        set_name("小販", ({ "seller" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "這是個小販，別看他長的老老實實，可你別想從他那兒掏便宜。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/stick",
                __DIR__"obj/shoes",
                __DIR__"obj/bottle",
                __DIR__"obj/egg",
        }));

        set("chat_msg_chance", 5);
        set("chat_msg", ({
                "小販一邊整理東西一邊嘟囔：別看我平時不走動，消息知道得還不少。\n",
                "小販四周看看，低聲道：今天怎麼這麼太平？\n",
                "小販打了個哈欠，看著你道：不瞞你說，華山村這些大大小小的事情我還知道一點。\n",
        }));

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        add_money("coin", 100);
}

void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}