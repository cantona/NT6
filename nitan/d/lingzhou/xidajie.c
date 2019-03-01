// Room: /lingzhou/xidajie.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "西大街");
        set("long", @LONG
這是靈州西大街，街道寬敞而幹凈，青磚砌的路面被雨水沖得光明
如鏡，街道兩側的瓦房高大而宏偉，雙人合抱的楊樹十步一株，整齊地
排在兩邊。大街北面一對大紅燈籠，懸掛在朱門兩旁。這裡就是一品堂
總壇。大街南面有幾家店舖，街道有點冷清。
LONG );
        set("exits", ([
                "south" : __DIR__"daodian",
                "north" : __DIR__"yipingate",
                "east"  : __DIR__"center",
                "west"  : __DIR__"biaoqiyin",
                "northwest"  : __DIR__"ximen",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6275);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
