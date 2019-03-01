// xiaofan.c

inherit KNOWER;
inherit F_DEALER;

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
                "/d/village/npc/obj/stick",
                "/d/village/npc/obj/shoes",
                "/d/village/npc/obj/bottle",
                "/d/village/npc/obj/egg",
                "/d/huanghe/npc/obj/tieqiao",
                __DIR__"obj/butter",
                __DIR__"obj/biandan",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin", 100);
}
void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
