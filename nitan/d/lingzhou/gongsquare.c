// Room: /lingzhou/gongsquare.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "皇宮廣場");
        set("long", @LONG
這裏是皇宮裏的廣場，中間是一條寬闊的青石板路，路的兩邊是
鎧甲鮮明的武士，十步一崗，五步一哨，個個手持長槍大戟，端的氣
勢非凡，西夏的軍力由此可見一斑。南邊是皇宮正門，北面就是議事
大殿。殿門口有兩口大銅缸，儲滿了清水。
LONG );
        set("exits", ([
                "north" : __DIR__"ysdian",
                "south" : __DIR__"gonggate",
        ]));
        set("objects", ([
                __DIR__"npc/gongweishi": 2,
        ]));
        set("outdoors", "xixiagong");
        create_door("south" , "紅漆宮門", "north" , DOOR_CLOSED);
        set("coor/x", -6265);
        set("coor/y", 2955);
        set("coor/z", 0);
        setup();
}
