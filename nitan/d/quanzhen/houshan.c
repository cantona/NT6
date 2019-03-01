// houshan.c 後山
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "後山");
        set("long", @LONG
這裡已經出了重陽宮，到了終南山的後山。這裡鳥語花香，
空氣清新，山勢也平緩得多了。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "west" : __DIR__"jingxiushi",
                "northeast" : __DIR__"xiaolu1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2720);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}