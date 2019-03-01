// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "山道");
        set("long", @LONG
蜿蜒而上的山道漸漸陡峭，高大的林木後面隱隱約約露出天空中
飄盪的飛絮。野花滿徑，花香濃濃繚繞在呼吸裡。耳畔時而想起潺潺
的流水聲，環顧翠綠的山谷，卻又找不見溪流的蹤影。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/yuanyuan-tai",
                "south" : "/d/hangzhou/shandao1",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -1980);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}