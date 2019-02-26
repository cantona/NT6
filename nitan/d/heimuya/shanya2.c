inherit ROOM;

void create()
{
        set("short", "山崖");
        set("long", @LONG
此處入雲高聳，已是黑木崖上，兩旁站滿了日月神教的弟子。兩
旁的刻着兩行大字，右首是「文成武德」，左首是「仁義英明」，橫
額上刻着「日月光明」四個大紅字。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "south" : __DIR__"shanya3",
            "north" : __DIR__"shanya1",
        ]));
        set("objects", ([
                __DIR__"npc/dizi2" : 4,
        ]));
        setup();
        replace_program(ROOM);
}