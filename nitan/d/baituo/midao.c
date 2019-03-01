inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這是漆黑的密道，當年白駝山弟子為了直達中原而挖鑿的。
LONG );
        set("region", "baituo");
        set("exits" , ([
                "east" : "/d/city/guangchang",
                "up"   : __DIR__"neishi",
        ]));
        set("objects",([
                __DIR__"obj/shenshe" : 1 ,
        ]));

        setup();
        replace_program(ROOM);
}