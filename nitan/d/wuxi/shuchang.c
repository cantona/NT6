// Room: /d/wuxi/shuchang.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "吟春書場");
        set("long", @LONG
這雖然是一家南方的書場，但也懂得兼容並緒。常有來自北方的
京韻大鼓藝人、中原的評書藝人上座獻藝，當然，最多最受歡迎的還
是附近的蘇州評彈。跑堂的在聽書的客人中間跑來穿去，傳遞着茶水
和毛巾，服務甚是殷勤。
LONG );
        set("exits", ([
                "east" : __DIR__"southroad2",
        ]));
        set("objects", ([
                __DIR__"npc/shuke" : 1,
        ]));
        set("coor/x", 1030);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}