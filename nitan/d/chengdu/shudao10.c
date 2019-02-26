#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
一條小石階，有點破破爛爛，青草從石頭的縫隙中長了出來，有
些地方的石階由於年代久遠，已經磨的光滑如鏡。向上看去，只見雲
霧中有幾座房子。
LONG );
        set("exits", ([
                "east" :  __DIR__"shudao9",
                "northwest" : __DIR__"sanxia1",
        ]));
        set("objects", ([
                "/d/beijing/npc/old2" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15080);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}