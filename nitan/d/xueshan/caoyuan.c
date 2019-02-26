inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
這裏是雪山腳下的一片草原。北面是起伏的羣山，山頂上積着終
年不化的雪。西邊有一條土路。
LONG );

        set("exits", ([
                "west"      : __DIR__"tulu1",
                "northeast" : "/d/xingxiu/silk5" ,
        ]));

        set("objects", ([
                "/clone/quarry/tu" : 4 ,
        ]));

        set("outdoors", "xuedao");

        setup();
        replace_program(ROOM);
}