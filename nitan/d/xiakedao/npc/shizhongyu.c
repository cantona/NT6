// shizhongyu.c 石中玉

inherit NPC;

void create()
{
        set_name("石中玉", ({ "shi zhongyu", "shi", "zhongyu" }));
        set("gender", "男性");
        set("age", 20);
        set("str", 15);
        set("int", 45);
        set("con", 18);
        set("dex", 20);
        set("per", 30);
        set("long", "這是一個年輕公子，大約二十左右歲，面若中秋之月，色如春曉
之花，鬢若刀裁，\n"
            "眉如墨畫，鼻如懸膽，情若秋波，雖怒而時笑，即視而有情。\n");
        set("combat_exp", 30000);
        set("shen_type", 1);
        set("score", 0);
        set("attitude", "peaceful");

        set_skill("unarmed", 30);
        set_skill("force", 30);
        set_skill("blade", 20);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("literate",100);

        set_skill("wuhu-duanmendao", 50);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 5);
        set_temp("apply/damage", 10);
        map_skill("blade", "wuhu-duanmendao");

        set("neili", 200);
        set("max_neili", 200);
        set("jiali", 20);
        set("inquiry", ([
                "俠客島" : "在泉州附近的一個小島。\n",
                "石破天" : "他是我的親兄弟，他現在在俠客島。\n"
                           "你見了他可別忘了帶玄冰碧火酒呀。\n",
//                "hop"    : "她是金磚的女神呀，我很崇拜她啊。\n",
//                "young"  : "他是我的老鄉呀。\n",
//                "host"   : "你太小看我了，誰不知道大名鼎鼎的冷晴人啊。\n",
//                "wind"   : "我久仰他的大名，就是沒見過。\n",
//                "shaw"   : "嘻嘻，我在MUD中到見過他。\n",
//                "aman"   : " 我當然知道了，我見過他呀。\n",
//                "xmo"    : "小莫啊！我們是好朋友呀，我們經常在一起玩。\n",
//                "mudos"  : "哈哈!我們也是好朋友呀! \n",
//                "road"   : "呀！你是誰呀? 怎麼連她都知道哇。她是新月的姐姐呀。\n"
//                           "她可是個好孩子，還是個研究生呢！唉，新月能有她的一半就好了。\n",
//                "xinyue" : "別提他了，一天遊手好閒，一點也不象他的姐姐。\n",
                "叮當"   : "我好久沒見到她了，不知道她現在怎麼樣了。\n",
                "賞善罰惡令" : "有了它，你可以到俠客島學武功呀。\n",
        ]) );
        set("chat_chance", 8);
        set("chat_msg", ({
                "\n石中玉說道: 叮當，你在哪呀，我好想你呀。\n",
                "\n石中玉嘆道: 也不知道我的叮當怎麼樣了。\n",
                "\n石中玉說道: 臘八粥可是好東西...\n",
                "\n石中玉說道: 唉，誰能幫我殺了外面的老頭，兄弟我謝謝你了！\n",

        }) );
        setup();
        carry_object("/d/city/obj/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",1);
}

void init()
{
        object ob;
        ob = this_player();
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}

void greeting(object ob)
{
        int change=0;
        if( !ob || environment(ob) != environment() )
                return;
        message_vision( "\n石中玉哈哈大笑道：我終于看見救我的人來了。\n",this_object());
}

void die()
{
        say("\n石中玉說道：我還有個心願沒了，希望你能幫我照顧叮當！\n");

        message_vision("石中玉喊著叮當的名字，死了！\n", this_object());
        ::die();
}

int accept_object(object who, object ob)
{
        object obn;

        if( !who || environment(who) != environment() )
                return 0;
        if ( !objectp(ob) )
                return 0;
        if ( !present(ob, who) )
                return notify_fail("你沒有這件東西。");

        if( query("id", ob) == "shoupa" )
        {
                remove_call_out("destroy");
                call_out("destroy", 1, who, ob);

                message_vision("\n石中玉感動的熱淚迎眶：終于知道了她的消息了！\n",who);
                obn = new("/d/xiakedao/obj/shane-bu");
                obn->move(who);
                return 1;
        }
}

void destroy(object me, object ob)
{
        destruct(ob);
        return;
}
