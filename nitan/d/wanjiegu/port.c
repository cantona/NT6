// Room: /t/wanjiegu/port.c

inherit ROOM;

void create()
{
        set("short", "善人渡");
        set("long", @LONG
這裏從前是瀾滄江的一個渡口，後來大理國在此修了一座鐵索橋，
人們便不用再乘船過江了。橋邊石上清清楚楚地刻着三個大字『善人
渡』。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"bridge",
            "east" : __DIR__"riverside3",
        ]));

        setup();
        replace_program(ROOM);
}