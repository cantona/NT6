inherit ROOM;

void create()
{
        set("short", "紫霄宮大門");
        set("long", @LONG
你已走到了展旗峰下，前面就是武當山最為宏大的宮宇紫霄宮了。
殿宇依山而築，高低錯落有致。周圍古木森森，翠竹成林，景色清幽。
這裡是武當師徒的主要活動場所。
LONG );
        set("exits", ([
                "northdown"  : __DIR__"shijie2",
                "southup"    : __DIR__"guangchang",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -280);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}