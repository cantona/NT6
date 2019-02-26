// cuihua.c

inherit NPC;

void create()
{
        set_name("翠蘭",({ "cui lan", "lan" }) );
        set("gender", "女性" );
        set("age", 18);
        set("long", "這是個普普通通的農家少女，看見生人羞的低下了頭。\n");

        set("shen_type", 1);
        set("str", 15);
        set("dex", 18);
        set("con", 15);
        set("int", 17);
        set("combat_exp", 200);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 10);
        set("attitude", "peaceful");
        set("chat_chance",10);
        set("chat_msg",({
        "翠蘭自言自語道：爹爹怎麼還不回來啊，飯都要涼了。\n",
        }));

        setup();
        carry_object("/d/city/obj/cloth")->wear();
        add_money("coin", 150);
        set("inquiry", ([
                "爹爹": "我爹爹上五毒山採藥去了，着麼晚了，也該回家了。\n",
                "五毒山": "五毒山就在村子的東南邊，不過進山要通過桃花峪，除了我爹爹，別人不敢去的。\n",
                "桃花峪": "想進桃花峪啊，那裏終年都有瘴氣瀰漫，除非你也有諸葛行軍散。\n",
                "諸葛行軍散": "全村就我爹爹有這個東西，據説是跟一個叫諸葛什麼的要的。\n",
        ]) );
}