inherit ROOM;

void create()
{
        set("short", "竹園");
        set("long", @LONG
這裏是一個幽靜的竹園，高高低低的翠竹把這裏裝點得別有情致。
西北方是後院，東北方有個兔苑。南邊是花園。
LONG );
        set("exits",([
                // "northeast" : __DIR__"sheyuan",
                "northeast" : __DIR__"tuyuan",
                "northwest" : __DIR__"houyuan",
                "south"     : __DIR__"huayuan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "baituo");
        set("coor/x", -49980);
        set("coor/y", 20060);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}