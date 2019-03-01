inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","韋府大門");
        set("long", @LONG
這裡便是當朝第一寵臣，被康熙帝御封為『一等鹿鼎公』的韋公
爺的居宅。來到這裡，一座富麗堂皇的高大建築出現在你的眼前，大
門兩側是兩頭高大的石獅子。門上橫著一塊大匾，上面是大學士索額
圖親筆提寫的『鹿鼎公府』四個金筆大字。門前站著個韋府的侍衛。
LONG );
        set("exits", ([
                "west" : "/d/beijing/weifu_zoulang1",
                "east" : "/d/beijing/wang_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/lilishi" : 1,
        ]));
	set("coor/x", -2790);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("li lishi", environment(me))) && dir == "west")
                return notify_fail("李力世喝道：別亂逛，公爺今天不見客。\n\n");
        return ::valid_leave(me, dir);
}