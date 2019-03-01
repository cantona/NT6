// shanlu3.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
小溪橫過山路，跨溪有一座小石橋。溪邊農家小孩在嬉戲玩樂。                    
南上便到了上天竺。北下就是中天竺。
LONG);
        set("exits", ([
            "southup"   : __DIR__"faxisi",
            "northdown" : __DIR__"fajinsi",
        ]));
        set("objects", ([
            __DIR__"npc/boy" : 3,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 750);
	set("coor/y", -2100);
	set("coor/z", 50);
	setup();
}
