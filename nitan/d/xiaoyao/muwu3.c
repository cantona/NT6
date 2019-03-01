// muwu3.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "工匠屋");
        set("long", @LONG
這裡也是一間木屋，屋子中的擺設十分簡單，但是卻有很多工具，
鋸子啦，刨子啦，錘子啦。滿地的木屑，一看就知道是一個工匠的家。
看！我們的巧匠正忙著呢，不過不知道他又在做什麼呢？
LONG );
        set("exits", ([
                "north" : __DIR__"mubanlu",
        ]));
        set("objects", ([
                CLASS_D("xiaoyao")+"/fengas": 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 90);
        set("coor/y", -520);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
} 
