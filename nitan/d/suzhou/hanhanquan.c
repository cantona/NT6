// Room: /d/suzhou/wanjing.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "憨憨泉");
        set("long", @LONG
在山道西側有一憨憨泉，系南朝梁代高僧憨憨尊者所開鑿，距今一
千四百多年。據説泉眼通海，姑又名“海湧泉”。水甚清冽為“天下第
五泉”。石刻“憨憨泉”三字，系北宋呂升卿所題。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown"   : __DIR__"wanjing",
        ]));
	set("coor/x", 1080);
	set("coor/y", -1030);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}