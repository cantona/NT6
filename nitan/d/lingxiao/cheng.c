inherit ROOM;

void create()
{
        set("short", "居室");
        set("long", @LONG 
這是成自學的房間。成自學雖和四位師弟一樣，由白自在代
師授藝，但在四位師兄弟中，他和白自在關系最好。同時他為人
方正，剛嚴不曲，最得白自在信任，所以白自在在失蹤以前，把
凌霄城的寒玉牌交給他保管。這間屋子整潔典雅，只在桌上放著
一卷未寫完的帛卷。
LONG);
        set("exits", ([
                    "south"  : __DIR__"zoulang4", 
        ]));
        set("objects", ([  
                __DIR__"npc/cheng" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
