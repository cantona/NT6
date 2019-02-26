inherit ROOM;

void create()
{
        set("short","龍門鏢局");
        set("long", @LONG
這兒是中州第一號鏢局，正對面是一人多高的香案，雙旁
坐着眾位鏢頭。亭中央的虎頭椅上正是龍門鏢局的總鏢頭都大
錦。右邊鄰着中州城的文定北街。
LONG);

        set("exits", ([
                "east" : __DIR__"wendingbei4",
                 
        ]));

        set("objects",([
                __DIR__"npc/dudajin":1,
        ]));
        set("coor/x", -9050);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}