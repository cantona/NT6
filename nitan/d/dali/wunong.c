//Room: /d/dali/wunong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","烏弄城");
        set("long", @LONG
此處已到大理的北疆，是烏蒙的珙部的治府，烏蒙屬烏夷，居民
多居於高山上。這裏正處高山之腰，北臨波濤洶湧的大渡河。巷陌皆
用山石壘成，高丈餘，延綿全城。此城不大，四面山上分佈着些烏蒙
民居，有牧人趕着牛羊穿鎮而過。
LONG );
        set("objects", ([
           "/d/dali/npc/wshangfan": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northdown"  : "/d/dali/daduhe",
            "southdown"  : "/d/dali/shanlu1",
            "east"       : "/d/dali/wumeng",
        ]));
	set("coor/x", -19180);
	set("coor/y", -6780);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}