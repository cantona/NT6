// /d/playertown/road4.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"這兒是小村的中心大街，南面是一片竹林，風吹過的時候沙沙的聲音煞是動聽，左右\n"
"看了看，西面隱約可以看一棟金黃色閃閃發光的奇怪建築物，而東面的不遠處有一座小亭。\n"
);

        set("outdoors","playertown");
              set("recordable_room",1); 
        set("exits",([
                "west"        :        __DIR__"road3",
                "east"        :        __DIR__"road6",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}