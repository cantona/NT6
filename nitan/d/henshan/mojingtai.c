inherit ROOM;

void create()
{
        set("short", "磨鏡台");
        set("long", @LONG
磨鏡台位於燕子巖下，與半山亭一溝相鄰。台前峯迴路轉，台旁
古鬆蒼翠，環境清幽。相傳南宗禪宗懷讓在此宣揚「頓悟法門」，坐
台高僧鬥法，懷讓磨鏡，智服北宗道一，此台因而傳名。「磨鏡台之
幽」是衡山大四絕之一。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shanlu8",
                "westup"     : __DIR__"shanlu7",
                "northup"    : __DIR__"shanlu6",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 2,
        ]));               
 
        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5550);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}