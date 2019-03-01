#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("迷路商人", ({ "milu shangren", "milu", "shangren" }));
        set("gender", "男性" );
        set("age", 43);
        set("long", "這是一位迷路的商人，八成是為了尋找蓬萊仙島而迷路的。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        
        set("inquiry", ([
                "蟠桃"       :   "我就是為了蟠桃而來，可惜蟠桃沒找到，卻迷路了，哎 ……。\n",
                "蓬萊仙島"   :   "我為了尋找傳說中的蟠桃，來到這裡，卻迷路了 ……。\n",
        ]));
                
        set("vendor_goods", ({
                "/d/city/obj/jitui",
                "/d/city/obj/jiudai",
                "/d/city/obj/baozi",
                "/d/city/obj/kaoya",
                "/clone/fam/pill/food",
                "/clone/fam/pill/water",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob;

        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        switch(random(2))
        {
        case 0:
                say(CYN "迷路商人笑咪咪地說道：這位" + RANK_D->query_respect(ob) +
                    CYN "，看看有什麼需要的，盡管選。\n" NOR);
                break;
        case 1:
                say(CYN "迷路商人吆喝道：這位" +
                    RANK_D->query_respect(ob) + CYN "，需要什麼盡管說，我這裡價格公道。\n" NOR);
                break;
        }
}
int accept_object(object me, object obj)
{                                
        object ob;
        
        if (obj->query("id") == "penglai pantao" &&
            base_name(obj) == "/d/penglai/obj/pantao")
        {
                command("nod");
                message_vision(HIC "$N" HIC "接過" + obj->name() + HIC "，一臉驚訝道：啊 …… 蟠……蟠桃……實在太感謝了……\n" NOR, this_object());
                message_vision(NOR + CYN "\n$N" NOR "拿出十兩白銀給" + me->name() + NOR + CYN "。\n" NOR, this_object(), me);
                ob = new("/clone/money/silver");
                ob->set_amount(10);
                ob->move(me, 1);
                destruct(obj);
                return 1;
        }
        return 0;        

}