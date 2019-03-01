// /guanwai/xuedi1.c

inherit ROOM;

#include "gwxuedi.h"

void create()
{
        set("short", "雪地");
        set("long", @LONG
這裡是一片白茫茫的雪地，一眼望不到邊際。四周一個人影也沒有，厚
厚的積雪踩起來發出咯吱的響聲，大地上留下一串孤獨的腳印。寒冷的北風
呼嘯而過，吹得臉生痛。暗淡的太陽低懸在天邊，顯得那麼蒼白。
LONG );
        set("exits", ([
                "west"       : __DIR__"dongcheng",
                "northeast"  : __DIR__"xuedi2",
                "southeast"  : "/d/yubifeng/songlin1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "guanwai");
        set("coor/x", 4010);
	set("coor/y", 9240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}