inherit ROOM;

void create()
{
    set("short", "前院");
    set("long", @LONG
你現在正站在一個寬敞的院子中。院子原來是作為練武場
用的。但自從桃花島弟子被黃藥師逐出島外，就沒人在此練武。
東面是兵器室，西面是廚房，往南是桃花山莊正廳。
LONG);
    set("exits", ([
        "north" : __DIR__"damen",
        "south" : __DIR__"dating",
        "east"  : __DIR__"bingqi",
        "west"  : __DIR__"chufang",
    ]));
    set("outdoors", "taohua");
    set("no_clean_up", 0);
    setup();
    replace_program(ROOM);
}