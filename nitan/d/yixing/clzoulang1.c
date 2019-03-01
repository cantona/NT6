// /d/yixing/clzoulang1.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
寬敞的走廊人來人往，再向內便是總舵的內宅了。西面是間幹雜活
的柴房，向東有個小小的亭子。一些日常守衛的幫眾警惕地注視著每個
人。
LONG );
        set("exits", ([
                "west"  : __DIR__"clchaifang",
                "east"  : __DIR__"clbajiaoting",
                "south" : __DIR__"cldating",
                "north" : __DIR__"clzoulang2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yixing");
        set("coor/x", 279);
	set("coor/y", -1001);
	set("coor/z", -1);
	setup();

        replace_program(ROOM);
}