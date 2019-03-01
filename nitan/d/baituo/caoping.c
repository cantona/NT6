inherit ROOM;

void create()
{
        set("short","草坪");
        set("long", @LONG
這裡是一塊芳草坪，綠草茵茵，蝴蝶漫舞，讓人感到愜意。不過
偶爾也會碰到菜花蛇。
LONG );
        set("exits", ([
                "west" : __DIR__"shijie",
        ]));

        set("objects" , ([
                "/clone/beast/caihuashe" : random(2),
        ]));

        set("quarrys", ([
                "caihuashe"  : 100000,
                "dushe"      : 20000,
                "jinshe"     : 20000,
                "qingshe"    : 20000,
        ]));

        set("outdoors", "baituo");
        set("coor/x", -49970);
        set("coor/y", 19990);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}