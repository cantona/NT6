// yang.c 楊老板 

inherit NPC;
//inherit F_VENDOR;
inherit F_DEALER;

void create()
{
        set_name("楊永福", ({ "Yang yongfu", "yang" }));
        set("title", "雜貨舖老板");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 45);
        set("long",
                "楊老板是土生土長的揚州人，做了幾十年的小買賣。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/city/npc/obj/obj/mabudai",
                "/d/city/npc/obj/obj/beixin",
                "/d/city/npc/obj/obj/toukui",
                "/d/city/npc/obj/obj/necklace",
                "/d/city/npc/obj/obj/surcoat",
                "/d/city/npc/obj/obj/shield",
                "/d/city/npc/obj/obj/huwan",
                "/d/city/npc/obj/obj/zhitao",
                "/d/city/npc/obj/obj/huyao",
                "/d/city/npc/obj/obj/caoxie",
                "/d/city/npc/obj/obj/pixue",
                "/d/city/npc/obj/obj/shoutao",
                "/d/city/npc/obj/obj/tieshou",
        }));
        
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}