// Room: /d/baihuagu/shanpo1.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIY"山坡"NOR);
        set("long", 
"這是一面山坡，山勢甚為平坦。山坡上有幾間茅屋。\n");
        set("outdoors", "baihuagu");
        set("count", 3);
        set("exits", ([
                "south"    : __DIR__"house2",
                "eastdown" : __DIR__"baihuagu2",
        ]));
        set("objects", ([           
        ]));
        set("no_clean_up", 0);
        set("coor/x", -410);
        set("coor/y", -360);
        set("coor/z", 10);
        setup();
}
void init()
{
        add_action("do_dig","dig");
}
int do_dig(string arg)
{
        object me;
        object food;
        me=this_player();
        if (query("count") > 0)
        {
                message_vision("你挖了一會兒，挖到一顆茯苓。\n",me);
                food=new(VEGETABLE_DIR"fuling");
                food->move(me);
                addn("count", -1);
        }
        else message_vision("你挖了一會兒，沒挖到什麼。\n",me);
        return 1;
}
