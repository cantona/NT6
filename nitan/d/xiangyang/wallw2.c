// Room: /d/xiangyang/wallw2.c
// Date: Jan. 8 1999 by Winder
// Modified by Zeratul Jan 15 2001,限制了瘋狂爬城

inherit __DIR__"wall.c";

void create()
{
        set("short", "石階");
        set("long", @LONG
這是登向城頭的石階，因為城牆很高，所以很陡。石階兩
側有可供拉車上下的斜坡道。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "southup"   : __DIR__"wallw4",
                "northdown" : __DIR__"westgate1",
        ]));
        set("coor/x", -7860);
	set("coor/y", -780);
	set("coor/z", 10);
	setup();
}