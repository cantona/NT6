inherit ROOM;

void create()
{
        set("short", "鬆林小路");
        set("long", @LONG
這是山腳鬆林中的小路，兩邊長滿參天的紅鬆樹，只能看見一線
天空。路旁有道士在奮力砍樹。西邊通向密林深處，東邊可回大道。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "west" : __DIR__"slxl2",
                "east" : __DIR__"wdroad10",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -330);
        set("coor/y", -180);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}