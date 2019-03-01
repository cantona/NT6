// Room: /lingzhou/biaoqiyin.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "驃騎營");
        set("long", @LONG
這裡是皇室禁衛軍的駐地，在靈州城西北，驃騎營佔地面積龐大，
北面是營房，南面是小校場，西面緊挨著城牆是一排馬廄，有東營門
和南營門通向皇宮和大街。驃騎營的軍士俱是西夏軍中千挑萬選的猛
士，平時負責皇城外圍的警戒，皇上出巡時便挑起開道護衛的重責，
戰時更是一支生力軍。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaoxiaochang",
                "north" : __DIR__"yinfang",
                "east"  : __DIR__"xidajie",
                "west"  : __DIR__"malan",
        ]));
        set("objects", ([
                __DIR__"npc/xixiabing" :2,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6285);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}