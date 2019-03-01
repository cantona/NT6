// chen.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("陳阿婆", ({ "chen apo", "chen", "apo" }));
        set("title", "雜貨舖老板娘");
        set("shen_type", 1);

        set("str", 20);
        set("gender", "女性");
        set("age", 55);
        set("long",
                "陳阿婆久居泉州城，據說她年輕時很有幾分風韻，福威鏢局\n"
                "當時的少鏢頭林震南還追求過她。\n");
        set("combat_exp", 800);
        set("attitude", "friendly");
        set("inquiry", ([
                "林震南" : "阿南生著那俊，那會琢一個河南七子婆，唉。\n",
                "name" : "婆婆我夫家姓陳。陳林半邊天嘛。\n",
                "here" : "泉州是個港口，會行船的人很多。\n",
        ]));

        set("vendor_goods", ({
                "/d/fuzhou/obj/xiuhua",
                "/d/fuzhou/obj/flower_shoe",
                "/d/fuzhou/obj/pink_cloth",
                "/d/city/obj/goldring",
                "/d/city/obj/necklace",
        }));

        setup();
//        carry_object("/d/city/obj/flower_shoe")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment())
                return;
        switch(random(2))
        {
                case 0 :
                        say("陳阿婆笑眯眯地說道：人客來坐。\n");
                        break;
                case 1 :
                        say("陳阿婆說道：可嘴的，你要買什？\n");
                        break;
        }
}