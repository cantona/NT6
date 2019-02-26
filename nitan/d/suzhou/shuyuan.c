// Room: /d/suzhou/shuyuan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "書院");
        set("long", @LONG
這裏是書院的講堂，窗明几淨，一塵不染。一位老夫子坐在太師椅
上講學。在他的兩側坐滿了求學的學生。一張古意盎然的書案放在他的
前面，案上擺着幾本翻開了的線裝書籍。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "northeast" : __DIR__"nandajie1",
        ]));
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/jiaoxi" : 1,
        ]));
//        set("no_clean_up", 0);

	set("coor/x", 1100);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}