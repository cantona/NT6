//Room: /d/dali/yuxuguan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","玉虛觀");
        set("long", @LONG
玉虛觀內十分清檢，正中供著張果老、呂洞賓、何香姑等八仙的
塑像，香火繚繞，供桌上擺著些蟠桃。正中放了幾個蒲團。旁邊一個
小間裡擺著桌椅，是玉虛散人休息和授徒的地方。
LONG );
        set("objects", ([
           CLASS_D("duan")+"/daobf": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/yuxuguanqian",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}