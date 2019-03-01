// Room: /huanghe/huanghe_3.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河");
        set("long", @LONG
葛水過了古浪，和源于酒泉西北的洪水河于新城合流。到了這裡，
河水的去勢逐漸加強，挾帶著千萬噸的高原泥沙，勢不可擋地向西南奔
去。由于此處水流湍急，這裡的魚大多肉厚脂豐。名揚天下的黃河大鯉
魚即產于此。
LONG );
        set("exits", ([
                "east" : __DIR__"huanghe_2",
                "northwest" : "/d/yongdeng/yongdeng",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -5000);
        set("coor/y", 450);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}