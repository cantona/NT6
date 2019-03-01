#include <ansi.h> 
inherit ROOM;
string* npcs = ({
        "/clone/worm/shishixie",
        "/clone/worm/tieguxie",
        "/clone/worm/heiguafu",
        "/clone/worm/jinxianwugong",
        "/clone/worm/baizuwugong",
        "/clone/worm/datouwugong",
        "/clone/worm/huibeixie",
});

void create()
{
        set("short", HIR "千毒窟" NOR);
        set("long", @LONG
這裡是一個天然形成的石洞，裡面深邃廣大。洞頂懸掛著許多鐘
乳石，不時傳來幾聲滴答的水聲。走在洞中，洞內陰暗潮濕，身旁忽
然傳來一陣“□□”的聲音。
LONG);

        set("exits", ([
                "south" : __DIR__"qiandu1",
                "north" : __DIR__"qiandu3",
                "west" : __DIR__"qiandu4",
                "east" : __DIR__"qiandu5",
        ]));
        set("objects", ([
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
        ]));

        setup();
        replace_program(ROOM);
}