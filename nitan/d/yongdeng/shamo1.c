// Room: /huanghe/shamo1.c
// Java. Sep 21 1998

#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "沙漠");
        set("long", @LONG
這是一片沒邊際的沙漠，到處是近百米高的巨大沙丘。你一走進來
就彷彿迷了路。地下有個石洞。
LONG );
        set("exits", ([
                "north" : __DIR__"shamo",
                "south" : __DIR__"shamo",
                "east"  : __DIR__"shamo",
                "west"  : __DIR__"shamo",
                "enter" : __DIR__"shidong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16070);
	set("coor/y", 4230);
	set("coor/z", 0);
	setup();
}
void init()
{
        object ob = this_player();
        if( query("water", ob)>10 )
                set("water",query("water",  ob)-10, ob);
        else
                set("water", 0, ob);
        message_vision(HIY"滿天黃沙，$N感到喉嚨冒煙，乾渴難熬！\n"NOR, ob);
}

int valid_leave(object me, string dir)
{
        int total_steps = random(9)+1;
        if ( dir == "north")
                addn_temp("shamo/steps", 1, me);
        if ( dir == "south")
                addn_temp("shamo/steps", -1, me);
        if( query_temp("shamo/steps", me) == total_steps )
        {
                me->move(__DIR__"jingyuan");
                delete_temp("shamo/steps", me);
                tell_object(me, "你走了半天，終於走出了西夏沙漠。\n");
                return -1;
        }
        if( query_temp("shamo/steps", me) == -total_steps )
        {
                me->move(__DIR__"qingcheng");
                delete_temp("shamo/steps", me);
                tell_object(me, "你走了半天，終於走出了西夏沙漠。\n");
                return -1;
             }
        return ::valid_leave(me,dir);
}