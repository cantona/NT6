// road1.c 小路

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這條小路是膽大的男人們去密林裏打獵時走出來的，再往西走就到草原
邊緣而進入森林了。偶爾可以聽見遠處傳來野獸的吼聲，你還是快回去吧。
LONG
        );

        
        set("exits", ([
            "westup" : __DIR__"shanqiu",
            "east" : __DIR__"pmchang",
            
        ]));

        set("outdoors", "hasake");
        
        setup();
        replace_program(ROOM);
}