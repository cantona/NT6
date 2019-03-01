//box.c 楠木雕花禮盒
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_open", "open");
}

void create()
{
        set_name(MAG"楠木雕花禮盒" NOR, ({"li he", "box"}));
        set("unit", "個");
        set("value", 50000);
        set("long", 
"這是「俠客行一百」飛雪堂專為新婚夫婦定做的禮盒，
楠木制的盒身，雕著精致的花紋，古色古香。\n");
        set("gift", 1);

        setup();
}

int do_open(string arg)
{
        object me,gift1;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="box"||arg=="li he")
        {
                if(query("gift") == 1)
                {
                        message_vision(HIY "$N輕輕打開禮盒，眼前一亮：哇，好多喜糖，好好吃哦！\n" NOR, me);
                        gift1 = new("/d/city/npc/obj/xitang");
                        gift1->move(me);
                        set("gift", 0);
                        me->start_busy(1);
                }
                else message("vision",HIC"禮盒已經被人打開過了，裡面空空的什麼也沒有。\n" NOR,me);
                return 1;
        }
}

void owner_is_killed()
{
        destruct(this_object());
}