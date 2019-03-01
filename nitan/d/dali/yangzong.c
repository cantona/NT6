//Room: /d/dali/yangzong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","陽宗鎮");
        set("long",@LONG
這裏是強宗部的村鎮，是麼些蠻族的聚居區域，麼些蠻族是擺夷
的一支。此處也是山間的小型平原，北面臨着一片綠水，叫做明湖，
這地方略微偏遠些，但有相當不少的擺夷人生活在附近。西南方有道
路通向其它村鎮。
LONG);
        set("objects", ([
           __DIR__"npc/bshangfan": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "westup"     : __DIR__"shanlu8",
            "northeast"  : __DIR__"nongtian4",
            "southup"    : __DIR__"sanglin",
            "southwest"  : __DIR__"milin",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19020);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}