// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "長廊");
        set("long",  @LONG
這裏是遊府的長廊，不少家丁和僕婦正在四處忙碌。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"xiangfang2",
                "east"  :  __DIR__"changlang3",
                "south" :  __DIR__"neitang",
                "north" :  __DIR__"changlang7",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
