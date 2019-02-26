#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "竹屋");
    set("long", @LONG
這裏是神龍教主的居室----仙福居，中間一張大桌，牆上掛着一
副水墨畫，沒有什麼特別出奇之處。
LONG );
    set("exits", ([
	"east" : __DIR__"zhulin",
    ]));

    set("objects",([
         CLASS_D("shenlong")+"/su": 1,
         __DIR__"npc/mujianping": 1,
         __DIR__"npc/fangyi": 1,
    ]));
    setup();
    replace_program(ROOM);
}
