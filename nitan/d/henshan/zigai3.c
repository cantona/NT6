inherit ROOM;

void create()
{
        set("short", "水蓮洞內");
        set("long", @LONG
這裏四周空曠，比起外面來卻沒有那麼潮濕，路到這裏卻沒有了。
LONG );

        set("exits", ([
               "south" : __DIR__"zigai2",
        ]));
        
        set("objects", ([
               "/clone/beast/yanjingshe" : 2,
        ]));
        
        setup();
        replace_program(ROOM);
}
