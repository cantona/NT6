// Room: /lingzhou/jiangjunyuan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "將軍府大院");
        set("long", @LONG
這裡是將軍府的大院，當面一堵寬闊的白玉照壁，上書“忠心報國”
四個大字，落款是當今西夏皇帝李元昊。一色的青磚舖地，有幾個僕役
正在院中洒掃，南面是內宅，西面是帳房，東面是個小院。
LONG );
        set("exits", ([
//                "east"  : __DIR__"xiaoyuan",
//                "west"  : __DIR__"zhangfang",
//                "enter" : __DIR__"neizai",
                "north" : __DIR__"jiangjungate",
        ]));
        set("no_fight",1);
        set("objects", ([
                "/d/city/npc/jiading" : 2,
        ]));
        set("coor/x", -17950);
        set("coor/y", 32050);
        set("coor/z", 0);
        setup();
        create_door("north" , "油木大門", "south" , DOOR_CLOSED);
//        create_door("south" , "卷簾門", "north" , DOOR_CLOSED);
}