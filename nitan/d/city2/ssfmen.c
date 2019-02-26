inherit ROOM;

void create()
{
        set("short", "尚書府大門");
        set("long", @LONG
這裏是京城尚書府大門，經常有人進出，可見尚書大人為國事操
勞何等之辛苦了，門口有兩個家將，看你進來，居然也沒來盤問你，
真是奇怪。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "west" : __DIR__"ydmen",
                "east" : __DIR__"ssfu",
        ]));

        set("objects", ([
  
        ]));

        setup();
        replace_program(ROOM);
}

