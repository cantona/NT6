inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一條崎嶇的山路上，再往南，就進入了雲貴高原了。
北面是一條大河攔住去路。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "south": __DIR__"yunnan",
                "north"  :__DIR__"road6",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}