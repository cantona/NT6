#include <ansi.h>

inherit ROOM;

#define PLACE "bjw"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "修羅門分壇");
        set("long", @LONG
這裏是黑道組織修羅門的北京分壇，沒想到堂堂的修羅門分壇，
竟然設立在這樣一個不起眼的建築下面，可能是天子腳下，皇城根兒
的緣故，這裏的分壇格外的隱祕，而且恐怖。正中的鑲金椅上正卧着
一位妖豔的女子。旁邊的牆上掛着一個任務牌（paizi）。
LONG );

        set("objects", ([
               "/d/beijing/npc/boss-hu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "up" : "/d/beijing/minju",
        ]));

        setup();
}
#include <bang_bad.h>
