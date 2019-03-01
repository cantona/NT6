// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "廂房");
        set("long",  @LONG
這裡是遊府的一間廂房，遊氏雙雄的知交好友來府上做客大多居于此
處。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  __DIR__"changlang6",
                "south" :  __DIR__"xiangfang5",
                "north" :  __DIR__"houyuan",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
