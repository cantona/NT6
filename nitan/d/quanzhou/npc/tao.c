// tao.c
// Last Modified by winder on May. 29 2001

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("陶老人", ({ "tao laoran", "tao", "laoren" }));
        set("gender", "男性");
        set("title", "陶然茶居老板");
        set("age", 53);
        set("long","陶老人是出名的老好人，他賣的茶又香又好，價錢公道，
所以城裡的人都喜歡到他那買茶。\n");
        set("combat_exp", 200);
        set("attitude", "friendly");

        set("vendor_goods", ({
                TEA_DIR+"chabei",
                TEA_DIR+"guanyinchabei",
                TEA_DIR+"longjingchabei",
                TEA_DIR+"molihuachabei",
                TEA_DIR+"xiangpianchabei",
        }));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
