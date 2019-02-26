// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","青磚路");
        set("long",
"這是一條非常平整的青磚鋪成的路，北面是一個非常別緻的小花園，\n"
"東面是村女們經常光顧的地方-清心池，東南面是一個三岔口，是出村的\n"
"必經之路。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("no_clean_up",0);
        
        set("exits",([
                "north"        :        __DIR__"huayuan4",
//        "east"  :   __DIR__"nvyutang",
                "southwest"        :        __DIR__"road8",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}