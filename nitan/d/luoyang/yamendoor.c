inherit ROOM;

void create()
{
        set("short", "衙門");
        set("long", @LONG
這裡是衙門大門，兩扇朱木大門緊緊關閉著。“肅靜”“回避”的牌
子分放兩頭石獅子的旁邊。前面有一個大鼓，顯然是供小民鳴冤用的。幾
名衙役在門前巡邏。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yamen",
                  "west" : __DIR__"nroad2",
        ]));
        set("objects", ([
                "/d/zhongzhou/npc/yayi" : 4,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}