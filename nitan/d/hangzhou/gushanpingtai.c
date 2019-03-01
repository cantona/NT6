// gushanpingtai.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "孤山平台");
        set("long", @LONG
平台北面有“西湖天下景”亭閣，亭柱兩旁有一對聯(duilian)。
這裡還有曲橋水池，臨池有疊石假山，布置得高低參差，疏密有致。
北邊是下山的路。
LONG);
        set("exits", ([
            "northdown" : __DIR__"gushan",
        ]));
        set("item_desc", ([
            "duilian" :
"山              晴
山              晴
水              雨
水              雨
處              時
處              時
明              好
明              好
秀              奇
秀              奇\n"
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -2040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}