#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山頂");
        set("long", @LONG
這裡是一座高山的山頂，臨江一面是陡峭的懸崖，仔細望去，有
一些石窩可以落腳，西看去，只見雲霧中有好象有幾棟房子。
LONG );
        set("exits", ([
                  "eastdown" :  __DIR__"shudao8",
                "west" : __DIR__"shudao10",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15070);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}