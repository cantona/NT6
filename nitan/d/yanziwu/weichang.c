// Room: /d/yanziwu/weichang.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "綠圍場");
        set("long", @LONG
這裡是慕容世家圍獵之處。圍場不大，但林深草茂，小獸很多。秋
來春往，南來北去的候鳥正當時令，前來湊趣，來考究主人們的箭頭是
否鋒銳。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "south" : __DIR__"xuanshuan",
        ]));
        set("objects", ([
                "/d/wudang/npc/yetu" : 1,
                "/d/hangzhou/npc/maque" : 1,
        ]));
        set("coor/x", 830);
        set("coor/y", -1240);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
