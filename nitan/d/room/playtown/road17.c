// /d/playertown/road3.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"這是一條布滿石子的小路，兩邊長著幾顆高大的楊柳樹，在小路的北\n"
"方，傳來陣陣小販的吆喝聲，大概集市就在那裡吧；東南面是通往村外的\n"
"路，東面的小路是深入村莊的中心。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("exits",([
                "east"        : __DIR__"road8",
                "west"        : __DIR__"road1",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}