// /d/playertown/road2.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"這是一條佈滿石子的小路，兩邊長着幾顆高大的楊柳樹，周圍有一小\n"
"片空地，景色不錯，非常適合建房。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("exits",([
                "west" : __DIR__"miao",
//          "north" : "/u/adx/workroom1",
                "east" : __DIR__"road19",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}