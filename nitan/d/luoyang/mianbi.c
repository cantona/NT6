inherit ROOM;

void create()
{
        set("short", "面壁室");
        set("long", @LONG
這間屋子是用來懲罰那些先生上課時不認真聽講的孩子的，屋子又黑
又小，而且很悶熱，沒有任何東西，除了站着不能擺任何姿勢，看樣子到
這裏來受罰的小孩子可要好好吃吃苦頭了。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"sishu",
        ]));
        set("objects", ([
                "/d/wudu/npc/xuetong" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}