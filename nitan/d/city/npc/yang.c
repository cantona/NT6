// yang.c 楊老闆

inherit BUNCHER;

inherit F_DEALER;

void create()
{
        set_name("楊永福", ({ "yang yongfu", "yang" }));
        set("title", "雜貨鋪老闆");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 45);
        set("long",
                "楊老闆是土生土長的揚州人，做了幾十年的小買賣。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/cloth/cuttonp",
                "/clone/misc/sleepbag",
                __DIR__"obj/mabudai",
                __DIR__"obj/beixin",
                __DIR__"obj/kaolu",
                __DIR__"obj/toukui",
                __DIR__"obj/cycle",
                __DIR__"obj/surcoat",
                __DIR__"obj/shield",
                __DIR__"obj/huwan",
                __DIR__"obj/zhitao",
                __DIR__"obj/huyao",
                __DIR__"obj/caoxie",
                __DIR__"obj/pixue",
                __DIR__"obj/shoutao",
                __DIR__"obj/tieshou",
                __DIR__"obj/jinsijia",
                "/d/xingxiu/obj/fire",
                "/clone/misc/huoba",
                "/d/item/obj/chanhs",
                "/d/city/obj/rrose",
                "/d/city/obj/yrose",
                "/clone/misc/wood",
                "/clone/misc/shoeshine",
                "/clone/misc/brush",
                "/clone/misc/yanhuo",
                "/clone/misc/diaogan",
                "/clone/misc/yuer",
                "/d/taohua/obj/bagua",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_look", "kan");
}
