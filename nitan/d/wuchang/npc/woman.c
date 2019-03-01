//Edited by fandog, 02/15/2000

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("老板娘", ({ "laoban niang", "woman", "boss" }));
        set("title", HIY"老通城第五代傳人"NOR);
        set("nickname", HIW"漢口一寶"NOR);
        set("shen_type", 1);

        set("str", 30);
        set("gender", "女性");
        set("age", 25);
        set("long","一位年輕女人，略施脂粉，別有一番風韻，她正在灶台上忙活著，一邊還招呼著客人。\n");
        set("combat_exp", 500);
        set("attitude", "friendly");
        set("vendor_goods", ({
           "/d/jingzhou/obj/dongdoufu",
           "/d/jingzhou/obj/doupi",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
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
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment()) return;
        switch(random(2)) {
        case 0 :
                say("老板娘笑眯眯地說道：這位" + RANK_D->query_respect(ob) + "，快請進來喝杯熱茶□。\n");
                break;
        case 1 :
                say("老板娘說道：喲！這位" + RANK_D->query_respect(ob) + "您□麼事？本店有剛煎好的豆皮，香噴噴的□。\n");
                break;
        }
}