inherit ROOM;

void create()
{
        set("short", "虎頭巖");
        set("long", @LONG
一塊巨大的巖石看上去好象一個虎頭正張大了血盆大口咆哮，虎
身隱藏在草木叢中。
LONG );
        set("objects", ([
                "/clone/quarry/laohu" : 1,
        ]));
        set("exits", ([
                "northdown" : __DIR__"wulaofeng",
                "southup"   : __DIR__"chaotiangong",
        ]));

        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -360);
        set("coor/z", 140);
        setup();
        replace_program(ROOM);
}