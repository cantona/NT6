inherit ROOM;

void create()
{
        set("short", "虎穴");
        set("long", @LONG
這裏是個隱藏在密林裏的巖洞，裏面腥味撲鼻，隨處都是
吃剩的獸骨。幾隻威風凜凜的大老虎正躺在洞口懶懶的曬太陽。
LONG);

        set("exits", ([
                "south" : __DIR__"huxue2",
                "out" : __DIR__"milin7",
        ]));
        set("objects", ([
                "/clone/quarry/laohu" : 2,
        ]));

        setup();
        replace_program(ROOM);
}