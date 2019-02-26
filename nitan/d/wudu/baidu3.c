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
這裏是一個天然形成的石洞，裏面深邃廣大。洞頂懸掛着許多鍾
乳石，不時傳來幾聲滴答的水聲。走在洞中，洞內陰暗潮濕，身旁忽
然傳來一陣“噝噝”的聲音。
LONG );
        set("exits", ([
                "north" : __DIR__"baidu2",
        ]));
        set("objects", ([
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
        ]));

        setup();
        replace_program(ROOM);
}