// Room: /d/fuzhou/wenrufang.c
// Last Modifyed by Evil on Sep. 10 2002

inherit ROOM;

void create()
{
        set("short", "文儒坊");
        set("long", @LONG
舊名山陰巷，初名儒林坊，以宋代祭酒鄭穆居於此，改為文儒坊。
因為坊裏除了鄭穆之外，還先後住有九門提督、台灣總兵甘國寶，抗倭
名將、七省經略張經，清光緒皇帝老師陳寶琛之父陳承裘，《福建通志
》主編陳衍等儒林名士，故稱儒林坊名符其實。 
LONG );
        set("exits", ([
                "east"    : __DIR__"nanhoujie3",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -100);
	set("coor/y", -6210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}