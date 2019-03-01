// Room: /yangzhou/xichuntai.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","熙春台二樓");
        set("long",@LONG
熙春台位于瘦西湖西岸，與蓮花橋遙遙相對。乾隆宸苑卿汪廷璋建，
舊景“春台明月”，為乾隆盛世北郊二十四景之一。傳說曾于此為乾隆
皇帝祝壽，故又名“春台祝壽”。
    樓層上懸“熙春台”大匾，兩列竹簡壁掛，融書法、篆刻于一體，
鐫刻歷代名家歌詠揚州的詩詞和古二十四橋橋名。頂棚三百六十五只竹
編燈籠，入夜五彩繽紛，熠熠生輝。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "down"   : __DIR__"xichuntai",
        ]));
        set("objects", ([
                "/d/city/npc/lady1" : 1,
        ]));
        set("coor/x", -60);
        set("coor/y", 100);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}