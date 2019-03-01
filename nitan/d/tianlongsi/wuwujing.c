inherit ROOM;

void create()
{
        set("short", "無無境");
        set("long", @LONG
一片水池靜卧眼前，一座精雕木橋橫跨其上，與其倒影恰成一圓，
映着空靈的水面，使你心中似有所動。彷彿體會到了眾生之源，萬物
之本的真諦。
LONG );
        set("outdoors","tianlongsi");
        set("exits", ([
            "north": __DIR__"yaotai",
            "south": __DIR__"qingxinge",                            
            "west" : __DIR__"cibeiyuan",
            "east" : __DIR__"yuhuayuan",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}