inherit ROOM;

void create()
{
        set("short", "南村口");
        set("long", @LONG
這裡是華山腳下，雖然遠離縣城，卻沒有什麼山賊草寇在附近出
沒。西面是一個小村莊，看來村子裡人家不多，村民們過著日出而作，
日落而息的寧靜生活。穿過這個小村子，就是上華山的山路了。
LONG );
        set("exits", ([
                "north" : __DIR__"sroad1",
                "south" : __DIR__"hsroad3",
        ]));
        set("objects", ([
                "/clone/quarry/gou" : 1,
        ]));
        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}