// Room: /d/huangshan/renzi.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "人字瀑");
        set("long", @LONG
黃山三名瀑之一，又名飛雨泉。人字瀑位於紫雲，硃砂兩峯間的山
坳之中，由於傾泄到半山之時，忽有巨石從山中斜插而出，所以半途一
分為二，形成一個人字，宛若兩條飛舞的玉龍，分道揚鑣，直落崖下。
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"qingluan",
        ]));
        set("objects", ([
                __DIR__"npc/xiangke" : 3,
        ]) );
        set("resources/water",1);
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -1080);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}