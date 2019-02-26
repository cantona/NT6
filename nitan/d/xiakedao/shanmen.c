// shanmen.c 山門

inherit ROOM;

void create()
{
        set("short", "山門");
        set("long", @LONG
你的面前是一座林木繁茂的高山，幾座山峯在雲霧中隱約可見，
一條山徑向山上延伸，不時有幾個江湖好漢從你身邊走過，他們都
是到俠客島來專研武功的。石壁上刻着三個大字 "俠客島" ，這就
是江湖上傳聞的俠客島。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup" : __DIR__"road1",
                "north" : __DIR__"lin8",
        ]));
        set("objects", ([
                __DIR__"npc/dizi2" : 1]));
        set("coor/x", -3000);
        set("coor/y", -22010);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}