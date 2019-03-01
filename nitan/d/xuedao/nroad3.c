inherit ROOM;

void create()
{
        set("short", "雪山北麓");
        set("long", @LONG
這裡山勢比大雪山東面稍緩，也不是十分的嚴寒。山道兩旁長得
有稀稀拉拉的一些野草。四下毫無人跡，只有幾只禿鷹在高處盤旋，
俯視著茫茫雪山。
LONG );
        set("exits", ([
                "south" : __DIR__"nroad4",
                "east"  : __DIR__"nroad2",
        ]));
        set("objects", ([
                "/clone/quarry/ying" : 2,
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
