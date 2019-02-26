// huoji. 藥鋪夥計

inherit BUNCHER;
inherit F_DEALER;

void create()
{
        set_name("藥鋪夥計", ({ "yaopu huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他是蘇州鄉下小夥子。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/medicine/nostrum/jinchuang",
                "/clone/medicine/nostrum/yangjing",
                "/clone/medicine/nostrum/zhujingchan",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
