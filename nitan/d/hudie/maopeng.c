// 茅棚 maopeng.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "茅棚");
        set("long", @LONG
這裡是一間簡陋的茅棚，裡面堆放著一些幹柴和茅草，看來是用
來生火用的，牆邊靠著一些花鋤和澆水用的水壺。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "north" : __DIR__"xfang2",
            "west" : __DIR__"huapu3",
            "east" : __DIR__"caojing",
        ]));

        setup();
}