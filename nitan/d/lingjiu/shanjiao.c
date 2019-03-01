inherit ROOM;

void create()
{
        set("short", "縹緲峰山腳");
        set("long", @LONG
這裡是縹緲峰山腳，抬頭上望，縹緲峰聳入雲天，峰頂白雲繚繞，
宛若仙境。白雲深處隱約可見瓊樓玉宇，那就是令江湖人物聞名喪膽
的靈鷲宮。聽說宮中住著一些武藝高強的女俠，而且只收女弟子為徒。
LONG );
        set("outdoors", "lingjiu");
        set("exits", ([
                "westup" : __DIR__"ya",
                "southdown" : "/d/xingxiu/tianroad2"
        ]));
        set("objects", ([
                __DIR__"npc/jiuyi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}