#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("阿芳", ({ "afang", "fang" }));
        set("title", "茶僚老闆");
        set("nickname", "荊州老姑娘");
        set("shen_type", 1);

        set("str", 30);
        set("gender", "女性");
        set("age", 20);
        set("long", "阿芳貌似鮮花，可不知道的原因，遲遲不嫁，惹得爺兒們心癢癢。\n");
        set("combat_exp", 500);
        set("attitude", "friendly");
        set("inquiry", ([
                "結婚" : "結婚？你有幾萬兩黃金？？籌夠了來找我吧。嘻嘻！\n",
                "生意" : "這個麼……。還將就。\n",
        ]));
        
        set("vendor_goods", ({
                __DIR__"obj/peanut",
                __DIR__"obj/tofu",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
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
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if ( ! ob || environment(ob) != environment())
                return;

        switch(random(2))
        {
        case 0 :
                say(CYN "阿芳笑眯眯地説道：這位" + RANK_D->query_respect(ob)
                    + CYN + "，快請進來喝杯熱茶。\n" NOR);
                break;
        case 1 :
                say(CYN "阿芳説道：喲！這位" + RANK_D->query_respect(ob)
                    + CYN + "您來了啊！\n" NOR);
                break;
        }
}
