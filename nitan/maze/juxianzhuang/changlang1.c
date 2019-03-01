// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "長廊");
        set("long",  @LONG
這裡是遊府的長廊，不少家丁和僕婦正在四處忙碌。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"beilou",
                "south" :  __DIR__"dayuan",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
