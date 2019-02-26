// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"這是一條佈滿石子的小路，兩邊長着幾顆高大的楊柳樹，北面的路似\n"
"乎總是被白煙瀰漫着，西南面是通往村外的路，在小路的西面赫然立着一\n"
"座小亭，裏面依稀可見幾個身影。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        
        set("exits",([
                "north" : __DIR__"road7",
                "south" : __DIR__"road5",
                "west" : __DIR__"road4",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}