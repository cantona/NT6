inherit ROOM;

void create()
{
        set("short", "苗家大院");
        set("long", @LONG
這是苗家莊園正廳前面的一個寬闊的大院，大院裏種植着
各類花草，假山水池，瓊樓高台，非常豪華。院內打掃得非常
乾淨，北邊是一間廚房，南邊也有一間小屋。
LONG);
        set("exits", ([
                  "west"  : __DIR__"miaojia_men",
                  "east"  : __DIR__"miaojia_zhengting",
                  "north" : __DIR__"miaojia_chufang",
                  "south" : __DIR__"miaojia_chaifang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -9020);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}