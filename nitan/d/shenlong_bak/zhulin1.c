// /d/shenlong/zhulin1 竹林1
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
面前是一片翠綠的竹林，這兒安靜多了，一陣涼風吹過，竹葉沙沙
作響。偶爾有幾個人走過，都誠惶誠恐的樣子，你不由得倒吸了一口涼
氣，把掛在嘴邊的話又嚥了回去。南面是一個竹房，北面又是一片竹林，
東面是一所竹堂。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "west"  : __DIR__"shibanlu",
                "enter" : __DIR__"qianlong",
                "south" : __DIR__"yaofang",
                "north" : __DIR__"zhulin2",
        ]));
        set("objects", ([
                CLASS_D("shenlong")+"/yin" : 1,
        ]));
        setup();

        replace_program(ROOM);
}
