//Edited by fandog, 02/15/2000

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("藥店伙計", ({ "yaodian huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他是藥店掌櫃從鄉下招來幫忙的。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
/*
                "/d/jiangling/obj/danggui",
                "/d/jiangling/obj/lingzhi",
                "/d/jiangling/obj/tianqi",
                "/d/jiangling/obj/hongshen",
                "/d/jiangling/obj/jinchai",
*/
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}