inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這是一條小房間。什麼東西都沒有，只是一個黑乎乎的小洞口，
不知道下面都隱藏了些什麼。
LONG );
        set("exits", ([
                "south" : __DIR__"midao",
                "up" : "/d/city/guangchang",
        ]));
        setup();
        replace_program(ROOM);
}