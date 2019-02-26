#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "書房" );
        set("long", @LONG
這是一間整潔明亮的書房，四壁都是書架，上面擺滿了各
種書籍，中間一張桌子，放着筆墨紙印。
LONG);
        set("exits", ([
                "east"   :__DIR__"xizoulang1"
                
        ]));
        set("objects",([
                __DIR__"npc/wusangui" : 1,
                __DIR__"obj/pingfeng" : 1,
        ]));
	set("coor/x", -16870);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}