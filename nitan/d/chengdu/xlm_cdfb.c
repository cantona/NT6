#include <ansi.h>

inherit ROOM;

#define PLACE "cd"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "修羅門分壇");
        set("long", @LONG
這裏是黑道組織修羅門的成都分壇，這是一間陰森恐怖的房間，
到不是因為他的名字可怕，而是左右兩旁的那兩尊修羅王的塑像，形
態詭異，讓人感覺彷彿和世界隔離了一般。牆上掛着修羅門的任務牌
（paizi）。
LONG );

        set("objects", ([
               __DIR__"npc/boss-leng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : __DIR__"qingyanggong",
        ]));

        setup();
}
#include <bang_bad.h>
