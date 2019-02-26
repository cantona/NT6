//Edited by fandog, 01/31/2000

inherit ROOM;
void create ()
{
        set ("short", "知府衙門");
        set ("long", @LONG
一座大廈，硃紅的大門，門上釘着碗口大的銅釘，門外兩盞大燈籠，
一盞寫着“荊州府正堂”，另一盞寫着“凌府”。門前兩座石獅子。
LONG);
        set("exits", ([ 
                "east" : __DIR__"datang",
                "west" : __DIR__"xijie3",
        ]));
        set("objects", ([
                __DIR__"obj/lion" : 2,
        ]));

        set("coor/x", -1490);
        set("coor/y", -2030);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}