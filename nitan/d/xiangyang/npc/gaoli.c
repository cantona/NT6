// gaoli.c

inherit BUNCHER;
//inherit F_VENDOR;
inherit F_DEALER;

void create()
{
        set_name("高麗商", ({ "gaoli shang", "shang" }));
        set("title", "新羅坊老闆");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 45);
        set("long",
                "這是個高麗商人，長得和中國人沒啥區別。連賣的東西也差不多。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/city/npc/obj/mabudai",
                "/d/city/npc/obj/beixin",
                "/d/city/npc/obj/toukui",
                "/d/city/npc/obj/cycle",
                "/d/city/npc/obj/surcoat",
                "/d/city/npc/obj/shield",
                "/d/city/npc/obj/huwan",
                "/d/city/npc/obj/zhitao",
                "/d/city/npc/obj/huyao",
                "/d/city/npc/obj/caoxie",
                "/d/city/npc/obj/pixue",
                "/d/city/npc/obj/shoutao",
                "/d/city/npc/obj/tieshou",
                "/d/city/npc/obj/jinsijia",
                "/d/xingxiu/obj/fire",
        }));
        
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
