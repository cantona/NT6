// duanqiao.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "斷橋");
        set("long", @LONG
斷橋正好在外湖和裏湖的分水點上。這裏亭軒錯落，掩映在綠樹佳蔭之下。
“山明水秀軒扉啟，落日漁歌過裏湖”，就是描述這裏傍晚的景色。在斷橋
上可瀏覽環湖諸山和湖中諸島的風光。每當雪後，站在橋頭，只見一切都被
覆上白雪，玉琢銀鏤的湖山風貌就是西湖十景之一的“斷橋殘雪”。民間神
話“白蛇傳”中的白娘娘和許仙就在這裏相會的。
    過橋往西走便是白堤了。東北邊可通往青石大道。
LONG);
        set("exits", ([
            "northeast" : __DIR__"road9",
            "west"      : __DIR__"baiti",
        ]));
        set("objects", ([
            __DIR__"npc/poorman" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 840);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}