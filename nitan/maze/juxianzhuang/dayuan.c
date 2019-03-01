

inherit ROOM;

void  create  ()
{
        set("short",  "大院");
        set("long",  @LONG
你走進聚賢莊大院，院裡栽著幾叢老梅，枝幹甚是虯勁。院角門內
小庭院內，少不了身在洛陽的標志：幾盆挺名貴的牡丹。院子中停了不
少車馬，每一匹牲口都是鞍轡鮮明。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"changlang2",
                "north"  :  __DIR__"changlang1",
                "east"   :  __DIR__"damen",
                "west"   :  __DIR__"zhengting",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("coor/x", -600);
        set("coor/y", 10);
        set("coor/z", 0);
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
