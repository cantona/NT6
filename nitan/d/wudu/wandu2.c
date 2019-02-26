#include <ansi.h> 
inherit ROOM;

string* npcs = ({
        "/clone/worm/xixuezhu",
        "/clone/worm/renmianzhu",
        "/clone/worm/tianwu",
        "/clone/worm/jiuweixie",
        "/clone/worm/shishixie",
        "/clone/worm/tieguxie",
        "/clone/worm/heiguafu",
        "/clone/worm/jinxianwugong",
});

void create()
{
        set("short", RED "萬毒窟" NOR);
        set("long", @LONG
這裏是一個天然形成的石洞，裏面深邃廣大。洞頂懸掛着許多鍾
乳石，不時傳來幾聲滴答的水聲。走在洞中，洞內陰暗潮濕，身旁忽
然傳來一陣“噝噝”的聲音。洞內似乎還有個小一點的支洞。
LONG);

        set("exits", ([
                "south" : __DIR__"wandu3",
                "north" : __DIR__"wandu1",
        ]));
        set("objects", ([
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
        ]));
    

        setup();
        replace_program(ROOM);
}