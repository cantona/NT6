inherit ROOM;

void create()
{
        set("short", "狼窩");
        set("long", @LONG
這裏是密林中的一個大樹洞，裏面腥味撲鼻，隨處都是吃
剩的獸骨殘渣。幾隻瘦得皮包骨頭的餓狼正抖擻精神，似乎要
出去覓食了。
LONG);

        set("exits", ([
                "out" : __DIR__"milin4",
        ]));
        set("objects", ([
                "/clone/quarry/lang"  : 2,
                "/clone/quarry/lang2" : 1,
        ]));

        setup();
        replace_program(ROOM);
}