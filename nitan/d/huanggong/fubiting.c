// fubiting.c

inherit ROOM;

void create()
{
        set("short", "浮碧亭");
        set("long", @LONG
御花園兩邊建有魚池, 池上建亭, 這裡就是浮碧亭. 亭子朝南抱廈, 
亭座下有涵洞, 洞中有井. 夏日, 池水清澈, 金魚戲遊于荷花之下. 冬
日, 池水結冰, 金魚就入井過冬. 
LONG
);
        set("outdoors", "huanggong");
        set("exits", ([
                "southwest" : __DIR__"yuhuayuan",
        ]) );
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}