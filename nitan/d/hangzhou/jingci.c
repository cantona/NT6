// jingci.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "凈慈寺");
        set("long", @LONG
凈慈寺有前，中，後三殿，以中間的大雄寶殿最為壯觀。大雄寶殿，
外觀兩層，黃色琉璃瓦屋頂，特別顯的精美宏偉。寺廊的鐘聲在蒼煙暮
靄中回盪，抑揚動聽，這就是西湖十景之一“南屏晚鐘”的來歷。
LONG);
        set("exits", ([
            "out"   : __DIR__"jingcisi",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 799);
	set("coor/y", -2101);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}