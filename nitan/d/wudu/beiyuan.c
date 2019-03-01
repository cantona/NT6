inherit ROOM;

void create()
{
        set("short", "北院");
        set("long", @LONG
這裡是北院，院子裡靜悄悄的。北面有一個廚房，遠遠飄來一股
飯香，想是該開飯了。  
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"bingqi",
                "south" : __DIR__"lianwu",
                "north" : __DIR__"chufang",
        ]));

        setup();
}