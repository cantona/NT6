// 廂房 xfang2.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "廂房");
        set("long", @LONG
這裡是一間很大的廂房，陳設雖然比較簡陋，但是十分幹凈，擺
放十分別致，靠近牆邊的地方放了一些木床，看來是給求醫的病人住
宿用的。
LONG );

        set("sleep_room", "1");
        set("no_fight", "1");

        set("exits", ([ 
            "north" : __DIR__"chufang",
            "south" : __DIR__"maopeng",
            "east" : __DIR__"maowu",
        ]));

        setup();
}