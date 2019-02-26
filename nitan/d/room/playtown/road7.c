// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"這是一條碎石小道。北面是三岔道，南面延伸至村外的小路，而在東\n"
"面，一座小廟屹立在那，裏面傳來鄉親們的禱告聲。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("no_clean_up",0);
        
        set("exits",([
                "north"        :        __DIR__"road8",
                "south"        :        __DIR__"road6",
                "east"        :        __DIR__"miao",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}