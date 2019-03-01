inherit ROOM;

void create()
{
        set("short", "後山");
        set("long", @LONG
谷西是絕情谷後山，這裡地勢偏僻平時很少有人來。俯瞰
山下千溝萬壑，雲霧繚繞。翹首北望，只見峭壁絕險，雲霧深
鎖。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "southeast" : __DIR__"shanlu3",
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}