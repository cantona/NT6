// Room: /lingzhou/yinfang.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "營房");
        set("long", @LONG
這裡是驃騎營的營房，一排排木屋煞是齊整, 門口空地許多軍士
們圍成個圈在喧鬧，西夏軍中崇尚勇力，佩服的是英雄，士兵個個都
是彪形大漢。
LONG );
        set("exits", ([
                "south" : __DIR__"biaoqiyin",
        ]));
        set("objects", ([
                __DIR__"npc/xixiabing" :3,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6295);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}