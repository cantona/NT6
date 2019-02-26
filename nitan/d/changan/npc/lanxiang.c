//lanxiang.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("張蘭香", ({"zhang lanxiang", "zhang", "lanxiang"}));
        set("shop_id",({"laoban","zhanglanxiang","zhang","lanxiang"}));
        set("shop_title", "水果店老闆");
        set("gender", "女性");
        set("combat_exp", 4000);
        set("age", 23);
        set("per", 40);
        set("attitude", "friendly");
        set("shen_type", 1);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set("vendor_goods", ({
                "/d/changan/npc/obj/pingguo",
                "/d/changan/npc/obj/hamigua",
                "/d/changan/npc/obj/juzi",
        }));

        setup();
          carry_object("/d/changan/npc/obj/skirt")->wear();
          add_money("silver", 30);
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");         
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        say("張蘭香笑咪咪地説道：這位" + RANK_D->query_respect(ob) +
            "，新到的各種水果，買點兒回家嚐嚐吧。\n");
}