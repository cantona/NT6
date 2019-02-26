inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
這是一片松樹林。中間一條小路，兩邊都是黑森森的幾丈高的鬆
樹。樹上結着不少松果，間或有野兔遊悠遊而過。
LONG );
        set("exits", ([
                "southwest" : "/d/village/hsroad2",
                "east"      : __DIR__"jzroad2",
        ]));
        set("objects", ([
                "/clone/quarry/tu" : 2,
        ]));
        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}