// /d/xueshan/obj/lamp.c
//su you deng


#include <ansi.h>

inherit ITEM;
inherit "/d/xueshan/inherit/liquid_container.c";


void create()
{
                object suyou;

        set_name(HIY "酥油燈" NOR, ({"lamp"}));
        set_max_encumbrance(200);
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "盞");
                set("long", "一盞純金打製的酥油燈，做的十分精巧別緻，看上去價值不菲。\n");
                set("value", 100000);
                                set("no_get",1);
        }

                // mark it as a liquid container
                set("liquid/container",1);
                set_max_liquid(5);
                set_current_liquid(0);
                set("liquid/unique",1);
            set("liquid/uniqueid","su you"); 

                setup();

}

void init()
{
        add_action("do_light", "light");
        ::init();
}


int do_light(string arg)
{
        object  me = this_player();
                object  ob = this_object();

        if (!present("fire", me))
                return notify_fail("你要用什麼點火？\n");
        if (!arg)
                return notify_fail("你要點燃什麼？\n");
        if (arg != "lamp")
                return notify_fail("你要點燃什麼？\n");
                if (ob->query_current_liquid() < 5)
                                return notify_fail("燈裏的酥油不夠啦。\n");
                if( query("burning", ob) )
                                return notify_fail("酥油燈已經點着啦。\n");
        message_vision(HIR"$N點燃了燈中的酥油，燈頭冒出小小的一股火焰，散發出淡淡的酥油香。\n"NOR, me);
        set("long", query("long") + HIR"裏面燃着小小的一股火焰。\n"NOR);
        set_temp("marks/油", 1, me);
        set("burning", 1);
        remove_call_out("finish_burn");
        call_out("finish_burn",80+random(80), me);
        return 1;
}

void finish_burn(object me)
{
        int point,i;
                object  ob = this_object();
                object  *inv;

        inv = all_inventory(ob);

                // destory all liquid inside of the lamp
        for( i=0; i<sizeof(inv); i++ ) {
                        destruct(inv[i]);
                }
                ob->set_current_liquid(0);
                set("burning", 0);
        message_vision(HIR"$N中的火焰隨風晃了兩下，終於熄滅了，冒出一股青煙。\n"NOR, ob);
        set("long", "一盞純金打製的酥油燈，做的十分精巧別緻，看上去價值不菲。\n");

}

