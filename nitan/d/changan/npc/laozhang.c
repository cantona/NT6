//laozhang.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("老張", ({"lao zhang", "zhang", "boss"}));
        set("title", "麪館老闆");
        set("gender", "男性");
        set("age", 35);
        set("qi", 350); 
        set("max_qi", 350);
        set("jing", 200);
        set("max_jing", 200);        
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 10);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set("vendor_goods", ({
                "/d/changan/npc/obj/miantang",
                "/d/changan/npc/obj/miantiao1",
                "/d/changan/npc/obj/miantiao2",
                "/d/changan/npc/obj/miantiao3",
        }));

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
        add_money("silver", 1);
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting())
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
        say("老張熱情地説道：這位" + RANK_D->query_respect(ob) +
            "，進來吃碗熱乎的麪條吧!。\n");
}