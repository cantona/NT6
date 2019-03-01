// Room: /d/huangshan/wenquan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "溫泉");
        set("long", @LONG
黃山溫泉古稱湯泉，古人雲“紫雲峰下藏太陽，不施爐灶自成湯”，
更兼有醫藥功能名聞天下。因為曾多次湧出紅色泉水，誤為朱砂，所以
又稱朱砂泉，多有山民在此建廬舍，設盆圩，遊人沐浴後，無不精神百
倍。溫泉西上便是慈光閣，北邊遠遠可見觀瀑亭。
LONG
        );
        set("exits", ([ 
                "northup"   : __DIR__"ciguang", 
                "eastup"    : __DIR__"guanpu",
                "southdown" : __DIR__"shanmen", 
        ]));
        set("objects", ([
                __DIR__"obj/tangquan" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -1100);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}