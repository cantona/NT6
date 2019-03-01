// runyu.c

inherit NPC;
inherit F_DEALER;
#include <ansi.h>;
int do_send(string arg);
void create()
{
        set_name( WHT"潤玉"NOR , ({ "run yu", "yu" }) );
        set("title", MAG"賣花姑娘"NOR );
        set("gender", "女性" );
        set("age",16);
        set("per",23);
        set("combat_exp", 1500);
        set("attitude", "friendly");

        set("vendor_goods", ({
                __DIR__"obj/red_rose",
                __DIR__"obj/yellow_rose",
                __DIR__"obj/yujinxiang",
                __DIR__"obj/kangnaixin",
                "/d/luoyang/npc/obj/chahua",
                "/d/luoyang/npc/obj/lanhua",
                "/d/luoyang/npc/obj/mudan",
                "/d/luoyang/npc/obj/chahua",
                "/d/luoyang/npc/obj/chahua",
        }));

        setup();
        carry_object("/clone/cloth/female-cloth")->wear();
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
        if( !ob || environment(ob) != environment( this_object() ) )
        return;

        if( query("gender", ob) == "女性" )
        {
                if( query("age", ob)<30 )
                {
                        message_vision("賣花姑娘沖$P甜甜一笑：姑娘不買朵鬱金香嗎？\n",ob);
                        return;
                }
        }
        else
        {
                if( query("couple", ob) )
                {
                        message_vision("賣花姑娘沖著$P笑著：不給您的妻子買束花嗎？\n",ob);
                        return;
                }
                else
                {
                        message_vision("賣花姑娘沖著$P笑著：不給心上人買束紅玫瑰嗎？\n",ob);
                        return;
                }
        }
        return;
}
