// lengquanting.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "冷泉亭");
        set("long", @LONG
冷泉亭建在靈隱寺西邊，亭下小溪清澈見底，游魚往復，歷歷可
數。亭邊就是飛來峯。亭柱兩旁有一對聯(duilian)。
LONG);
        set("exits", ([
            "east" : __DIR__"lingyinsi",
        ]));
        set("item_desc", ([
            "duilian" :
"泉          峯
自          從
幾          何
時          處
冷          飛
起          來
？          ？\n"
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 730);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}