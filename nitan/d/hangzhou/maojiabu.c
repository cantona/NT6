// maojiabu.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "茅家埠");
        set("long", @LONG
路兩旁蓋著幾座小土房。房門口一位老大娘正在喂雞，幾個小孩
正在追逐嬉戲。北邊是上黃泥嶺。南面是丁家山。
LONG);
        set("exits", ([
            "southwest"   : __DIR__"tulu1",
            "northup"     : __DIR__"huangniling",
        ]));
        set("objects", ([
            __DIR__"npc/boy" : 1,
            __DIR__"npc/oldwoman" : 1,
            __DIR__"npc/camel" : 1,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 760);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}