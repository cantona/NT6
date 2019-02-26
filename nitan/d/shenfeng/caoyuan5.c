inherit ROOM;
void create()
{
        set("short", "戈壁");
        set("long", @LONG
戈壁平坦如鏡，和沙漠上的沙丘起伏全然不同，只見一片
平沙，凝眸遠眺，只覺天地相接，萬籟無聲，身當此境，不禁
也生慄慄之感，頓覺大千無限，一己渺小異常。
LONG);
        set("outdoors", "xiyu");
        set("exits", ([
                  "east" : __DIR__"caoyuan4",
                   "west"  : "/d/xingxiu/nanjiang1",
                   "south" : "/d/xingxiu/nanjiang2",
                   "southwest" : "/d/xingxiu/nanjiang1",
        ]));

        setup();
        replace_program(ROOM);
}