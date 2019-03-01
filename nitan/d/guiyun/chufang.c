// Room: /d/guiyun/chufang.c
// Last Modified by winder on Jul. 9 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這是歸雲莊的廚房，供應弟子們每日的飯食。屋中充斥著青菜和調
料的味道。幾個廚師正在忙碌著。偶爾會有些吃不完的主食和做菜時剩
下的豬肉留在這裡。
LONG );
        set("exits", ([
                "west" : __DIR__"fanting",
        ]));
        set("objects",([
                __DIR__"obj/meat" : 2,
                __DIR__"obj/baozi" : 1,
                __DIR__"obj/rice" : 1,
                __DIR__"obj/zongzi" : 1,
        ]));
        set("coor/x", 260);
        set("coor/y", -870);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
