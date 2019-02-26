//room: shoushe.c
inherit ROOM;

void create()
{
        set("short","獸舍");
        set("long", @LONG
這裏是白駝山莊的獸舍。白駝山馭獸術天下知名，這裏也豢養了
各種猛獸，以供下山的白駝弟子使用。獸舍裏猛獸長聲嘶嚎，老遠都
聽得見。尤其是夜晚聽來，更有是撕心裂肺的慘烈。
LONG );
        set("exits",([
                "east"  : __DIR__"tuyuan",
        ]));
        set("outdoors", "baituo");
        set("objects",([
                __DIR__"npc/fox" :1,
                __DIR__"npc/wolf" :1,
                __DIR__"npc/tiger" :1,
                __DIR__"npc/lion" :1,
        ]));
        set("coor/x", -49980);
        set("coor/y", 20070);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
