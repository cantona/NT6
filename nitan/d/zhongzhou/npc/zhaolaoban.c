inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("趙德言", ({ "zhao deyan", "zhao", "deyan" }));
        set("title", "雜貨舖老板");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 45);
        set("long", "趙德言是土生土長的中州人，做了幾十年的小買賣。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/cloth/cuttonp",
                "/d/xingxiu/obj/fire",
                "/d/item/obj/chanhs",
                "/clone/misc/wood",
                "/clone/misc/shoeshine",
                "/clone/misc/brush",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}