//Room: /d/dali/neitang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","內堂");
        set("long", @LONG
這裏是鎮南王府的內堂。十分寬闊明亮。正面牆上掛着一幅水墨
畫，兩邊各有一個窗子，透過窗户可以看見外面的青山綠水。
LONG );
        set("objects", ([
            CLASS_D("duan")+"/duanzc": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/yongdao2",
        ]));
	set("coor/x", -19091);
	set("coor/y", -6811);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}