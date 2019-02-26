// Code of ShenZhou
// road: /zhongnan/dajiaochang.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"大校場"NOR);

        set("long", @LONG
這是一個位於終南山山腰的圓坪，四周羣山環抱。山腳下有一座
大池。每年臘月，全真派便於此地舉行大校，以考察門下弟子在這一
年間的進境。往南是一條崎嶇的山道。往西是一條通往峯頂的山路。
往北行便是重陽宮。只見遠處十餘幢道觀屋宇疏疏落落的散處山間。
LONG );

        set("exits",([ "north" : "/d/quanzhen/jiaobei",
        ]));

        set("objects", ([
                CLASS_D("quanzhen") + "/zhao" : 1,
        ]));

        set("cost",1);
        set("outdoors", "zhongnan");
        setup();
}

#include "/kungfu/class/quanzhen/beidou.h" 
