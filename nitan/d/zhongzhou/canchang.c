inherit ROOM;

void create()
{
        set("short", "菜場");
        set("long", @LONG
這是熙熙攘攘的菜場，地上濕濕的長年沒有幹的時候。商
人小販們走來走去都想盡快賣完了回家。常年在這裡擺攤的都
要給南面屋裡的惡霸交保護費。
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "south" : __DIR__"eba",
                "west" : __DIR__"wendingnan1",
        ]));
        set("objects", ([
                __DIR__"npc/caifan" : 1,
                "/d/city/npc/liumangtou" : 1,
        ]));

        set("coor/x", -9030);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}