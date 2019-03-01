// Room: /d/taiwan/chiqiancheng.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "赤嵌城");
        set("long", @LONG
赤嵌城位于台南地區，為台灣府駐所。荷蘭人安平築熱蘭遮城後，
為鞏固政權，乃于一六五三年在台南地區再築新城，與熱蘭遮城互為犄
角，名為普羅文查城，漢人稱之為「赤嵌城」或「紅毛樓」。一六六二
年，國姓爺驅荷，在赤嵌城設東都「承天府治」。
    台灣歸清後，清廷大臣多主張棄守，唯征台將軍施琅力言：「棄之
必釀大禍，留之永固邊圍。」終得保留，隔年，並將台灣府治設于台南
赤嵌城。
LONG );
        set("exits", ([
                "east"  : __DIR__"donganfang",
                "west"  : __DIR__"xidingfang",
                "south" : __DIR__"ningnanfang",
                "north" : __DIR__"zhenbeifang",
        ]));
        set("objects", ([
                __DIR__"npc/bing": 2,
                __DIR__"npc/shilang": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2510);
        set("coor/y", -7050);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
