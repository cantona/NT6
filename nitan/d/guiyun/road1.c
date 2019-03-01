// Room: /d/guiyun/road1.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "湖濱小路");
        set("long", @LONG
一條湖濱的荒野小路，岸堤長滿長草，風過處，一陣陣搖頭晃腦。
往西邊遠處看似乎橫著一條小河。東邊是無錫的泰伯廟。
LONG);
        set("outdoors", "guiyun");
        set("objects",([
                __DIR__"npc/youke" : 1,
        ]));  
        set("exits", ([
                "east": "/d/wuxi/taibomiao",
                "west": __DIR__"rivere",
        ]) );
        set("coor/x", 330);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
