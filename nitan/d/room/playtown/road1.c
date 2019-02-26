// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"你走在一條曲長的小道上，時而有從東面兩三個村民結夥向北面的村\n"
"外離去，東面是一個熱鬧的集市，是村女每天必去的地方；西面是村長的\n"
"居所，總有一些人會登門拜訪。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("no_clean_up",0);
        
        set("exits",([
                "north" : __DIR__"road11",
                "east" : __DIR__"road17",
                "west" : __DIR__"chunzhangjia",
                "south":        __DIR__"road2",
        ]));
                
        setup();
        
        // replace_program(ROOM);
        
}