// Room: chufang.c

inherit ROOM;
void create()
{
        set("short", "酒樓廚房");
        set("long", @LONG
這裏是酒樓後面的廚房，幾個大水池前面有不少的夥計在摘菜和
清洗碗碟，還有一些夥計站在油煙直冒的油鍋面前努力的翻炒着各色
菜餚，而一個粗手大腳的中年廚娘大聲吆喝，指手畫腳的卻不幹活。
LONG );
        set("exits", ([
                "west" : __DIR__"jiudian",
        ]));
        set("objects", ([
                __DIR__"npc/chuniang" : 1,
        ]) );
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("coor/x", -15180);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}