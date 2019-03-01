#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("金湘玉", ({ "jin xiangyu", "jin", "xiangyu" }));
        set("title", "龍門客棧老板娘");
        set("shen_type", 0);
        set("gender", "女性");
        set("per", 34);
        set("long", "金湘玉是黃土高原一帶有名的大美人。一些達官\n"
                    "貴人，江湖浪子常常在這裡歇息，所以她對這一\n"
                    "帶的一舉一動都了如指掌。\n");
        set("combat_exp", 500);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/xingxiu/obj/fire",
                "/d/city/npc/obj/jiudai",
                "/d/shenfeng/npc/obj/dogrou",
                "/d/shenfeng/npc/obj/hulu",
        }));
        setup();
        carry_object("/d/city/npc/cloth/yan-dress")->wear();
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
        if ( ! ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
        case 0:
                say(CYN "金湘玉笑眯眯地說道：這位" + RANK_D->query_respect(ob)
                  + CYN + "，快請進來喝碗酒吧。\n" NOR);
                break;
        case 1:
                say(CYN "金湘玉說道：喲！這位" + RANK_D->query_respect(ob)
                  + CYN + "快請進，本店有剛出窯的好酒。\n" NOR);
                break;
        }
}