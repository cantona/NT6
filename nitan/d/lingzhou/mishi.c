// d/lingzhou/mishi.c

#include "room.h"

inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這是一品堂的密室，平時只有堂主一個人可以進來。密室不大卻陳
設豪華，地上舖著猩紅的新疆純羊毛手織地毯，四個角落裡點著牛油巨
燭，一張寬大的軟床放在屋中央，粉色的紗帳罩在床的上方。床邊的矮
幾上擺著的新疆的馬奶子葡萄看上去晶瑩剔透，靠牆有張大理石制的桌
子，一縷甜香從桌上的青銅香爐裡飄了過來。
LONG
        );
        set("exits", ([
                "east" : __DIR__"yipindating",
        ]));
        create_door("east","木門","west",DOOR_CLOSED);
        set("objects", ([
                __DIR__"npc/duan" : 1,
        ]));
        set("coor/x", -6305);
        set("coor/y", 2965);
        set("coor/z", 0);
        setup();
}
