inherit ROOM;

void create()
{
        set("short", "林間小徑");
        set("long", @LONG
你走在一條小徑上，兩旁種滿了竹子，修篁森森，綠蔭滿地，除
了竹葉聲和鳥鳴聲，聽不到別的動靜。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaolu2",
                "north" : __DIR__"houyuan",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -320);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}