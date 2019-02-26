//  Room:  /d/luoyang/zuoshe2.c
#include <ansi.h>;
inherit  ROOM;

void  create  ()
{
        set("short",  "內進");
        set("long",  @LONG
走進內進，見桌椅几榻，無一而非竹製。竹几上擺着一具瑤琴，幾
後端坐一妙齡少女，玉手輕撥，曼妙琴聲便自手傍輕輕升起。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"       :  __DIR__"zuoshe1",
        ]));
        set("objects",  ([
                CLASS_D("riyue")+"/ren" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}