// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "南樓");
        set("long",  @LONG
這裡是遊府的南樓，遊氏雙雄的知交好友來府上做客大多居于此處。
此次英雄宴邀請的賓客之中，“鐵面判官”單正聲望既高，又與遊氏雙
雄交情匪淺，便將他安頓在這間廂房內暫住。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"changlang4",
                "east"  :  __DIR__"changlang2",
                "north" :  __DIR__"zhengting",
        ]));
        /*
        set("objects",([
                __DIR__"npc/shanzheng" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
