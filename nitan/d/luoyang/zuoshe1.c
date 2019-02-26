//  Room:  /d/luoyang/zuoshe1.c
#include <ansi.h>;
inherit  ROOM;

void  create  ()
{
        set("short",  "左舍");
        set("long",  @LONG
走進小舍，見桌椅几榻，無一而非竹製，一隻竹枝撐起竹窗，涼風
灌入，如仙風入堂。西邊是內進，一層細竹窗簾後，又障了一層輕紗，
你只隱隱約約的見到有個人影，五官面貌卻一點也無法見到。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "southeast"  :  __DIR__"xiaoshe",
                "west"       :  __DIR__"zuoshe2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6960);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}