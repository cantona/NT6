// quyuanfenghe.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "曲院風荷");
        set("long", @LONG
走進亭院，只見臨湖一座小榭。柱上有一對聯(duilian)。 依榭
觀湖，只見荷花滿湖，茭荷深處，香遠益清。楊萬裡曾有題詠“畢竟
西湖六月中，風光不與四時同。接天蓮葉無窮碧，映日荷花別樣紅”。
LONG);
        set("exits", ([
            "out"    : __DIR__"quyuanbei",
        ]));
        set("item_desc", ([
            "duilian" :
"\n
        身              眼
        在              明
        荷              小
        香              閣
        水              浮
        影              煙
        中              翠\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 779);
	set("coor/y", -2031);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}