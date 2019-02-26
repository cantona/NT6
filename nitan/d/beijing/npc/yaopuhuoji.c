inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("藥鋪夥計", ({ "yaopu huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他十分強壯，看上去會幾分武功，對藥鋪生意似乎並不在乎。\n");
        set("combat_exp", 15000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/beijing/obj/yao1",
                "/d/beijing/obj/yao2",
                "/d/beijing/obj/yao3",
        }));
        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("silver", 5);
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
