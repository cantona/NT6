// Room: /d/yueyang/yamen.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "衙門");
        set("long", @LONG
這裏是岳陽府衙。兩扇朱木大門緊緊關閉着，門上貼着“老爺丁憂”
字樣的字條，看來新官未至，這個門也就不用開了。“肅靜”“迴避”
的牌子分放兩頭石獅子的旁邊。門前側面架子擺着個皮鼓，掛着一對木
棰。顯然是供小民鳴冤用的。幾名衙役在門前巡邏。
LONG );
        set("exits", ([
                "south" : __DIR__"dongjie",
        ]));
        set("objects", ([
                __DIR__"npc/yayi" : 2,
        ]));
        set("outdoors", "yueyang");
	set("coor/x", -6190);
	set("coor/y", -3000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}