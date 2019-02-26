// huoji. 藥鋪夥計

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("藥鋪夥計", ({ "yaopu huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他十分強壯，看上去會幾分武功，對藥鋪生意似乎並不在乎。\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/misc/jinchuang",
                "/clone/misc/yangjing",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}