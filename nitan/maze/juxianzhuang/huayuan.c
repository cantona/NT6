// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這裡是遊府的花園。院子裡種了各色名貴的牡丹。
LONG );
        set("outdoors", "luoyang");
        set("region", "luoyang");

        set("exits", ([
                "north" : __DIR__"xiaofotang",
                "south" : __DIR__"xiangfang1",
                "west"  : __DIR__"yanwuchang",
                "east"  : __DIR__"zhengting",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
