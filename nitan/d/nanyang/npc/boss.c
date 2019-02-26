// Room: /d/nanyang/npc/boss.c
// Last Modified by winder on Nov. 20 2001

#include <ansi.h>;

inherit NPC;
inherit F_DEALER;
void create()
{
        set_name("樊子發", ({ "fan zifa","fan","seller"}) );
        set("gender", "男性" );
        set("age", 46);
        set("long", "樊子發是這間小商號的老闆，寫得一手好字。\n");
        set("chat_chance", 20);
        set("chat_msg", ({
                "樊子發道：“這裏是南陽城。”\n",
                "樊子發道：“南陽城北接中原，南渡漢水，客官想去哪裏呀？”\n",
        }));
        set("chat_chance_combat", 20);
        set("chat_msg_combat",({
                "樊子發喊道：“你幹什麼？如此無理？！！！”\n",
                "樊子發邊打邊喊：“我可是嵩山派的紅人，你竟敢殺我？！！！”\n",
        }) );
        set("inquiry", ([
                "here"   : "這裏是南陽城，南陽諸葛祠，天下聞名耶！",
        ]) );
        set("attitude", "friendly");
        set("rank_info/respect", "老哥");
        set("rank_info/rude","老王八蛋");
        set("vendor_goods", ({
                __DIR__"obj/zheshan",
                __DIR__"obj/jiuhulu",
                __DIR__"obj/jiutan",
                __DIR__"obj/xianbing",
        }) );
        set("combat_exp",100);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
}
void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        message_vision("樊老闆笑嘻嘻地迎上前來，説道：“客官，您來啦？”\n",ob);
}