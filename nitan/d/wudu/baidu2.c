inherit ROOM;

string* npcs = ({
        "/clone/worm/changtuizhu",
        "/clone/worm/huabanzhu",
        "/clone/worm/baizuwugong",
        "/clone/worm/qianjiewugong",
        "/clone/worm/datouwugong",
        "/clone/worm/changaoxie",
        "/clone/worm/huibeixie",
});

void create()
{
        set("short", "百毒窟");
        set("long", @LONG
這裡是一個天然形成的石洞，裡面深邃廣大。洞頂懸掛著許多鐘
乳石，不時傳來幾聲滴答的水聲。走在洞中，洞內陰暗潮濕，身旁忽
然傳來一陣“□□”的聲音。
LONG );
        set("exits", ([
                "north" : __DIR__"baidu1",
                "south" : __DIR__"baidu3",
                "west" : __DIR__"baidu4",
                "east" : __DIR__"baidu5",
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