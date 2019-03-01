// Room: /d/wuxi/road14.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "西驛道");
        set("long", @LONG
這是一條寬闊的大驛道，由于離城市不遠，路兩邊樹林成片，林
蔭間，涼風習習。驛道上一有馬匹疾而過就飛起成片的灰塵。許久才
會散盡。路上的行人大多行色匆匆。向東可以遠遠地看見無錫城的城
頭了。北面是著名的天下第二泉，惠山泉。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"   : __DIR__"road16",
                "east"   : __DIR__"kuaxiqiao",
                "north"  : __DIR__"huishanquan",
        ]));
        set("coor/x", 990);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}