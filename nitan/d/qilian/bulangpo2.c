// Room: /d/qilian/bulangpo2.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "不狼坡");
        set("long", @LONG
山勢越來越兇險，遍是齊腰雜草，連山狼也不便行動，唯見山野兔
和幾只蒼鷹翱翔於空。往西北四十余裡，可遙見一嶺，蜿蜒連綿數百裡，
滿眼翠綠，名大通嶺。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "northwest" : __DIR__"datongling",
                "southdown" : __DIR__"bulangpo1",
        ]));
        set("objects", ([
                "/d/wudang/npc/yetu": 2,
        ]));
        set("coor/x", -9900);
        set("coor/y", 2900);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}