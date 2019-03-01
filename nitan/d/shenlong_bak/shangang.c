// 山崗 /d/shenlong/shangang
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "山崗");
        set("long", @LONG
這是一個亂石崗，野草叢生，亂石成堆，顯得很荒涼，石縫中有許
多小洞，四周是許多亂石。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "westdown"  : __DIR__"tiandi4",
                "northdown" : __DIR__"shulin1",
                "southwest" : __DIR__"shanqiu",
        ]));
        set("objects", ([
                __DIR__"npc/mangshe" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
