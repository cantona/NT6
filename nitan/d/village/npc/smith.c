// smith.c

inherit "/inherit/char/smith.c";

void create()
{
        set_name("馮鐵匠", ({ "feng", "smith" }) );
        set("gender", "男性" );
        set("age", 53);
        set("long", 
"馮鐵匠想是常年彎腰打鐵，背已駝了，雙眼被煙火薰的又紅又細，\n"
"左腿殘廢，肩窩下撐著一根枴杖。\n");
        set("combat_exp", 50000);

        set("str", 24);
        set("dex", 17);
        set("con", 28);
        set("int", 27);
        set("shen_type", 1);

        set("attitude", "friendly");
        set_skill("dodge", 70);
        set_skill("hammer", 40);
        set_skill("parry", 60);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);

        set("vendor_goods", ({
                __DIR__"obj/hammer",
        }));

        set("inquiry", ([
                "name": "小人姓馮，村裏人都叫我馮鐵匠。",
                "here": "這裏是小人餬口的鋪子，小人就住在後邊的屋子。",
                "鋤頭": "鋤頭... 抱歉，鋤頭已經賣光了...",
                "鐵錘": "鐵錘？小人做的鐵錘堅固又耐用，一把只要三百文錢。",
                "劍"  : "哦，那是給華山派嶽掌門打的，小人用了三個月，總算沒浪費那塊好鐵。\n"
                "嗯，嶽掌門前不久率門徒下山去了，不知什麼時候才會派人來取劍。",
                "取劍": "小人一定要見了嶽掌門的手信才能給劍。",
                "工作" : (: ask_me :),
                "job"  : (: ask_me :),
        ]));

        setup();
        add_money("coin", 50);
        carry_object(__DIR__"obj/hothammer")->wield();
}

void init()
{
        ::init();
        add_action("do_buy", "buy");
}

int accept_object(object who, object ob)
{
        object sword;

        if( query("id", ob) == "handletter" )
        {
                destruct(ob);
                if (! query("yl_trigger"))
                {
                        sword = new(__DIR__"obj/youlong");
                        say("馮鐵匠説道：這把劍雖不起眼，可也是小人的心血，總算對得起嶽掌門。\n"
                            "馮鐵匠把"+query("name", sword)+"交給了"+query("name", who)+"。\n");
                        sword->move(who, 1);
                        set("yl_trigger", 1);
                } else
                        say("馮鐵匠眼也不抬，説道：要劍自己進去拿。\n");
                return -1;
        }
        return 0;
}