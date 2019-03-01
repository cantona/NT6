//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "西山小路");
        set("long", @LONG
西邊都是荒山，亂石嶙峋，那是連油桐樹、油茶樹也不能種的。那
邊荒山之中，有一個旁人從來不知的山洞。翻過兩個山坡，來到一個大
山洞前。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"maxipu",
                "enter"     : __DIR__"dashandong",
        ]));
        set("outdoors", "jingzhou");
        set("no_clean_up", 0);
        set("coor/x", -7130);
	set("coor/y", -2180);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}