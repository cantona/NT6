#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("阿慶嫂", ({ "aqing sao", "sao" }));
        set("title", "茶館老板娘");
        set("nickname", "揚州一支花");
        set("shen_type", 1);

        set("str", 30);
        set("gender", "女性");
        set("age", 25);
        set("long",
                "阿慶嫂是揚州城裡有名的大美人，因為爺兒們總喜歡往她這兒逛，\n"
                "所以她對城裡的一舉一動都了如指掌。\n");
        set("combat_exp", 500);
        set("attitude", "friendly");
        set("inquiry", ([
                "阿慶" : "我們家阿慶去北邊做生意去了耶。\n",
                "生意" : "這個麼……。\n",
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

        switch(random(2)) {
        case 0 :
                say("阿慶嫂笑眯眯地說道：這位" + RANK_D->query_respect(ob) +
                        "，快請進來喝杯熱茶。\n");
                break;
        case 1 :
                say("阿慶嫂說道：喲！這位" + RANK_D->query_respect(ob) +
                        "您來了啊！本店有剛炸好的五香花生出售。\n");
                break;
        }
}