#include <ansi.h>
inherit ROOM;
#define QUESTDIR2 "quest/雪山飛狐/復仇篇/"

void create()
{
        set("short","山路");
        set("long", @LONG
一條被捕蛇人踏出的小道，彎彎曲曲的向西北方向的山幽伸展。道旁的雜
草(grass) 高達五尺，遮住了天光。山幽中的一切都顯的陰森幽暗。幾乎使你
分不清前方的道路。
LONG
        );

        set("exits", ([
                "southeast" : __DIR__"slu1",
        ]));
        set("item_desc", ([
                "grass": "這裏雜草(grass)很密，但你似乎可以撥開(push)它們。\n",
                "雜草": "這裏的雜草(grass)很密，但你似乎可以撥開(push)它們。\n"
        ]));
        setup();
}
void init()
{
        add_action("do_push", "push");
}
int do_push(string arg)
{
	  object me=this_player();
        if( arg == "grass" || arg == "茅草" || arg == "草")
        {
        message_vision("$N撥開路邊的雜草，發現了一條向西北的路。\n", this_player());
        if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang") && !random(3))
        {
           set("exits/northwest", __DIR__"houshan_copy");
           remove_call_out("close_path");
           call_out("close_path", 5);
        }
        else if( !query("exits/northwest") )
        {
        set("exits/northwest", __DIR__"houshan");
        remove_call_out("close_path");
        call_out("close_path", 5);
        }
        return 1;
        }
}
void close_path()
{
        if( !query("exits/northwest") ) return;
        message("vision",
"一陣風吹過，雜草晃了晃，又淹沒了向西北的路。\n",
                this_object() );
                delete("exits/northwest");
}
