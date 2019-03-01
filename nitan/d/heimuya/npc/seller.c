#include <ansi.h>

inherit KNOWER;
inherit F_VENDOR;

void create()
{
        set_name("小販", ({ "xiao fan", "xiao", "fan" }));
        set("gender", "男性" );
        set("age", 32);
        set("long", "這是個小販，別看他長的老老實實，可你別\n"
                    "想從他那兒掏便宜。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/xingxiu/obj/fire",
        }));
        set("count", 3);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin", 100);
}

void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy", "buy");
}
