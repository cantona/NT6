//Room: /d/dali/wangfulu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","王府路");
        set("long", @LONG
鎮南王府前大道，延伸兩裏餘。街面是由碗口大的彩色石塊鋪砌
而成，青蘭紫綠，煞是好看。城內居民族裔繁雜，習俗各異，飲食穿
着無不異於中原。太學生們的朗朗之聲透室可聞。北面是一座連雲府
院，‘鎮南’、‘保國’兩面大旗矗立門前。
LONG );
        set("objects", ([
           CLASS_D("dali")+"/fusigui": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "west"   : "/d/dali/paifang",
            "north"  : "/d/dali/wangfugate",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}