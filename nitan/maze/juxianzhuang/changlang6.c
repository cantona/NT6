// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "長廊");
        set("long",  @LONG
這裡是遊府的長廊，不少家丁和僕婦正在四處忙碌。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"xiangfang3",
                "east"  :  __DIR__"changlang4",
                "south" :  __DIR__"changlang8",
                "north" :  __DIR__"neitang",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
