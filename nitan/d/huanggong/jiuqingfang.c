// jiuqing.c

inherit ROOM;

void create()
{
        set("short", "九卿房");
        set("long", @LONG
這裡是六部尚書和都察院御史、大理寺卿、通政使司通政使等九卿
官員以及王公、貝勒大臣等候皇上召見的場所, 對面是蒙古王公值房, 
所以也叫"待漏房".
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"qianqingmen",
        ]));
	set("coor/x", -2800);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}