inherit ROOM;

void create()
{
        set("short", "鬥母宮");
        set("long", @LONG
這是給進香客們休息的地方。四周圍放著一溜檀木紅漆椅。幾個
進香客坐在上面休息。
LONG );
        set("exits", ([
                "southwest" : __DIR__"doushuai",
                "north" : __DIR__"yuhuayuan",
        ]));
        set("objects",([
                "/d/wudang/npc/guest" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}