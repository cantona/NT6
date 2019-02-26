inherit ROOM;

void create()
{
        set("short", "青石小巷");
        set("long", @LONG
這裏一條青石小路，路面用青石板鋪成，剛剛下過雨，路面很是乾淨，
小巷內靜悄悄的，只能聽見自己的腳步聲，偶爾風吹動樹枝發出沙沙的響
聲。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"juyi",
                  "west" : __DIR__"xiaoxiang",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));

	set("coor/x", -6970);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}