// xiaofan.c
// Last Modified by winder on May. 29 2001

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("小販", ({ "xiao fan", "fan", "seller" }));
        set("gender", "男性");
        set("age", 35);
        set("long","這是個小販，別看他長的老老實實，可你別想從他那兒掏便宜。\n");
        set("combat_exp", 2800);
        set("attitude", "friendly");

        set("vendor_goods", ({
                "/d/quanzhou/obj/caomao",
                "/d/quanzhou/obj/douli",
        }));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
