// Room: /d/village/nwexit.c

inherit ROOM;

void create()
{
        set("short", "東村口");
        set("long", @LONG
這裏是華山腳下，雖然遠離縣城，卻沒有什麼山賊草寇在附近出
沒。往東就是上山的路了。西邊是一個小村莊，村子裏人家並不多，
村民們過着日出而作，日落而息的寧靜生活。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"eroad1",
                "east" : "/d/huashan/path1",
        ]));
        set("objects", ([
            __DIR__"npc/boy": 1
        ]) );

        set("outdoors", "village" );
        setup();
        replace_program(ROOM);
}
