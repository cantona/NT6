// huoji. 藥舖伙計

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("藥舖伙計", ({ "yaopu huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他是華神醫從鄉下招來幫忙的。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/beijing/obj/yao3",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}