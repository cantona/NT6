// qiantang.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "錢塘江畔");
        set("long", @LONG
錢塘江，每年八月十八是觀潮的好日子。“八月十八潮，壯觀天
下無”。潮水來時“遠若素練橫江，聲如金鼓；近則亙如山嶽，奮如
雷霆”，剎那間，漫江沸騰，潑濤萬頃，潮高丈餘，萬馬奔騰，真有
“濤來勢轉雄，獵獵駕長風。雷震雲霓裏，山飛霜雪中”的壯麗氣勢。
西上月輪山便到了六和塔。
LONG);
        set("exits", ([
            "north"     : __DIR__"road17",
            "westup"    : __DIR__"liuheta",
            "eastdown"  : "/d/binghuo/qiantang",
        ]));
        set("objects", ([
            __DIR__"npc/jian-ke" : 1,
        ]));
        set("outdoors", "xihu");
//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}