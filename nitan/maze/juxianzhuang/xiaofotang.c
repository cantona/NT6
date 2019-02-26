// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "小佛堂");
        set("long",  @LONG
遊氏兄弟並非出身佛門，卻也在家中蓋了一座小佛堂，供奉佛祖和菩
薩。這次廣開英雄宴，少林寺玄寂大師率弟子前來赴會，正好暫居於
此。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"changlang3",
                "east"  :  __DIR__"beilou",
                "south" :  __DIR__"huayuan",
        ]));
        /*
        set("objects",([
                __DIR__"npc/xunji" : 1,
                __DIR__"npc/xunnan" : 1,
                __DIR__"npc/sengren" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
