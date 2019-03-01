// seller.c

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("小販", ({ "seller" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long", "這是個小販，別看他長的老老實實，可你別想從他那兒掏便宜。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("inquiry", ([
                "大力丸" : "看你也是正人君子，怎麼問這個？\n",
        ]) );
        set("vendor_goods", ({
                "/d/village/npc/obj/bottle",
                "/d/village/npc/obj/egg",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin", 100);
}
void init()
{
        object ob;
        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
void greeting(object ob)
{
        if( query("gender", ob) != "女性" )
                say("小販吆喝道：大力丸，大力丸，一夜管睡百姑娘！\n");
        return;
}