inherit ROOM;

void create()
{
        set("short", "牢房");
        set("long", @LONG
這是一間陰暗潮濕的牢房，地上幾隻老鼠莫無旁人在那裏
找東西吃。就只有鐵門上的一個小窗户透一點光進來。這種地
方多呆一刻你就要發瘋。
LONG);
        set("exits", ([
                "west" : __DIR__"xunbu",
        ]));

        set("coor/x", -9020);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}