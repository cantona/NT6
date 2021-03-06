// Room: /d/xiangyang/southgate1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "朱雀內門");
        set("long", 
"這裏是襄陽城的南城門的內城門，只見城門上方是三個大字。因近年
來蒙古屢次侵犯襄陽城，故這兒把守相當嚴密，一些官兵們正在盤查要離
襄陽城的人。兩邊是上城頭的石階，向北進入城區。\n\n"
"                         s________________s         
                        /LLLLLLLLLLLLLLLLLL\\      
    []__[]             ^^||======||======||^^             []__[] 
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏━━━┓_|__|__|__|__|__|__[]==[]    
    []==[]__|__|__|__|__|__|_┃"HIY"襄陽城"NOR"┃__|__|__|__|__|__|_[]==[]  
    []==[]|__|__|__|__|__|__|┗━━━┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|__/      \\|__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__||        |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__| "HIR"朱雀門"NOR" |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]"
"\n\n");
        set("outdoors", "xiangyang");

        set("exits", ([
                "eastup" : __DIR__"walls2",
                "westup" : __DIR__"walls1",
                "south"  : __DIR__"southgate2",
                "north"  : __DIR__"southjie3",
        ]));
        set("objects", ([
                "/quest/quest5/job2/pi3"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7820);
	set("coor/y", -810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}