// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "廂房");
        set("long",  @LONG
這裏是遊府的一間廂房，遊氏雙雄的知交好友來府上做客大多居於此
處。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  __DIR__"changlang7",
                "south" :  __DIR__"xiangfang2",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
