//1997-3-10 by qyz
#include <room.h>

inherit DOOR_ROOM;



void create()
{
        set("short","靈芝園");
        set("long",@LONG
這裡便是靈芝園，園牆中央辟了一個八卦門，門呈八角形，旁列八卦圖案，
浮雕鬆鶴，梅鹿圖，牆椽頂上置“雙龍戲珠”雕塑，工藝極其精湛，門後刻“
八卦涵宇宙，雙龍衛乾坤”一聯，園內奇花異草，種類繁多，芳香濃鬱，樹木
蔥蔭，是天師散步納涼休息之所，平時很少有人到這裡來。
LONG);
        set("exits",
        ([
          "south" : __DIR__"xuanyuan_gong",
          "north" : __DIR__"lianhua_tai",
         
                ]));
        create_door("north",([
                        "name" : "小木門",
                        "lock" : "lock001",
                        "status": 3,
                        "id"  : ({ "north","小木門","door"}),
                        "other_side_dir": "south",
                                ]),
                        "south");
        set("outdoors","kongdong");
        set("objects",([
                __DIR__"npc/shouyuan" : 1,
                ]) );
        setup();
}
