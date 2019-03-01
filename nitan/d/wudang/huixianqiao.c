inherit ROOM;

void create()
{
        set("short", "會仙橋");
        set("long", @LONG
這裡地勢稍平，一道山澗緩緩流過，一座窄窄的木橋橫在澗上，
只溶一人經過。
LONG );
        set("exits", ([
                "north" : __DIR__"chaotiangong",
                "south" : __DIR__"toutiangate",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -380);
        set("coor/z", 150);
        setup();
        replace_program(ROOM);
}