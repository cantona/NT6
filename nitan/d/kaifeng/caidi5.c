inherit ROOM;

void create()
{
        set("short", "菜地");
        set("long", @LONG
這片菜園子幾畦地裡種了一些時鮮蔬菜。另外有幾個木樁搭起的
菜架子，供一些爬籐的蔬菜生長，不過你舉目看去，老大的一片菜園
子，居然疏疏落落的沒有幾棵菜。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"caidi",
                  "east" : __DIR__"kongdi",
                  "south" : __DIR__"maofang",
                  "north" : __DIR__"jiaomen",
        ]));

        set("outdoors", "kaifeng");
	set("coor/x", -4990);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}