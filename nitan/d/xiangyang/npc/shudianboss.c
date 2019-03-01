// shudianboss.c

inherit BUNCHER;
inherit F_VENDOR;

void create()
{
        set_name("書店老板", ({ "shudian laoban", "boss" }) );
        set("gender", "男性" );
        set("age", 62);
        set("long", "一個讓孩子們一見就覺得可親的老翁。\n");
        set("combat_exp", 3000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/book/parry_book",
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