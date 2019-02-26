// Room: /d/xiangyang/northgate1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "玄武內門");
        set("long", 
"這裏是襄陽城的北城門的內城門，只見城門上方是三個大字。因近年來
蒙古屢次侵犯襄陽城，故這兒把守相當嚴密，一些官兵們正在盤查要離襄陽
城的人。兩邊是上城頭的石階，向南進入城區。\n\n"
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
    []==[]_|__|__|__|__|__|__| "HIB"玄武門"NOR" |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]\n\n"
);
        set("outdoors", "xiangyang");

        set("exits", ([
                "eastup" : __DIR__"walln1",
                "westup" : __DIR__"walln2",
                "south"  : __DIR__"northjie",
                "north"  : __DIR__"northgate2",
        ]));
        set("objects", ([
              "quest/quest5/job2/pi1"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7810);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}