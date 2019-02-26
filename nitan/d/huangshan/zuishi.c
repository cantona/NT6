// Room: /d/huangshan/zuishi.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "醉石");
        set("long", @LONG
這是李白醉酒卧眠的醉石，石上一人形依稀可見，觀其形狀恰似酒
至酣處，石側有醉石二字，筆力遒勁，邊上立有牌坊一座，歷代文人題
字皆在此處。由醉石繼續南行便是試劍石。
LONG
        );
        set("exits", ([ 
                "west"      : __DIR__"shijian",
                "eastup"    : __DIR__"banshan",
                "northdown" : __DIR__"sandie",
                "southeast" : __DIR__"qingluan",
        ]));
        set("objects", ([
                __DIR__"obj/stone2" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -1080);
        set("coor/z", -30);
        setup();
        replace_program(ROOM);
}