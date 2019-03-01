// huangshalin.c
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

int do_move(string arg);

void create()
{
        set("short", "黃沙嶺");
        set("long", @LONG
此處位於終南山西部。只見遠處王曲原上，孤立著一座由荒沙堆積
而成的山嶺，波紋為奇特。據當地人說，這是在商朝，一位名叫陸亞仙
的人，用法力遣來一股黃沙而成。往東是一片密林。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "east" : __DIR__"mumen",
        ]));
        set("coor/x", -3230);
        set("coor/y", 30);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}