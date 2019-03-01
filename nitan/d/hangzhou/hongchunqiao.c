// hongchungqiao.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "洪春橋");
        set("long", @LONG
從這裡可以看到西湖十景之一的雙峰插雲(scenery)。大道通向北
邊，再向西南是通往靈隱寺的路。
LONG);
        set("exits", ([
            "southwest"     : __DIR__"road3",
            "north"         : __DIR__"road4",
        ]));
        set("item_desc", ([
        "scenery" : 
"雙峰，南高峰在西湖之西南，北高峰在西湖之西北。南北遙遙相對，
只見宿雨初收，雙峰隱現在輕風薄霧之中，或濃或淡，時有時無；霧
層飄移，卷舒斷續，變幻無穹。\n",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}