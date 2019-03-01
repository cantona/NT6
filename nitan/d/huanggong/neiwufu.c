// Room: /d/huanggong/neiwufu.c

inherit ROOM;

void create()
{
        set("short", "內務府");
        set("long", @LONG
內務府專司宮內。下置七司：廣儲司、都虞司、掌儀司、慶豐司、
會計司、營造司、慎刑司，和三院：上駟院、武備院、奉宸院，各司其
職。內務府在乾清門內設敬事房，專門管理宮內太監。
LONG
        );
        set("exits", ([
                "south"     : __DIR__"wuying",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}