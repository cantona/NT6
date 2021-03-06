// daodianhuoji.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("小夥計", ({ "xiao huoji", "huoji" }));
        set("shen_type", 1);
        set("gender", "男性" );
        set("age", 33);

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/d/beijing/obj/tudao",
                "/d/city/obj/dagger",
                "/d/xingxiu/obj/wandao",
                "/d/city/obj/gangdao",
        }));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
