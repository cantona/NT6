#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "天壇" NOR);
        set("long", @LONG
這裏便是北京城裏的最有名的名勝天壇了。天壇是世界最大的祭
天神壇。天壇南的圍牆呈方型，象徵地，最北的圍牆呈半圓型，象徵
天。南方一座叫圜丘壇，壇呈圓型。壇中心是一塊圓石，外轉共有九
圈扇型石板。當年皇帝們就站在圓壇的中心虔誠地祭祀蒼天。中間一
座叫皇穹宇，通高七丈，是存放天神牌位的地方。著名的祈年殿在最
北方，這是天壇內最宏偉、最華麗的建築，也是傳説想象中的離天最
近的地方。皇帝離開皇穹宇，緩步來到這裏，殺牲焚香和天帝『祕談
』，祈求風調雨順。從天壇轉北通往著名的凡陛橋，向南則是一條大
道，通往永定門，出了永定門便是北京的郊外了。
LONG );
        set("exits", ([
                "south" : "/d/beijing/yongdingdao",
                "north" : "/d/beijing/tiantan_n",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 2,
               "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}