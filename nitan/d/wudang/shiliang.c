inherit ROOM;

void create()
{
        set("short", "石樑");
        set("long", @LONG
你走入山塢中，有一道石樑跨溪而建，這裡是九渡澗的下流，各
嶺之水均在此交匯景色極佳。附近設有許多小吃店，遊人至此，大多
小住歇歇腳力。再往上就是陡峭的十八盤了。
LONG );
        set("exits", ([
                "northup"    : __DIR__"taizipo",
                "southup"    : __DIR__"shibapan",
                "east"       : __DIR__"shop",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -250);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}