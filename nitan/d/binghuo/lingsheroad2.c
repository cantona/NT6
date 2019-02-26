// Room: /binghuo/lingsheroad2.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在樹林中的小路上，四周僻靜得讓你感到窒息般的異常。密
密層層的樹林遮天蔽日，你甚至聽不到一點蟲鳴。這裏就是靈蛇島？
怎麼沒有其他人呢？
LONG );
        set("outdoors", "lingshe");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"lingsheroad1",
                "eastup"    : __DIR__"lingsheroad3",
        ]));
        set("objects", ([
                __DIR__"npc/liuyun"   : 1,
                __DIR__"npc/miaofeng" : 1,
                __DIR__"npc/huiyue"   : 1,
        ]));
        setup();
        replace_program(ROOM);
}
