// oldwoman.c

inherit NPC;

void create()
{
        set_name("老大娘", ({ "old woman", "woman" }) );
        set("gender", "女性" );
        set("age", 63);
        set("long", "一個滿臉風霜之色的老婆婆。\n");
//        set("shen", 1000);
        set("shen_type", 1);
        set("combat_exp", 150);
        set("env/wimpy", 60);
        set("chat_chance_combat", 50 );
//        set("chat_msg_combat", ({
//               "E)7r=P5@#:I1HKDD#!I1HKDD#!\n",
//              "E)7r=P5@#:SPMA7KDD#!9bLl;/HUOB4r=YDD#!\n",
//                (: command, "surrender" :),
//        }) );
        set("str", 13);
        set("dex", 12);
        set("con", 14);
        set("int", 13);
        set("attitude", "friendly");
        set("inquiry", ([
                "雞" : "我那老母雞啊...一定是那幾個不務正業的小流氓乾的。",
                "流氓" : "那幾個小流氓正天不務正業，就在小衚衕裏喝酒賭錢。"
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
                "老大娘傷心的説道：那個天殺的，偷了我的老母雞。\n",
                "老大娘歎了口氣，説道：這是個什麼世道啊。\n",
                "老大娘呆呆的望着雞籠，發起愣來了。\n",
        }) );
        carry_object(__DIR__"obj/cloth")->wear();
        add_money("coin", 100);
}
