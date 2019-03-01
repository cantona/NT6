//Room: /d/dali/tianweijing.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","天威徑");
        set("long",@LONG
此處據說是三國時蜀漢諸葛孔明第七次擒孟獲之處，孟獲曰：“
公，天威也，吾既降，南人不復反也。”，故此得名。這是一條貫通
南北的大路，南去十裡是喜州城，北上約三十裡可達大理城。
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"road4",
            "south"      : __DIR__"xizhou",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}