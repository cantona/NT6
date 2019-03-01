// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","青磚路");
        set("long",
"這是一條非常平整的青磚舖成的路，北面是一個非常別致的小花園，\n"
"東南面是一個三岔口。\n"
);
        set("recordable_room",1);
        set("outdoors","playertown");        
        set("exits",([
                "northeast" : __DIR__"huayuan1",
                "west" : __DIR__"road11",
                "southeast" : __DIR__"road8",
        ]));
        setup();
        // replace_program(ROOM);
}