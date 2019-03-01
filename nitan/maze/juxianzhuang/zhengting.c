// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "遊府正廳");
        set("long",  @LONG
這是一間頗為寬闊的廳堂，沒有什麼太多的裝飾，只在北面牆上掛了
一幅名家所繪的《百馬圖》，暗合此間主人的名字。正廳當中擺了一
張紅木茶幾，左右各放了一張太師椅，椅上坐的二人便是這座宅院的
主人，遊氏雙雄。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"huayuan",
                "east"  :  __DIR__"dayuan",
                "south" :  __DIR__"nanlou",
                "north" :  __DIR__"beilou",
        ]));
        /*
        set("objects",([
                __DIR__"npc/youju" : 1,
                __DIR__"npc/youji" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
