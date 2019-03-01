// Room: /d/songshan/westting.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "西庭");
        set("long", @LONG
這裡是一個小小庭院，院子裡常有嵩山弟子結伴往來。庭院四周矮
牆下長著的小灌木裡，偶爾冒出幾星白色小花。鵝卵細石舖就的小路在
灌木叢和長草間穿過。
LONG );
        set("outdoors", "songshan");
        set("exits", ([
                "east"  : __DIR__"westpath1",
                "west"  : __DIR__"chufang",
                "north" : __DIR__"westpath2",
                "south" : __DIR__"cangku",
        ]));
        set("objects", ([
                __DIR__"npc/dizi": random(2),
        ]));
        set("coor/x", -40);
        set("coor/y", 900);
        set("coor/z", 90);
        setup();
        create_door("south" , "木門", "north" , DOOR_CLOSED);
}