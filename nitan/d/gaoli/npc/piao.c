
inherit NPC;
inherit F_DEALER;

void create()
{
   set_name("樸老闆",({ "piao laoban","piao"}) );
        set("gender", "男性" );
        set("age", 32);
   set("long", "這是書鋪的老闆,他的文化水平也是很高的。\n");
   set("shop_id",({ "piao laoban","piao"}) );
   set("combat_exp", 20000);
   set("str", 25);
   set("per", 24);
 
   set("attitude", "peaceful");

        set("vendor_goods", ({
                "/d/gaoli/obj/wenxue",

        }));  
   setup();
    carry_object("/d/gaoli/obj/cloth")->wear();
}

void init()
{
        ::init();

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

