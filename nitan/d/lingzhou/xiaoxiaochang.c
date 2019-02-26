// Room: /lingzhou/xiaoxiaochang.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "小校場");
        set("long", @LONG
這裏是驃騎營的小校場，平時軍士們就在這裏操練，地上很平整，
居中是指揮台，有根長達數丈的旗杆，杆頂一面繡着一條紅龍的驃騎
營白色軍旗迎風獵獵作響。平時軍士們一天三練，早上出操，中午出
城練馬術和野戰，晚上則負責皇城外的巡邏。
LONG );
        set("exits", ([
                "north" : __DIR__"biaoqiyin",
        ]));
        set("objects", ([
                __DIR__"npc/xixiabing" :3,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6295);
        set("coor/y", 2925);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}