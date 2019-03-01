inherit ROOM;

void create()
{
        set("short", "亂石崗");
        set("long", @LONG
山路漸漸爬到了盡頭，眼前突然出現一片難見的開闊地來。
這是一片怪石林立的小山崗，只見那些石頭千姿百態，除了有
點荒涼外，倒是有種詭異的美麗。
LONG);
        set("exits", ([
                "north" : __DIR__"zhulin",
                "west" : __DIR__"houcun-shanlu",
                 "southeast" : __DIR__"luanfengang",
        ]));

        set("xinshoucun", 1);
            set("outdoors", "newbie");

           set("objects", ([
                "/clone/quarry/tu" : 40 + random(30),
           ]));
        setup();

        replace_program(ROOM);
}