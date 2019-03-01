inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
一條斜斜的小路，向西去不遠有片樹林，看上去黑呼呼的自從不
久前樹林中出了野豬傷人後，這條道就少人走。只有貪圖路近的人還
走這條道。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "southwest" : __DIR__"yezhulin",
                  "northeast" : __DIR__"dadao1",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}