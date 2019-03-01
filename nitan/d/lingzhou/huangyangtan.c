// Room: /lingzhou/huangyangtan.c
// Java Sep.23 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "黃羊灘");
        set("long", @LONG
這裡就是靈州西南著名的黃羊灘，本來是黃河邊的一大片水澤鹽
鹼地，黃河水泛濫後退去形成了一大片低窪水灘，上面水草豐盛，春
秋兩季吸引了大批塞北的野生黃羊到這裡來飲水嬉戲，休養生息，成
為塞上一大景觀。
LONG        );
        set("exits", ([
                "north"     : __DIR__"nanmen",
                "southwest" : __DIR__"xiaoba",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/lamb": 1,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6285);
        set("coor/y", 2905);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}