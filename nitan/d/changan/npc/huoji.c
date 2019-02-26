//huoji.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("小夥計", ({"huo ji"}));
        set("age", 18);
        set("gender", "男性");
        set("long","包子鋪的夥計，懶洋洋的看着你。\n");
        set("shop_title", "包子鋪夥計");
        set("attitude", "friendly");
        set("combat_exp", 10000);
        set("shen_type", 1);
        set("neili", 200);
        set("jiali", 5);
        set_skill("unarmed", 20);
        set_skill("dodge", 60);
        set_skill("parry", 20);
        set("vendor_goods", ({
                "/d/changan/npc/obj/bao1",
                "/d/changan/npc/obj/bao2",                
                "/d/changan/npc/obj/bao3",                
        }));

        setup();
        add_money("silver", 3);
        carry_object("/d/changan/npc/obj/linen")->wear();
}

int accept_fight(object me)
{
        command("say 這位大俠，小人那敢跟您動手啊！\n");
        return 0;
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");         
}

void greeting(object ob)
{
        if (! ob || ! visible(ob) || environment(ob) != environment())
                return;

        say(name()+"帶理不理地説道：這位" +RANK_D->query_respect(ob) +
            "，進來吃幾個包子吧。\n");
}