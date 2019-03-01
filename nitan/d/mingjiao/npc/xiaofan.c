// xiaofan.c 小販子

inherit KNOWER;
inherit F_DEALER;
#include <ansi.h>

void create()
{
        set_name("小販子", ({ "xiao fan", "xiao", "fan" }) );
        set("gender", "男性" );
        set("age", 34);
        set("long", "這是個小販，別看他長的老老實實，可你別想從他那兒掏便宜。\n");
        set("combat_exp", 300);
        set("attitude", "peaceful");
        set("rank_info/respect", "小販子");
        set("vendor_goods", ({
                "/d/mingjiao/obj/book",
                "/d/village/npc/obj/stick",
                "/d/village/npc/obj/shoes",
                "/d/village/npc/obj/bottle",
        }));
        setup();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch(random(2)){
          case 0:
          say(CYN"小販子笑咪咪地說道：這位"+RANK_D->query_respect(ob)+"，要明教簡史嗎？\n"NOR);
          break;
          case 1:
          break;
        }
}
