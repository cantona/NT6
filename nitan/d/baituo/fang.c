inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裏是白駝山弟子的練功房。裏面有幾個單間，是練功室。第子
們在裏邊砌磋武藝，絕對不允許外人打攪。
LONG );
        set("exits",([
                "west" : __DIR__"liangong",
                "1"    : __DIR__"room1",
                "2"    : __DIR__"room2",
                "3"    : __DIR__"room3",
        ]));

        set("objects",([
                __DIR__"npc/trainer" : 1,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}