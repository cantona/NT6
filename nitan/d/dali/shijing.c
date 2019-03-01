//Room: /d/dali/shijing.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","石徑");
        set("long", @LONG
你走在大理鎮南王府中的石徑上。路邊長木遮天，微風習習，十
分涼爽。路南是一個碧綠透亮的小湖，水禽遊魚，映影其間。西邊通
向大廳，東面好象是個花園。
LONG );
        set("objects", ([
           "/d/dali/npc/xianhe": 1,
        ]));
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/tingyuan",
            "west"  : "/d/dali/wfdating",
        ]));
	set("coor/x", -19111);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}