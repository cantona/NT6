inherit ROOM;

void create()
{
        set("short", "水蓮洞內");
        set("long", @LONG
這裡四周空曠，比起外面來卻沒有那麼潮濕。
LONG );
        set("exits",([
               "south" : __DIR__"inhole2",
        ]));
        
        set("objects",([
               "/clone/beast/yanjingshe" : 2,
        ]));
        
        setup();
        
}

void init()
{
       object me = this_player();

       if (present("fire", me))
                      set("exits/north", __DIR__"zigai3");
        
        return ;
}
