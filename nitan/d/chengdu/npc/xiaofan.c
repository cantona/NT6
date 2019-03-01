// Room: /d/chengdu/npc/xiaofan.c
// Last Modifyed by Winder on Jan. 4 2002

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("小販", ({ "xiao fan", "seller", "fan" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "這是個小販，別看他長的老老實實，可你別想從他那兒掏便宜。\n");
        set("shen_type", 1);
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set("vendor_goods", ({
                "/d/village/npc/obj/stick",
                "/d/village/npc/obj/shoes",
                "/d/village/npc/obj/bottle",
                FOOD_DIR"jitui",
                FOOD_DIR"jiudai",
        }) );
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        add_money("coin", 100);
}
void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
