// /d/shenlong/shibanlu 石板路
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "青石板路");
        set("long", @LONG
一條幽靜的青石板路，一頭通向大廳，一頭通向竹林，路旁放著幾
盆花卉，開著菊花、薔薇等，煞是艷麗。南面是仙福居，北面是伙房。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "south" : __DIR__"xianfuju",
                "north" : __DIR__"huofang",
                "west" : __DIR__"dating",
                "east" : __DIR__"zhulin1",
        ]));
        set("objects", ([
                CLASS_D("shenlong")+"/zhong" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
