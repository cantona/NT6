// Room: /city/jiao.c
// Date: Feb.14 1998 by Java
inherit ITEM;
#include <ansi.h>
void setup()
{}
void init()
{
        add_action("do_enter", "enter");
}
void create()
{
        set_name(CYN"藍呢官轎"NOR, ({"jiao",}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一頂蘭呢大官轎，是揚州知府和成都提督共同出資設立的，往返兩地的快轎。\n");
                set("unit", "頂");
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_drop", 1);
                set("no_put", 1);
        }
        setup();
}
int do_enter(string arg)
{
        object room, me = this_player();
        if( !arg || arg!="jiao" ) return 0;
        message_vision("$N一哈腰掀開轎簾往轎裏鑽進去。\n\n", me ) ;
        if( !(room = find_object("/d/city/obj/jiaonei")) )
            room = load_object("/d/city/obj/jiaonei");
        if( room = find_object("/d/city/obj/jiaonei") ) 
        me->move(room);
        message("vision", me->name() + "從轎外鑽了進來。\n\n",
                environment(me), ({me}) );
        call_out("reach", 20, me);
        return 1;
}        

void reach(object me)
{
        tell_object(me, "突然，轎子頓了一下停了下來，然後有人説: 到了，落轎。\n");
        me->move("/d/city3/eastroad1");
}