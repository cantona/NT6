inherit ROOM;

void create()
{
        set("short", "石壁小徑");
        set("long", @LONG
這裡道路驟陡，一線天光從石壁之間照射下來，只覺陰氣
森森，寒意逼人。路旁又現一堆白骨，骸骨中光亮閃耀，竟是
許多寶石珠玉。
LONG);
        set("outdoors", "gaochang");

        if (random(10) > 8)
                set("objects", ([
                        "/clone/money/gold" : 1,
                        "/clone/fam/item/bixue" : 1,
                        __DIR__"obj/skeleton" : 1,
                ]));

        set("exits", ([ 
                "south" : __DIR__"xiaojing1",
                  "west" : __DIR__"feixu1",
        ]));

        setup();
        replace_program(ROOM);
}