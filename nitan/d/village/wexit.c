inherit ROOM;

void create()
{
        set("short", "西村口");
        set("long", @LONG
這裡是華山腳下，雖然遠離縣城，卻沒有什麼山賊草寇在附近出
沒。東面是一個小村莊，看來村子裡人家不多，村民們過著日出而作，
日落而息的寧靜生活。穿過這個小村子，就是上華山的山路了。北邊
有間破房子。
LONG );

        set("exits", ([
                "east"      :__DIR__"nwroad1",
                "north"     : __DIR__"shack",
                "northwest" : "/d/huanghe/road6",
        ]));
        set("objects", ([
                __DIR__"npc/kid": 2,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "village");

        setup();
        replace_program(ROOM);
}
