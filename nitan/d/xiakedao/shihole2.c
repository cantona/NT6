// /d/xiakedao/shihole2.c 俠客島 石洞2

inherit ROOM;

int do_learn(string arg);
void create()
{
        set("short", "石洞");
        set("long", @LONG
此洞通向第二組石室。洞中水聲淙淙，右面恰巧一道山泉流過。
中間四個草書大字深入石壁「飄渺煙雲」，兩側均是藍色帷幔環繞。
幾名藍衣弟子侍立。
LONG );
        set("exits", ([
                "out"   : __DIR__"shihole1",
                "enter" : __DIR__"shihole3",
                "north" : __DIR__"shiroom05",
                "south" : __DIR__"shiroom06",
                "east"  : __DIR__"shiroom07",
                "west"  : __DIR__"shiroom08",
        ]));
        set("objects", ([
                __DIR__"npc/maliu": 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25200);
        set("coor/z", 0);
        setup();
}
int valid_leave(object me, string dir)
{

        if (  (dir == "south")
            && (query("PKS", me)>10 )
           && objectp(present("ma liu", environment(me))) )
                return notify_fail("馬六把手一攔：你這種殺人狂魔，還敢到俠客島來，快滾!\n");
        return ::valid_leave(me, dir);
}