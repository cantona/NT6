//Room: /d/dali/badidian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","巴的甸");
        set("long",@LONG
這裏就是大理西部要鎮巴的甸，是烏夷的重要治府，多個烏夷部
落分佈在附近。坐於東瀘水谷地正中，巴的甸四周多農田，以此為中
心，道路四通八達連接各方的部落。
LONG);
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"zhenxiong",
            "south"      : __DIR__"lushui",
            "eastup"     : __DIR__"lushuieast",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19210);
	set("coor/y", -6870);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}