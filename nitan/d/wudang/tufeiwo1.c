#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "林中小路");
        set("long", @LONG
你走在一條僻靜的林中小路上，兩旁是陰森森的樹林。只見左右
前後，到處都是舖天蓋地的鬆樹林。幾十丈高的大鬆樹簇在一塊，密
實的枝葉象一蓬蓬巨傘恆伸向天空，把陽光遮得絲毫也無。據說這裡
經常有土匪出沒，不可久留。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "south"     : __DIR__"tufeiwo2",
                "northdown" : __DIR__"wdroad10",
        ]));
        set("objects", ([
                __DIR__"npc/tufei2" : 2
        ]));
        set("coor/x", -320);
        set("coor/y", -190);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
