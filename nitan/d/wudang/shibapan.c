inherit ROOM;

void create()
{
        set("short", "十八盤");
        set("long", @LONG
這是一個很大的斜坡，俗稱十八盤，大石階一級一級筆直而上，
頗費腳力。這裡坡坡有神，拐拐有祠，往上十裡之後即是靈霄宮。
LONG );
        set("exits", ([
                "northdown" : __DIR__"shiliang",
                "southup" : __DIR__"shijie2",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -260);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}