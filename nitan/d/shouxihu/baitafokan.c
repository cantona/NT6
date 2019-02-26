// Room: /yangzhou/baitafokan.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","白塔佛龕");
        set("long",@LONG
白塔佛龕。塔基方形，磚砌，建於平台上，底為方形折角，四面八
角。下為束腰。磚雕須彌座，每面各置三龕，每龕各磚雕一生肖像，象
徵周天十二時辰。須彌座上有半圓突起的蓮瓣座和承託塔身的環帶形金
剛圖，從而使塔身從方形須彌座自然而柔和地過渡到圓形塔身。塔身形
若古瓶，面南中空，設“眼光門”，內供白衣大士像。
LONG );
        set("exits", ([
                "down" : __DIR__"baitataji",
                "up"   : __DIR__"baitabaosha",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 50);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}