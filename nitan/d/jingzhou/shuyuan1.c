inherit ROOM;

void create()
{
        set("short", "書院後院");
        set("long", @LONG
這裡是蕭湘書院的後院，打掃得非常幹凈，四周是過人高的圍牆，
偶爾傳來幾聲鳥語，讓人覺得安靜和諧，南邊有一道小門，通往一片
竹林。
LONG );
        set("exits", ([
                  "north" : __DIR__"shuyuan",
                  "south" : __DIR__"shijie",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7090);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}