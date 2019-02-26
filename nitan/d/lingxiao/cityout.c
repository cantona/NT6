inherit ROOM;

void create()
{
        set("short", "城外");
        set("long", @LONG
這裏是凌霄城的城外，出現在你面前的是高聳的城牆，看來
如果不從城門走，想要越牆而入，是不太可能的。凌霄城外野狼
很多，絕對不是什麼安全的地方，還是趕快進城吧。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                "west" : __DIR__"shanya",
        ]));
        set("objects", ([
                "/clone/quarry/lang" : 2,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}