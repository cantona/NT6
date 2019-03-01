// huoji. 藥舖伙計

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("伙計", ({ "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("per", 18);
        set("age", 18);
        set("long", "他是這兒的伙計，正在店裡忙裡忙外。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/city/obj/goupi",
                "/d/city/obj/beixin",
                "/clone/medicine/nostrum/gaoyao",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}