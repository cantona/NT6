// baishulin2.c 柏樹林
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "柏樹林");
        set("long", @LONG
你走進了柏樹林的深處，腳下踩著厚厚的落葉，鬆鬆軟軟。這裡
的光線非常陰暗，你幾乎什麼都看不清了。突然一只鬆鼠從你眼前的
樹枝上猛地跳了過去，嚇了你一跳。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northup" : __DIR__"baishulin4",
                "west" : __DIR__"baishulin1",
        ]));
        set("objects", ([
                __DIR__"npc/yunbao" : 1,
        ]));
        set("coor/x", -3130);
        set("coor/y", 30);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}