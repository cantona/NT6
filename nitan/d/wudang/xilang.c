inherit ROOM;

void create()
{
        set("short", "西廂走廊");
        set("long", @LONG
你走在一條走廊上，東邊是大殿，北邊是一座樓閣。西面樓上傳
來陣陣打鬥聲。
LONG );
        set("exits", ([
                "northup" : __DIR__"cangjingge",
                "east"    : __DIR__"sanqingdian",
                "westup"  : __DIR__"caolianfang",
        ]));
        set("coor/x", -380);
        set("coor/y", -300);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}