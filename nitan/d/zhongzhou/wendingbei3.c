inherit ROOM;

void create()
{
        set("short", "文定北街");
        set("long", @LONG
這是中州城文定北街，寬敞的街道讓人不竟心情一暢。街
道的東面就是中州的巡捕房，你不竟加快步伐，看來這種地方
還是少去為妙。西面一座大房子，門口的兩隻石獅子朝你瞪着
眼睛。門口還有一隻大鼓，原來這就是中州的縣衙門。
LONG);

        set("outdoors", "zhongzhou");
        set("exits", ([
                "east" : __DIR__"xunbu",
                "south" : __DIR__"wendingbei2",
                "west" : __DIR__"yamen",
                "north" : __DIR__"wendingbei4",
        ]));

        set("objects",([
                __DIR__"npc/old1" : 1,
                __DIR__"npc/old2" : 1,
        ]));

        set("coor/x", -9040);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}