// huoji.c

inherit BUNCHER; 
inherit F_DEALER;

void create()
{
        set_name("藥店伙計", ({ "yaodian huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他是模樣老老實實的年輕人。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/misc/jinchuang",
                "/clone/misc/yangjing",
                "/clone/misc/bicanfeng",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}