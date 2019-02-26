//Room: /d/dali/wumeng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","烏蒙村落");
        set("long", @LONG
這裏是山的緩坡，烏夷人搬石去土，把這裏修成一層層階梯狀的
平台，民居分別建在各處平台上，互不連接，各自有石砌圍牆，村中
道路也由石頭鋪成。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "west"    : "/d/dali/wunong",
            "east"    : "/d/dali/caopo",
            "north"   : "/d/dali/wuyiminju1",
            "south"   : "/d/dali/wuyiminju2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19170);
	set("coor/y", -6780);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}