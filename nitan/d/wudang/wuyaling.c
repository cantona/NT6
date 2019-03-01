inherit ROOM;

void create()
{
        set("short", "烏鴉嶺");
        set("long", @LONG
這是一狹長的脊嶺，兩側懸削，一無所傍，但見白雲朵朵冉冉而
過，山風拂拂，陣陣襲來。數百只烏鴉正翱翔雲際，黑白分明，蔚成
奇觀。
LONG );
        set("objects", ([
                "/clone/quarry/niao3" : 3,
        ]));
        set("exits", ([
                "northdown": __DIR__"langmeiyuan",
                "southup"  : __DIR__"sanlaofeng",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -330);
        set("coor/z", 110);
        setup();
        replace_program(ROOM);
}