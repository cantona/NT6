#include <ansi.h>
inherit ROOM;
int is_chat_room()      { return 1;}
void create()
{
       set("short", HIY "遊戲客服" NOR);
        set("long", @LONG
大家對遊戲種遇到的問題及遊戲發展的意見都可以POST在這裡！
謝謝大家合作。
LONG );

        set("exits", ([
                "out" : "/d/city/kedian",
                "sea" : "/inherit/room/hanghai_room.c",
                "up"  : "/adm/daemons/fairyland_quest/room_door_hj",
        ]));
                set("no_fight", 1);
                set("no_sleep_room",1);
	set("coor/x", 1);
	set("coor/y", 11);
	set("coor/z", 10);
	setup();
        "/clone/board/advice_b"->foo();

}