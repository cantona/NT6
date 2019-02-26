//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "農田");
        set("long", @LONG
這裏是湘西山中的一片農田。山裏土地貧脊也沒什麼可種的，鄉下
人家種了些小麥番薯。田裏禾秧已長得四寸來高。田梗上插種着大豆和
花生，倒是綠油油的顯得比較有生氣。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"tulu3",
                "south"     : __DIR__"maxipu",
        ]));
        set("objects", ([
                __DIR__"npc/cow" : 1,
        ]));
        set("outdoors", "jingzhou");
        set("coor/x", -7120);
	set("coor/y", -2170);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}