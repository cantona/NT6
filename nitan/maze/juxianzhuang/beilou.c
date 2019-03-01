// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "北樓");
        set("long",  @LONG
這是遊府的北樓，與南樓遙遙相對。這次英雄宴的主賓，“閻王敵”
薛神醫在外廳被眾多江湖豪傑爭相結納，應酬得累了，暫時到這間廂房
來歇息片刻。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"xiaofotang",
                "east"  :  __DIR__"changlang1",
                "south" :  __DIR__"zhengting",
        ]));
        set("objects",([
                "/maze/juxianzhuang/npc/xuemuhua" : 1,
        ]));
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
