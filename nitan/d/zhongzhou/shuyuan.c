inherit ROOM;

void create()
{
        set("short", "書院");
        set("long", @LONG
這是中州城南的一家書院，雖說這家書院不大，聽說從這
裡學有所成的人還不少，兵部尚書劉大人也在這裡念過書。書
院裡有幾個人搖頭晃腦正在念著四書五經。
LONG);

        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"wendingnan4",
        ]));

        set("no_fight",1);
        set("coor/x", -9050);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
}