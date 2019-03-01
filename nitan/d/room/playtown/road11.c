// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","青磚路");
        set("long",
"這是一條非常平整的青磚舖成的小路。周圍有一小片空地，景色不錯\n"
"，很適合建房。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");        
        set("exits",([
                "north" : __DIR__"road12",
                "east" : __DIR__"road9",
                "south" : __DIR__"road1",
        ]));
        setup();
        // replace_program(ROOM);
}