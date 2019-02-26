// Room: /d/huijiang/goldroom.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "儲藏室");
        set("long",@LONG
這是一間小屋子，地上乾乾淨淨，纖塵不染。南邊靠牆角的地方放
着幾個箱子，屋子兩壁廂點滿了粗如兒臂的紅燭，照得四下如同白晝一
般。
LONG );
        set("exits", ([
                "east" : __DIR__"zongduo",
        ]));
        set("objects", ([
                CLASS_D("honghua")+"/xu-tianhong" : 1,
                __DIR__"obj/box" : 1,
        ]));        
        set("coor/x", -50080);
        set("coor/y", 9150);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}